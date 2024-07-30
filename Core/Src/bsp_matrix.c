#include "bsp_matrix.h"
#include "main.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdio.h>

// Row output pins
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_R1 = { Key_Line_R1_GPIO_Port, Key_Line_R1_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_R2 = { Key_Line_R2_GPIO_Port, Key_Line_R2_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_R3 = { Key_Line_R3_GPIO_Port, Key_Line_R3_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_R4 = { Key_Line_R4_GPIO_Port, Key_Line_R4_Pin };

const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_ROWS[MATRIX_N_ROWS] = {
  MATRIX_LINE_GPIO_R1,
  MATRIX_LINE_GPIO_R2,
  MATRIX_LINE_GPIO_R3,
  MATRIX_LINE_GPIO_R4
};

// Column input pins (pull-up)
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_C1 = { Key_Line_C1_GPIO_Port, Key_Line_C1_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_C2 = { Key_Line_C2_GPIO_Port, Key_Line_C2_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_C3 = { Key_Line_C3_GPIO_Port, Key_Line_C3_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_C4 = { Key_Line_C4_GPIO_Port, Key_Line_C4_Pin };

const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_COLS[MATRIX_N_COLS] = {
  MATRIX_LINE_GPIO_C1,
  MATRIX_LINE_GPIO_C2,
  MATRIX_LINE_GPIO_C3,
  MATRIX_LINE_GPIO_C4
};


const Matrix_Key MATRIX_LINE_KEY_MAP[MATRIX_N_ROWS][MATRIX_N_COLS] = {
  { MATRIX_KEY_1, MATRIX_KEY_2, MATRIX_KEY_3, MATRIX_KEY_4 },
  { MATRIX_KEY_5, MATRIX_KEY_6, MATRIX_KEY_7, MATRIX_KEY_8 },
  { MATRIX_KEY_9, MATRIX_KEY_10, MATRIX_KEY_11, MATRIX_KEY_12 },
  { MATRIX_KEY_13, MATRIX_KEY_14, MATRIX_KEY_15, MATRIX_KEY_16 }
};

static Matrix_Line_Col __Matrix_Row_Scan(Matrix_Line_Row row) {
  // Set specified row to low, others are high.
  for (uint8_t i = 0; i < MATRIX_N_ROWS; ++i) {
    if (i == row) {
      HAL_GPIO_WritePin(MATRIX_LINE_GPIO_ROWS[i].port, MATRIX_LINE_GPIO_ROWS[i].pin, GPIO_PIN_RESET);
    } else {
      HAL_GPIO_WritePin(MATRIX_LINE_GPIO_ROWS[i].port, MATRIX_LINE_GPIO_ROWS[i].pin, GPIO_PIN_SET);
    }
  }

  // Scan columns of this row. Because the column pins are set to pull-up,
  // if the key of one column is pressed, its pin should be low (for the pin
  // of specified row is set to low), while other pins are default to high.
  Matrix_Line_Col col = MATRIX_LINE_C_EMPTY;

  for (uint8_t i = 0; i < MATRIX_N_COLS; ++i) {
    if (HAL_GPIO_ReadPin(MATRIX_LINE_GPIO_COLS[i].port, MATRIX_LINE_GPIO_COLS[i].pin) == GPIO_PIN_RESET) {
      col = (Matrix_Line_Col)i;
      break;
    }
  }

  /** @test */
  printf("Row %d | ", row);
  for (uint8_t i = 0; i < MATRIX_N_ROWS; ++i) {
    printf("%d ", HAL_GPIO_ReadPin(MATRIX_LINE_GPIO_ROWS[i].port, MATRIX_LINE_GPIO_ROWS[i].pin));
  }
  for (uint8_t i = 0; i < MATRIX_N_COLS; ++i) {
    printf("%d ", HAL_GPIO_ReadPin(MATRIX_LINE_GPIO_COLS[i].port, MATRIX_LINE_GPIO_COLS[i].pin));
  }
  printf("\n");

  return col;
}

Matrix_Key Matrix_Key_Scan() {
  Matrix_Key key = MATRIX_KEY_EMPTY;
  Matrix_Line_Col col;

  // Scan all rows.
  for (uint8_t i = 0; i < MATRIX_N_ROWS; ++i) {
    if ((col = __Matrix_Row_Scan(i)) != MATRIX_LINE_C_EMPTY) {
      // Column is not empty. The pressed key is on this row and column.
      key = MATRIX_LINE_KEY_MAP[i][col];
    }
  }

  return key;
}

void Matrix_Debug_Lines_Status(GPIO_PinState *states) {
  for (uint8_t i = 0; i < MATRIX_N_ROWS; ++i) {
    states[i] = HAL_GPIO_ReadPin(MATRIX_LINE_GPIO_ROWS[i].port, MATRIX_LINE_GPIO_ROWS[i].pin);
  }
  for (uint8_t i = 0; i < MATRIX_N_COLS; ++i) {
    states[i + MATRIX_N_ROWS] = HAL_GPIO_ReadPin(MATRIX_LINE_GPIO_COLS[i].port, MATRIX_LINE_GPIO_COLS[i].pin);
  }
}
