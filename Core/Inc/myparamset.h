/**
 * @file myparamset.h
 * @author LittleYe233 (littleye233@gmail.com)
 * @brief This file and its corresponding C file define functions to control DDS parameters from reactions of matrix keyboard.
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MYPARAMSET_H
#define __MYPARAMSET_H

#include "stm32f4xx_hal.h"
#include "bsp_matrix.h"

typedef enum {
  PARAMSET_STEP_MINUS,
  PARAMSET_STEP_ADD
} ParamSet_Step_Direction;

typedef struct {
  uint16_t min;
  uint16_t max;
  uint16_t step;
} ParamSet_StepInfo_TypeDef;

void ParamSet_Init();
void ParamSet_Process(Matrix_Key key);

#endif
