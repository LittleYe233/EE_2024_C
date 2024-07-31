/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define AD9959_SD2_Pin GPIO_PIN_9
#define AD9959_SD2_GPIO_Port GPIOF
#define AD9959_P2_Pin GPIO_PIN_0
#define AD9959_P2_GPIO_Port GPIOB
#define AD9959_UD_Pin GPIO_PIN_1
#define AD9959_UD_GPIO_Port GPIOB
#define AD9959_CS_Pin GPIO_PIN_11
#define AD9959_CS_GPIO_Port GPIOF
#define Key_Line_C4_Pin GPIO_PIN_0
#define Key_Line_C4_GPIO_Port GPIOG
#define Key_Line_R2_Pin GPIO_PIN_11
#define Key_Line_R2_GPIO_Port GPIOE
#define Key_Line_R3_Pin GPIO_PIN_13
#define Key_Line_R3_GPIO_Port GPIOE
#define Key_Line_R4_Pin GPIO_PIN_15
#define Key_Line_R4_GPIO_Port GPIOE
#define Key_Line_C1_Pin GPIO_PIN_11
#define Key_Line_C1_GPIO_Port GPIOD
#define Key_Line_R1_Pin GPIO_PIN_13
#define Key_Line_R1_GPIO_Port GPIOD
#define Key_Line_C3_Pin GPIO_PIN_2
#define Key_Line_C3_GPIO_Port GPIOG
#define Key_Line_C2_Pin GPIO_PIN_4
#define Key_Line_C2_GPIO_Port GPIOG
#define AD9959_SD3_Pin GPIO_PIN_8
#define AD9959_SD3_GPIO_Port GPIOG
#define AD9959_RST_Pin GPIO_PIN_8
#define AD9959_RST_GPIO_Port GPIOC
#define AD9959_PDC_Pin GPIO_PIN_11
#define AD9959_PDC_GPIO_Port GPIOC
#define AD9959_P1_Pin GPIO_PIN_4
#define AD9959_P1_GPIO_Port GPIOD
#define AD9959_SD0_Pin GPIO_PIN_9
#define AD9959_SD0_GPIO_Port GPIOG
#define AD9959_SD1_Pin GPIO_PIN_10
#define AD9959_SD1_GPIO_Port GPIOG
#define AD9959_CLK_Pin GPIO_PIN_15
#define AD9959_CLK_GPIO_Port GPIOG
#define AD9959_P0_Pin GPIO_PIN_9
#define AD9959_P0_GPIO_Port GPIOB
#define AD9959_P3_Pin GPIO_PIN_0
#define AD9959_P3_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
