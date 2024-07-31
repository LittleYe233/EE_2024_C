#ifndef __BSP_AD9959_H
#define __BSP_AD9959_H

#include "stm32f4xx_hal.h"
#include "main.h"

#define AD9959_Max_Voltage 240  // 240mV
#define AD9959_Max_Quantification 1023  // 1-1023
#define AD9959_Min_Quantification 1

#define AD9959_System_Clk 500000000 // AD9959工作频率设定为 500MHz

/***************通道寄存器地址宏定义***************/
#define CSR 0x00   /* 通道选择寄存器 */
#define FR1 0x01   /* 功能寄存器1 */
#define FR2 0x02   /* 功能寄存器2 */
#define CFR 0x03   /* 通道功能寄存器 */
#define CFTW0 0x04 /* 32位通道频率转换字寄存器 */
#define CPOW0 0x05 /* 14位通道相位转换字寄存器 */
#define ACR 0x06   /* 幅度控制寄存器 */
#define SRR 0x07   /* 线性扫描定时器 */
#define RDW 0x08   /* 线性向上扫描定时器 */
#define FDW 0x09   /* 线性向下扫描定时器 */

/***************引脚声明***************/
#define AD9959_P0_l HAL_GPIO_WritePin(AD9959_P0_GPIO_Port, AD9959_P0_Pin, GPIO_PIN_RESET)
#define AD9959_P0_h HAL_GPIO_WritePin(AD9959_P0_GPIO_Port, AD9959_P0_Pin, GPIO_PIN_SET)
#define AD9959_P0_t HAL_GPIO_TogglePin(AD9959_P0_GPIO_Port, AD9959_P0_Pin)
#define AD9959_P1_l HAL_GPIO_WritePin(AD9959_P1_GPIO_Port, AD9959_P1_Pin, GPIO_PIN_RESET)
#define AD9959_P1_h HAL_GPIO_WritePin(AD9959_P1_GPIO_Port, AD9959_P1_Pin, GPIO_PIN_SET)
#define AD9959_P1_t HAL_GPIO_TogglePin(AD9959_P1_GPIO_Port, AD9959_P1_Pin)
#define AD9959_P2_l HAL_GPIO_WritePin(AD9959_P2_GPIO_Port, AD9959_P2_Pin, GPIO_PIN_RESET)
#define AD9959_P2_h HAL_GPIO_WritePin(AD9959_P2_GPIO_Port, AD9959_P2_Pin, GPIO_PIN_SET)
#define AD9959_P2_t HAL_GPIO_TogglePin(AD9959_P2_GPIO_Port, AD9959_P2_Pin)
#define AD9959_P3_l HAL_GPIO_WritePin(AD9959_P3_GPIO_Port, AD9959_P3_Pin, GPIO_PIN_RESET)
#define AD9959_P3_h HAL_GPIO_WritePin(AD9959_P3_GPIO_Port, AD9959_P3_Pin, GPIO_PIN_SET)
#define AD9959_P3_t HAL_GPIO_TogglePin(AD9959_P3_GPIO_Port, AD9959_P3_Pin)

#define AD9959_CS_l HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin, GPIO_PIN_RESET)
#define AD9959_CS_h HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin, GPIO_PIN_SET)
#define AD9959_UD_l HAL_GPIO_WritePin(AD9959_UD_GPIO_Port, AD9959_UD_Pin, GPIO_PIN_RESET)
#define AD9959_UD_h HAL_GPIO_WritePin(AD9959_UD_GPIO_Port, AD9959_UD_Pin, GPIO_PIN_SET)
#define AD9959_CLK_l HAL_GPIO_WritePin(AD9959_CLK_GPIO_Port, AD9959_CLK_Pin, GPIO_PIN_RESET)
#define AD9959_CLK_h HAL_GPIO_WritePin(AD9959_CLK_GPIO_Port, AD9959_CLK_Pin, GPIO_PIN_SET)
#define AD9959_SD0_l HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin, GPIO_PIN_RESET)
#define AD9959_SD0_h HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin, GPIO_PIN_SET)
#define AD9959_SD1_l HAL_GPIO_WritePin(AD9959_SD1_GPIO_Port, AD9959_SD1_Pin, GPIO_PIN_RESET)
#define AD9959_SD1_h HAL_GPIO_WritePin(AD9959_SD1_GPIO_Port, AD9959_SD1_Pin, GPIO_PIN_SET)
#define AD9959_SD2_l HAL_GPIO_WritePin(AD9959_SD2_GPIO_Port, AD9959_SD2_Pin, GPIO_PIN_RESET)
#define AD9959_SD2_h HAL_GPIO_WritePin(AD9959_SD2_GPIO_Port, AD9959_SD2_Pin, GPIO_PIN_SET)
#define AD9959_SD3_l HAL_GPIO_WritePin(AD9959_SD3_GPIO_Port, AD9959_SD3_Pin, GPIO_PIN_RESET)
#define AD9959_SD3_h HAL_GPIO_WritePin(AD9959_SD3_GPIO_Port, AD9959_SD3_Pin, GPIO_PIN_SET)
#define AD9959_RST_l HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin, GPIO_PIN_RESET)
#define AD9959_RST_h HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin, GPIO_PIN_SET)

#define AD9959_PDC_l HAL_GPIO_WritePin(AD9959_PDC_GPIO_Port, AD9959_PDC_Pin, GPIO_PIN_RESET)
#define AD9959_PDC_h HAL_GPIO_WritePin(AD9959_PDC_GPIO_Port, AD9959_PDC_Pin, GPIO_PIN_SET)

/***************外部函数声明***************/
void AD9959_GPIO_Init();
void AD9959_Init();
void AD9959_Set_Signal(uint8_t ch, double freq, uint16_t phase, uint16_t amp);

#endif
