#include "myparamset.h"
#include "bsp_matrix.h"
#include "main.h"
#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

// Control which preset is used
// #define MYPARAMSET_PRESET_AD9959_ONLY  // Only provides AD9959 controllers
#define MYPARAMSET_PRESET_FULL  // Full controllers

#ifdef MYPARAMSET_PRESET_AD9959_ONLY

/** @todo */

#endif  /* End of MYPARAMSET_PRESET_AD9959_ONLY */

#ifdef MYPARAMSET_PRESET_FULL

/*************************************************************************
 * Key map (S4 at the left upper corner):
 * (Carrier Amp -)  (Carrier Amp +)   (Debug Amplifier Ch)  (Sd Type)
 * (Mod Depth -)    (Mod Depth +)     (Carrier Freq -)      (Carrier Freq +)
 * (Sm Amp Decay -) (Sm Amp Decay +)  (Debug Amplifier -)   (Debug Amplifier +)
 * (Sm Delay -)     (Sm Delay +)      (Sm Phase -)          (Sm Phase +)
 ************************************************************************/

const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_CARRIER_AMP = { 100, 1000, 100 };
const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_CARRIER_FREQ = { 30, 40, 1 };
const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_MOD_DEPTH = { 30, 90, 10 };
const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_SM_AMP_DECAY = { 0, 20, 2 };
const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_SM_DELAY = { 50, 200, 30 };
const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_SM_PHASE = { 0, 180, 30};
/** @test */
// const ParamSet_StepInfo_TypeDef PARAMSET_STEPINFO_SM_PHASE = { 0, 180, 10};

static void __ParamSet_SetParam(uint16_t *param, ParamSet_StepInfo_TypeDef info, ParamSet_Step_Direction dir) {
  if (dir == PARAMSET_STEP_MINUS) {
    if (info.min + info.step <= *param) {
      *param -= info.step;
    } else {
      *param = info.min;
    }
  } else if (dir == PARAMSET_STEP_ADD) {
    if (info.max - info.step >= *param) {
      *param += info.step;
    } else {
      *param = info.max;
    }
  }
}

static void __ParamSet_Sprint_SdType() {
  if (Param_sd_type == SD_CW) {
    sprintf(UART_Buffer, "main.sd_type.txt=\"CW\"\xff\xff\xff");
  } else {
    sprintf(UART_Buffer, "main.sd_type.txt=\"AM\"\xff\xff\xff");
  }
}

static void __ParamSet_Sprint_CarrierAmp() {
  sprintf(UART_Buffer, "main.carrier_amp.txt=\"%dmV\"\xff\xff\xff", Param_carrier_amp);
}

static void __ParamSet_Sprint_CarrierFreq() {
  sprintf(UART_Buffer, "main.carrier_freq.txt=\"%dMHz\"\xff\xff\xff", Param_carrier_freq);
}

static void __ParamSet_Sprint_ModDepth() {
  sprintf(UART_Buffer, "main.am_mod.txt=\"%d%%\"\xff\xff\xff", Param_mod_depth);
}

static void __ParamSet_Sprint_SmAmpDecay() {
  sprintf(UART_Buffer, "main.sm_amp_decay.txt=\"%ddB\"\xff\xff\xff", Param_sm_amp_decay);
}

static void __ParamSet_Sprint_SmDelay() {
  sprintf(UART_Buffer, "main.sm_delay.txt=\"%dns\"\xff\xff\xff", Param_sm_delay);
}

static void __ParamSet_Sprint_SmPhase() {
  sprintf(UART_Buffer, "main.sm_phase.txt=\"%d\"\xff\xff\xff", Param_sm_phase);
}

static void __ParamSet_Transmit() {
  HAL_UART_Transmit(&huart2, (const uint8_t *)UART_Buffer, strlen(UART_Buffer), 1000);
}

void ParamSet_Init() {
  Param_sd_type = SD_AM;
  Param_carrier_amp = 1000;
  Param_carrier_freq = 35;
  Param_mod_depth = 60;
  Param_sm_amp_decay = 0;
  Param_sm_delay = 50;
  Param_sm_phase = 0;

  __ParamSet_Sprint_SdType();
  __ParamSet_Transmit();
  __ParamSet_Sprint_CarrierAmp();
  __ParamSet_Transmit();
  __ParamSet_Sprint_CarrierFreq();
  __ParamSet_Transmit();
  __ParamSet_Sprint_ModDepth();
  __ParamSet_Transmit();
  __ParamSet_Sprint_SmAmpDecay();
  __ParamSet_Transmit();
  __ParamSet_Sprint_SmDelay();
  __ParamSet_Transmit();
  __ParamSet_Sprint_SmPhase();
  __ParamSet_Transmit();
}

void ParamSet_Process(Matrix_Key key) {
  uint8_t flag_need_uart_transmit = 1;

  switch (key) {
    // Row 1
    case MATRIX_KEY_4:
      __ParamSet_SetParam(&Param_carrier_amp, PARAMSET_STEPINFO_CARRIER_AMP, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_CarrierAmp();
      break;
    
    case MATRIX_KEY_8:
      __ParamSet_SetParam(&Param_carrier_amp, PARAMSET_STEPINFO_CARRIER_AMP, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_CarrierAmp();
      break;

    case MATRIX_KEY_12:
      if (Debug_amp_step_ch == DEBUG_AMP_STEP_CH1) {
        Debug_amp_step_ch = DEBUG_AMP_STEP_CH2;
      } else {
        Debug_amp_step_ch = DEBUG_AMP_STEP_CH1;
      }
      break;

    case MATRIX_KEY_16:
      if (Param_sd_type == SD_CW) {
        Param_sd_type = SD_AM;
      } else {
        Param_sd_type = SD_CW;
      }
      __ParamSet_Sprint_SdType();
      break;

    // Row 2
    case MATRIX_KEY_3:
      __ParamSet_SetParam(&Param_mod_depth, PARAMSET_STEPINFO_MOD_DEPTH, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_ModDepth();
      break;

    case MATRIX_KEY_7:
      __ParamSet_SetParam(&Param_mod_depth, PARAMSET_STEPINFO_MOD_DEPTH, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_ModDepth();
      break;

    case MATRIX_KEY_11:
      __ParamSet_SetParam(&Param_carrier_freq, PARAMSET_STEPINFO_CARRIER_FREQ, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_CarrierFreq();
      break;

    case MATRIX_KEY_15:
      __ParamSet_SetParam(&Param_carrier_freq, PARAMSET_STEPINFO_CARRIER_FREQ, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_CarrierFreq();
      break;

    // Row 3
    case MATRIX_KEY_2:
      __ParamSet_SetParam(&Param_sm_amp_decay, PARAMSET_STEPINFO_SM_AMP_DECAY, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_SmAmpDecay();
      break;

    case MATRIX_KEY_6:
      __ParamSet_SetParam(&Param_sm_amp_decay, PARAMSET_STEPINFO_SM_AMP_DECAY, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_SmAmpDecay();
      break;

    case MATRIX_KEY_10:
      if (Debug_amp_step_ch == DEBUG_AMP_STEP_CH1) {
        --Debug_carrier_amp_amplifier_n_steps_ch1[Param_carrier_freq - 30];
      } else {
        --Debug_carrier_amp_amplifier_n_steps_ch2[Param_carrier_freq - 30];
      }
      break;

    case MATRIX_KEY_14:
      if (Debug_amp_step_ch == DEBUG_AMP_STEP_CH1) {
        ++Debug_carrier_amp_amplifier_n_steps_ch1[Param_carrier_freq - 30];
      } else {
        ++Debug_carrier_amp_amplifier_n_steps_ch2[Param_carrier_freq - 30];
      }
      break;

    // Row 4
    case MATRIX_KEY_1:
      __ParamSet_SetParam(&Param_sm_delay, PARAMSET_STEPINFO_SM_DELAY, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_SmDelay();
      break;

    case MATRIX_KEY_5:
      __ParamSet_SetParam(&Param_sm_delay, PARAMSET_STEPINFO_SM_DELAY, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_SmDelay();
      break;

    case MATRIX_KEY_9:
      __ParamSet_SetParam(&Param_sm_phase, PARAMSET_STEPINFO_SM_PHASE, PARAMSET_STEP_MINUS);
      __ParamSet_Sprint_SmPhase();
      break;

    case MATRIX_KEY_13:
      __ParamSet_SetParam(&Param_sm_phase, PARAMSET_STEPINFO_SM_PHASE, PARAMSET_STEP_ADD);
      __ParamSet_Sprint_SmPhase();
      break;

    default:
      flag_need_uart_transmit = 0;
      break;
  }

  if (flag_need_uart_transmit) {
    __ParamSet_Transmit();
  }

  AD9959_UpdateParams();
}

#endif  /* End of MYPARAMSET_PRESET_FULL */
