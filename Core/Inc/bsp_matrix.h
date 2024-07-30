#ifndef __BSP_MATRIX_H
#define __BSP_MATRIX_H

#include "main.h"
#include "stm32f407xx.h"

/*****************************
 * Matrix Keyboard line map:
 * Line 8 --- 1 2 3 A
 * Line 7 --- 4 5 6 B
 * Line 6 --- 7 8 9 C
 * Line 5 --- * 0 # D
 * Line 4 ----| | | |
 * Line 3 ------| | |
 * Line 2 --------| |
 * Line 1 ----------|
 ****************************/

typedef enum {
  MATRIX_KEY_OFF = 0,
  MATRIX_KEY_ON = 1
} Matrix_Key_Status;

typedef enum {
  MATRIX_KEY_0,
  MATRIX_KEY_1,
  MATRIX_KEY_2,
  MATRIX_KEY_3,
  MATRIX_KEY_4,
  MATRIX_KEY_5,
  MATRIX_KEY_6,
  MATRIX_KEY_7,
  MATRIX_KEY_8,
  MATRIX_KEY_9,
  MATRIX_KEY_STAR,  // *
  MATRIX_KEY_HASH,  // #
  MATRIX_KEY_A,
  MATRIX_KEY_B,
  MATRIX_KEY_C,
  MATRIX_KEY_D,
  MATRIX_KEY_EMPTY = 0xff
} Matrix_Key;

typedef enum {
  MATRIX_LINE_8,
  MATRIX_LINE_7,
  MATRIX_LINE_6,
  MATRIX_LINE_5
} Matrix_Line_Row;

typedef enum {
  MATRIX_LINE_4,
  MATRIX_LINE_3,
  MATRIX_LINE_2,
  MATRIX_LINE_1
} Matrix_Line_Col;

typedef struct {
  GPIO_TypeDef *port;
  uint16_t pin;
} Matrix_Line_GPIO_TypeDef;

Matrix_Key Matrix_Key_Scan();

#endif
