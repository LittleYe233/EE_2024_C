#include "bsp_ad9959.h"

/**
 * @brief AD9959 simple delay function.
 * 
 * @param nns Delay parameter
 */
static void AD9959_Delay(uint32_t nns) {
  for (; nns != 0; --nns) {
    __NOP();
    __NOP();
    __NOP();
  }
}

/**
 * @brief AD9959 data IO update.
 * 
 */
static void AD9959_IO_Update() {
  AD9959_UD_l;
  AD9959_Delay(6);
  AD9959_UD_h;
  AD9959_Delay(12);
  AD9959_UD_l;
}

/**
 * @brief AD9959 write single word.
 * 
 * @param word Word
 */
static void AD9959_WriteWord(uint8_t word) {
  for (uint8_t i = 0; i < 8; ++i) {
    AD9959_CLK_l;
    if (0x80 == (word & 0x80)) {
      AD9959_SD0_h;
    } else {
      AD9959_SD0_l;
    }
    AD9959_CLK_h;
    word <<= 1;
  }
  AD9959_CLK_l;
}

/**
 * @brief AD9959 write data.
 *
 * @note This function is modified from the original example code.
 * 
 * @param reg Register
 * @param nData Number of data
 * @param data Data
 */
static void AD9959_WriteData(uint8_t reg, uint8_t nData, uint8_t *data) {
  AD9959_CLK_l;
  AD9959_CS_l;

  // Write control word
  AD9959_WriteWord(reg);

  // Write data
  for (uint8_t cnt = 0; cnt < nData; ++cnt) {
    AD9959_WriteWord(data[cnt]);
  }
  
  AD9959_CS_h;
}

/**
 * @brief AD9959 calculate frequency conversion word and store it.
 * 
 * @param freq Frequency
 * @param CFTW0_data Frequency conversion word
 */
static void AD9959_Get_CFTW0_Data(double freq, uint8_t *CFTW0_data) {
  double buff = 4294967296.0 / AD9959_System_Clk * freq;
  uint32_t value = (uint32_t)buff;

  CFTW0_data[0] = (uint8_t)(value >> 24);
  CFTW0_data[1] = (uint8_t)(value >> 16);
  CFTW0_data[2] = (uint8_t)(value >> 8);
  CFTW0_data[3] = (uint8_t)value;
}

/**
 * @brief AD9959 calculate phase conversion word and store it.
 * 
 * @param phase Phase
 * @param CP0W0_data Phase conversion word
 */
static void AD9959_Get_CPOW0_Data(uint16_t phase, uint8_t *CP0W0_data) {
  double buff = 16384.0 / 360 * phase;
  uint32_t value = (uint32_t)buff;

  CP0W0_data[0] = (uint8_t)(value >> 8);
  CP0W0_data[1] = (uint8_t)value;
}

/**
 * @brief AD9959 calculate amplitude conversion word and store it.
 * 
 * @param amp Amplitude
 * @param ACR_data Amplitude conversion word
 */
static void AD9959_Get_ACR_Data(uint16_t amp, uint8_t *ACR_data) {
  uint16_t value = amp & 0x03FF;

  ACR_data[0] = ACR_data[0];
  ACR_data[1] = (ACR_data[1] | (uint8_t)(value >> 8));
  ACR_data[2] = (uint8_t)value;
}

/**
 * @brief AD9959 enable channel selection.
 * 
 * @param ch Channel
 */
static void AD9959_Channel_Select_Enable(uint8_t ch) {
  uint8_t Ch_select[4] = { 0x10, 0x20, 0x40, 0x80 };

  AD9959_WriteData(CSR, 1, &Ch_select[ch]);
}

/**
 * @brief AD9959 GPIO initialization, with general initialization.
 *
 */
void AD9959_GPIO_Init() {
  AD9959_PDC_l;
  AD9959_Init();
}

/**
 * @brief AD9959 general initialization.
 *
 */
void AD9959_Init() {
  AD9959_CS_h;
  AD9959_CLK_l;
  AD9959_UD_l;
  AD9959_P0_l;
  AD9959_P1_l;
  AD9959_P2_l;
  AD9959_P3_l;

  AD9959_SD0_l;
  AD9959_SD1_l;
  AD9959_SD2_l;
  AD9959_SD3_l;

  AD9959_RST_l;
  AD9959_Delay(3);
  AD9959_RST_h;
  AD9959_Delay(500);
  AD9959_RST_l;
}

/**
 * @brief AD9959 set output signal parameters and enable output.
 * 
 * @param ch Channel
 * @param freq Frequency
 * @param phase Phase
 * @param amp Amplitude
 */
void AD9959_Set_Signal(uint8_t ch, double freq, uint16_t phase, uint16_t amp) {
  uint8_t CFTW0_Data[4];
  uint8_t CPOW0_Data[2];
  uint8_t ACR_Data[3] = {0x00, 0x10, 0x00};
  uint8_t CFR_Data[3] = {0x00, 0x23, 0x35};
  uint8_t FR1_Data[3] = {0xD0, 0x00, 0x00};

  AD9959_Channel_Select_Enable(ch);

  AD9959_WriteData(FR1, 3, FR1_Data);
  AD9959_WriteData(CFR, 3, CFR_Data);

  AD9959_Get_ACR_Data(amp, ACR_Data);
  AD9959_WriteData(ACR, 3, ACR_Data); // 写入幅度控制字

  AD9959_Get_CPOW0_Data(phase, CPOW0_Data);
  AD9959_WriteData(CPOW0, 2, CPOW0_Data); // 写入相位控制字

  AD9959_Get_CFTW0_Data(freq, CFTW0_Data);
  AD9959_WriteData(CFTW0, 4, CFTW0_Data); // 写入频率控制字

  AD9959_IO_Update();
}
