#ifndef __BSP_MATRIX_H
#define __BSP_MATRIX_H

#include "stm32f4xx_hal.h"

/*****************************
 * Matrix Keyboard line map:
 * Line (R1) --- 1  2  3  4
 * Line (R2) --- 5  6  7  8
 * Line (R3) --- 9  10 11 12
 * Line (R4) --- 13 14 15 16
 * Line (C1) ----|  |  |  |
 * Line (C2) -------|  |  |
 * Line (C3) ----------|  |
 * Line (C4) -------------|
 ****************************/

#define MATRIX_N_ROWS 4
#define MATRIX_N_COLS 4

typedef enum {
  MATRIX_KEY_1,
  MATRIX_KEY_2,
  MATRIX_KEY_3,
  MATRIX_KEY_4,
  MATRIX_KEY_5,
  MATRIX_KEY_6,
  MATRIX_KEY_7,
  MATRIX_KEY_8,
  MATRIX_KEY_9,
  MATRIX_KEY_10,
  MATRIX_KEY_11,
  MATRIX_KEY_12,
  MATRIX_KEY_13,
  MATRIX_KEY_14,
  MATRIX_KEY_15,
  MATRIX_KEY_16,
  MATRIX_KEY_EMPTY = 0xff
} Matrix_Key;

typedef enum {
  MATRIX_LINE_R1,
  MATRIX_LINE_R2,
  MATRIX_LINE_R3,
  MATRIX_LINE_R4,
  MATRIX_LINE_R_EMPTY = 0xff
} Matrix_Line_Row;

typedef enum {
  MATRIX_LINE_C1,
  MATRIX_LINE_C2,
  MATRIX_LINE_C3,
  MATRIX_LINE_C4,
  MATRIX_LINE_C_EMPTY = 0xff
} Matrix_Line_Col;

typedef struct {
  GPIO_TypeDef *port;
  uint16_t pin;
} Matrix_Line_GPIO_TypeDef;

Matrix_Key Matrix_Key_Scan();
void Matrix_Debug_Lines_Status(GPIO_PinState *states);

#endif
