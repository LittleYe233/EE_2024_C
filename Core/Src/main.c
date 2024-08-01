/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "bsp_ad9959.h"
#include "bsp_matrix.h"
#include "myparamset.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// Amplifier coefs for 30-40MHz (11 steps).
const double CARRIER_AMP_AMPLIFIERS_CH1[11] = {
  8.54, 8.66, 8.54, 8.54, 8.66, 8.6,
  8.54, 8.54, 8.6, 8.6, 8.54
};
const double CARRIER_AMP_AMPLIFIERS_CH2[11] = {
  11.2, 10.67, 9.9, 9.31, 8.96, 8.31,
  8.01, 7.6, 7.25, 6.89, 6.6
};

char UART_Buffer[UART_Buffer_Len];
GPIO_PinState Matrix_Lines_Status[MATRIX_N_ROWS + MATRIX_N_COLS];
uint16_t ad9959_amps[4];

// Important parameters
SD_Type Param_sd_type;
uint16_t Param_carrier_amp;  // 100-1000 mV
uint16_t Param_carrier_freq;  // 30-40 MHz
uint16_t Param_mod_depth;  // 30-90 %
uint16_t Param_sm_amp_decay;  // 0-20 dB
uint16_t Param_sm_delay;  // 50-200 ns
uint16_t Param_sm_phase;  // 0-180 degree

uint8_t Debug_carrier_amp_max = 0;  // If the carrier amp should be set to max

DEBUG_Amp_Step_Ch Debug_amp_step_ch = DEBUG_AMP_STEP_CH1;
int8_t Debug_carrier_amp_amplifier_n_steps_ch1[11] = {0};
int8_t Debug_carrier_amp_amplifier_n_steps_ch2[11] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 10);
  return ch;
}

// Peripheral test function
void Taojingchi_Test();
void AD9959_Test();
Matrix_Key MatrixKeyboard_Test();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("Welcome to EE 2024 C!\n");

  AD9959_GPIO_Init();
  ParamSet_Init();

  Taojingchi_Test();
  // AD9959_Test();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Matrix_Key key = MatrixKeyboard_Test();
    ParamSet_Process(key);
    // Add delay to reduce output signal glitch
    HAL_Delay(25);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Taojingchi_Test() {
  sprintf(UART_Buffer, "main.sd_type.txt=\"AM\"\xff\xff\xff");
  printf("%s", UART_Buffer);
  printf("Welcome to EE 2024 C 2!\n");
  HAL_StatusTypeDef status = HAL_UART_Transmit(
      &huart2, (const uint8_t *)UART_Buffer, strlen(UART_Buffer), 1000);
  printf("%d\n", status);
}

void AD9959_Test() {
  AD9959_Set_Signal(0, 2000000, 0, 512);
  AD9959_Set_Signal(1, 40000000, 0, 1023);
  AD9959_Set_Signal(2, 40000000, 0, 1023);
  AD9959_Set_Signal(3, 2000000, 0, 512);
}

Matrix_Key MatrixKeyboard_Test() {
  Matrix_Key key = Matrix_Key_Scan();

  // printf("%d   ", key);

  if (key != MATRIX_KEY_EMPTY) {
    // Supress long press
    while (Matrix_Key_Scan() != MATRIX_KEY_EMPTY);
    // Print key
    switch (key) {
      case MATRIX_KEY_1:
        printf("1\n");
        break;
      case MATRIX_KEY_2:
        printf("2\n");
        break;
      case MATRIX_KEY_3:
        printf("3\n");
        break;
      case MATRIX_KEY_4:
        printf("4\n");
        break;
      case MATRIX_KEY_5:
        printf("5\n");
        break;
      case MATRIX_KEY_6:
        printf("6\n");
        break;
      case MATRIX_KEY_7:
        printf("7\n");
        break;
      case MATRIX_KEY_8:
        printf("8\n");
        break;
      case MATRIX_KEY_9:
        printf("9\n");
        break;
      case MATRIX_KEY_10:
        printf("10\n");
        break;
      case MATRIX_KEY_11:
        printf("11\n");
        break;
      case MATRIX_KEY_12:
        printf("12\n");
        break;
      case MATRIX_KEY_13:
        printf("13\n");
        break;
      case MATRIX_KEY_14:
        printf("14\n");
        break;
      case MATRIX_KEY_15:
        printf("15\n");
        break;
      case MATRIX_KEY_16:
        printf("16\n");
        break;
      case MATRIX_KEY_EMPTY:
        // No key
        break;
    }
  }

  return key;
}

void AD9959_UpdateParams() {
  uint16_t mod_signal_amp_n_1, mod_signal_amp_n_2;
  double sm_carrier_delay_to_degree, mod_signal_delay_to_degree;
  uint16_t carrier_amp_n_1, carrier_amp_n_2;

  if (Param_sd_type == SD_CW) {
    // CW wave, mod signal amplitude is the least
    mod_signal_amp_n_1 = AD9959_Min_Quantification;
    mod_signal_amp_n_2 = AD9959_Min_Quantification;
  } else {
    // DC offset
    double mod_signal_amp_1 = (double)Param_mod_depth / 100 * 188;
    double mod_signal_amp_2 = (double)Param_mod_depth / 100 * 180;
    // Max voltage is 250mV, not AD9959_Max_Voltage
    mod_signal_amp_n_1 = (uint16_t)(mod_signal_amp_1 / 250 * AD9959_Max_Quantification);
    mod_signal_amp_n_2 = (uint16_t)(mod_signal_amp_2 / 250 * AD9959_Max_Quantification);
  }

  // Amp decay
  double amp_decay_coef = pow(10, -(double)Param_sm_amp_decay / 20);

  if (Debug_carrier_amp_max) {
    carrier_amp_n_1 = AD9959_Max_Quantification;
    carrier_amp_n_2 = AD9959_Max_Quantification;
  } else {
    // Param_carrier_amp is RMS!!
    // Channel 1 (Sd) has an 8.7x amplifier, while Channel 2 (Sm) has an 8.2x amplifier.
    carrier_amp_n_1 = (uint16_t)(Param_carrier_amp * 1.414 / (CARRIER_AMP_AMPLIFIERS_CH1[Param_carrier_freq - 30] + Debug_carrier_amp_amplifier_n_steps_ch1[Param_carrier_freq - 30] * DEBUG_CARRIER_AMP_AMPLIFIER_STEP_CH1) / AD9959_Max_Voltage * AD9959_Max_Quantification);
    carrier_amp_n_2 = (uint16_t)(Param_carrier_amp * 1.414 / (CARRIER_AMP_AMPLIFIERS_CH2[Param_carrier_freq - 30] + Debug_carrier_amp_amplifier_n_steps_ch2[Param_carrier_freq - 30] * DEBUG_CARRIER_AMP_AMPLIFIER_STEP_CH2) / AD9959_Max_Voltage * AD9959_Max_Quantification * amp_decay_coef);
  }

  uint16_t sm_phase_n = Param_sm_phase;

  // Phase & Delay
  double carrier_period_ns = 1000.0 / Param_carrier_freq;
  double mod_signal_period_ns = 500;
  if (Param_sd_type == SD_CW) {
    sm_carrier_delay_to_degree = Param_sm_delay / carrier_period_ns * 360;
    mod_signal_delay_to_degree = Param_sm_delay / mod_signal_period_ns * 360;
  } else {
    sm_carrier_delay_to_degree = (Param_sm_delay - 30) / carrier_period_ns * 360;
    mod_signal_delay_to_degree = (Param_sm_delay - 30) / mod_signal_period_ns * 360;
  }
  uint16_t sm_phase_carrier_final = (uint16_t)(230 + sm_phase_n + sm_carrier_delay_to_degree) % 360;
  uint16_t sm_phase_mod_signal_final = (uint16_t)(230 + sm_phase_n + mod_signal_delay_to_degree) % 360;

  AD9959_Set_Signal(0, 2000000, sm_phase_mod_signal_final, mod_signal_amp_n_1);
  AD9959_Set_Signal(1, Param_carrier_freq * 1000000, sm_phase_carrier_final, carrier_amp_n_1);
  AD9959_Set_Signal(2, Param_carrier_freq * 1000000, 0, carrier_amp_n_2);
  AD9959_Set_Signal(3, 2000000, 0, (uint16_t)(mod_signal_amp_n_2 * amp_decay_coef));
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
