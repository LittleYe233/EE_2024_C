#include "bsp_matrix.h"

const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_1 = { Key_Line1_GPIO_Port, Key_Line1_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_2 = { Key_Line2_GPIO_Port, Key_Line2_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_3 = { Key_Line3_GPIO_Port, Key_Line3_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_4 = { Key_Line4_GPIO_Port, Key_Line4_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_5 = { Key_Line5_GPIO_Port, Key_Line5_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_6 = { Key_Line6_GPIO_Port, Key_Line6_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_7 = { Key_Line7_GPIO_Port, Key_Line7_Pin };
const Matrix_Line_GPIO_TypeDef MATRIX_LINE_GPIO_8 = { Key_Line8_GPIO_Port, Key_Line8_Pin };

const Matrix_Key MATRIX_LINE_KEY_MAP[4][4] = {
  { MATRIX_KEY_1, MATRIX_KEY_2, MATRIX_KEY_3, MATRIX_KEY_A },
  { MATRIX_KEY_4, MATRIX_KEY_5, MATRIX_KEY_6, MATRIX_KEY_B },
  { MATRIX_KEY_7, MATRIX_KEY_8, MATRIX_KEY_9, MATRIX_KEY_C },
  { MATRIX_KEY_STAR, MATRIX_KEY_0, MATRIX_KEY_HASH, MATRIX_KEY_D }
};

static Matrix_Key_Status __Matrix_Line_Scan(Matrix_Line_GPIO_TypeDef line) {
  if (HAL_GPIO_ReadPin(line.port, line.pin) == MATRIX_KEY_ON) {
    return MATRIX_KEY_ON;
  } else {
    return MATRIX_KEY_OFF;
  }
}

static Matrix_Key __Matrix_Key_Detect() {
  Matrix_Line_Row row;
  Matrix_Line_Col col;

  if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_8)) {
    row = MATRIX_LINE_8;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_7)) {
    row = MATRIX_LINE_7;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_6)) {
    row = MATRIX_LINE_6;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_5)) {
    row = MATRIX_LINE_5;
  } else {
    // No key is pressed
    return MATRIX_KEY_EMPTY;
  }

  if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_4)) {
    col = MATRIX_LINE_4;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_3)) {
    col = MATRIX_LINE_3;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_2)) {
    col = MATRIX_LINE_2;
  } else if (__Matrix_Line_Scan(MATRIX_LINE_GPIO_1)) {
    col = MATRIX_LINE_1;
  } else {
    // No key is pressed
    return MATRIX_KEY_EMPTY;
  }

  return MATRIX_LINE_KEY_MAP[row][col];
}

Matrix_Key Matrix_Key_Scan() {
  Matrix_Key key;

  if ((key = __Matrix_Key_Detect()) != MATRIX_KEY_EMPTY) {
    // supress long press
    while (__Matrix_Key_Detect() != MATRIX_KEY_EMPTY);
  }

  return key;
}
