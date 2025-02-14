/**
 ********************************************************************************
 * @file    	pecontroller_pwm.c
 * @author 		Waqas Ehsan Butt
 * @date    	December 10, 2021
 *
 * @brief   
 ********************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 Taraz Technologies Pvt. Ltd.</center></h2>
 * <h3><center>All rights reserved.</center></h3>
 *
 * <center>This software component is licensed by Taraz Technologies under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the License. You may obtain 
 * a copy of the License at:
 *                        www.opensource.org/licenses/BSD-3-Clause</center>
 *
 ********************************************************************************
 */

/********************************************************************************
 * Includes
 *******************************************************************************/
#include "pecontroller_pwm1_10.c"
#include "pecontroller_pwm11_16.c"
#include "pecontroller_pwm.h"
/********************************************************************************
 * Defines
 *******************************************************************************/

/********************************************************************************
 * Typedefs
 *******************************************************************************/

/********************************************************************************
 * Structures
 *******************************************************************************/

/********************************************************************************
 * Static Variables
 *******************************************************************************/

/********************************************************************************
 * Global Variables
 *******************************************************************************/

/********************************************************************************
 * Function Prototypes
 *******************************************************************************/

/********************************************************************************
 * Code
 *******************************************************************************/
/**
 * @brief Activates a specific PWM Inverted pair
 * @param pwmNo Channel no of reference channel is the PWM pair (Valid Values 1-16). <br>
 * 				<b>Pairs are classified as :</b>
 * 				-# CH1 = Reference channel available at pin pwmNo
 * 				-# CH2 = Inverted Channel from reference available at pin pwmNo + 1 if pwmNo is odd else pwmNo - 1
 * @param en <c>true</c> if needs activation, else false
 */
void BSP_PWM_ActivateInvertedPair(uint32_t pwmNo, bool en)
{
	if (pwmNo <= 10)
		PWM1_10_ActivateInvertedPair(pwmNo, en);
}
/**
 * @brief Configures an PWM pair as inverted pair
 * @param pwmNo Channel no of reference channel is the PWM pair (Valid Values 1-16). <br>
 * 				<b>Pairs are classified as :</b>
 * 				-# CH1 = Reference channel available at pin pwmNo
 * 				-# CH2 = Inverted Channel from reference available at pin pwmNo + 1 if pwmNo is odd else pwmNo - 1
 * @param *config Pointer to a  pwm_config_t structure that contains the configuration
 * 				   parameters for the PWM pair
 * @return DutyCycleUpdateFnc Returns the function pointer of the type DutyCycleUpdateFnc which needs to be called
 * 						  whenever the duty cycles of the pair need to be updated
 */
DutyCycleUpdateFnc BSP_PWM_ConfigInvertedPair(uint16_t pwmNo, pwm_config_t *config)
{
	if (pwmNo <= 10)
		return BSP_PWM1_10_ConfigInvertedPairs(pwmNo, config, 1);
	else if (pwmNo <= 16)
		return BSP_PWM11_16_ConfigInvertedPairs(pwmNo, config, 1);
	return NULL;
}
/**
 * @brief Configures a PWM channel
 * @param pwmNo PWM channel to be configured (Valid Values 1-16)
 * @param *config Pointer to a  pwm_config_t structure that contains the configuration
 * 				   parameters for the PWM pair
 * @return DutyCycleUpdateFnc Returns the function pointer of the type DutyCycleUpdateFnc which needs to be called
 * 						  whenever the duty cycles of the pair need to be updated
 */
DutyCycleUpdateFnc BSP_PWM_ConfigChannel(uint16_t pwmNo, pwm_config_t *config)
{
	if (pwmNo <= 10)
		return BSP_PWM1_10_ConfigChannels(pwmNo, config, 1);
	else if (pwmNo <= 16)
		return BSP_PWM11_16_ConfigChannels(pwmNo, config, 1);
	return NULL;
}

/**
 * @brief Update the Duty Cycle of an Inverted Pair
 * @param pwmNo Channel no of reference channel is the PWM pair (Valid Values 1-16). <br>
 * 				<b>Pairs are classified as :</b>
 * 				-# CH1 = Reference channel available at pin pwmNo
 * 				-# CH2 = Inverted Channel from reference available at pin pwmNo + 1 if pwmNo is odd else pwmNo - 1
 * @param duty duty cycle to be applied to the pair (Range 0-1 or given in the config parameter)
 * @param *config Pointer to a  pwm_config_t structure that contains the configuration
 * 				   parameters for the PWM pair
 * @return float Duty cycle applied in this cycle. May differ from the duty variable if outside permitted limits
 */
float BSP_PWM_UpdatePairDuty(uint32_t pwmNo, float duty, pwm_config_t* config)
{
	if (pwmNo <= 10)
		return BSP_PWM1_10_UpdatePairDuty(pwmNo, duty, config);
	else if (pwmNo <= 16)
		return BSP_PWM11_16_UpdatePairDuty(pwmNo, duty, config);
	return 0;
}

/**
 * @brief Update the Duty Cycle of a channel
 * @param pwmNo PWM channel to be configured (Valid Values 1-16)
 * @param duty duty cycle to be applied to the channel (Range 0-1 or given in the config parameter)
 * @param *config Pointer to a  pwm_config_t structure that contains the configuration
 * 				   parameters for the PWM channel
 * @return float Duty cycle applied in this cycle. May differ from the duty variable if outside permitted limits
 */
float BSP_PWM_UpdateChannelDuty(uint32_t pwmNo, float duty, pwm_config_t* config)
{
	if (pwmNo <= 10)
		return BSP_PWM1_10_UpdateChannelDuty(pwmNo, duty, config);
	else if (pwmNo <= 16)
		return BSP_PWM11_16_UpdateChannelDuty(pwmNo, duty, config);
	return 0;
}

/**
 * @brief Enable / Disable interrupt for a PWM channel as per requirement
 * @param pwmNo Channel no of the PWM Channel (Range 1-16)
 * @param enable If enable interrupt set this parameter to <c>true</c>
 * @param callback Specifies the function to be called when the PWM is reset
 * @param priority Interrupt priority. Range (0-15). Here 0 is the highest priority
 */
void BSP_PWM_Config_Interrupt(uint32_t pwmNo, bool enable, PWMResetCallback callback, int priority)
{
	if (pwmNo <= 10)
		BSP_PWM1_10_Config_Interrupt(pwmNo, enable, callback, priority);
	else if (pwmNo <= 16)
		BSP_PWM11_16_Config_Interrupt(enable, callback, priority);
}
/**
 * @brief  Enables or disables the TIM Capture Compare Channel xN.
 * @param  TIMx to select the TIM peripheral
 * @param  Channel specifies the TIM Channel
 *          This parameter can be one of the following values:
 *            @arg TIM_CHANNEL_1: TIM Channel 1
 *            @arg TIM_CHANNEL_2: TIM Channel 2
 *            @arg TIM_CHANNEL_3: TIM Channel 3
 * @param  ChannelNState specifies the TIM Channel CCxNE bit new state.
 *          This parameter can be: TIM_CCxN_ENABLE or TIM_CCxN_Disable.
 * @retval None
 */
static void TIM_CCxNChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelNState)
{
	uint32_t tmp;

	tmp = TIM_CCER_CC1NE << (Channel & 0x1FU); /* 0x1FU = 31 bits max shift */

	/* Reset the CCxNE Bit */
	TIMx->CCER &=  ~tmp;

	/* Set or reset the CCxNE Bit */
	TIMx->CCER |= (uint32_t)(ChannelNState << (Channel & 0x1FU)); /* 0x1FU = 31 bits max shift */
}

/**
 * @brief Starts the PWM on required PWM pins. To enable outputs for required channels call BSP_PWMOut_Enable().
 * @code
 * // Start PWM for channel 1
 * BSP_PWM_Start(0x1, true);
 * // Start PWM for channel 1 and channel 2
 * BSP_PWM_Start(0x3, false);
 * // Start PWM for channel n and channel m, where n & m are between 1 & 16
 * BSP_PWM_Start((1U << (n - 1)) | (1U << (m - 1)), bool);
 * @endcode
 * @param pwmMask Set the PWM channels needed to be run.<br>
 * 				<b>Valid Range</b> =  (0x0001 - 0xffff)
 * @param masterHRTIM <c>true</c> if masterHRTIM to be enabled synchronously else <c>false</c>
 */
void BSP_PWM_Start(uint32_t pwmMask, bool masterHRTIM)
{
	uint32_t th_tim_sel =
			(pwmMask & 0x3 ? HRTIM_TIMERID_TIMER_A : 0) |
			(pwmMask & 0xc ? HRTIM_TIMERID_TIMER_B : 0) |
			(pwmMask & 0x30 ? HRTIM_TIMERID_TIMER_C : 0) |
			(pwmMask & 0xc0 ? HRTIM_TIMERID_TIMER_D : 0) |
			(pwmMask & 0x300 ? HRTIM_TIMERID_TIMER_E : 0) |
			(masterHRTIM ? HRTIM_TIMERID_MASTER : 0);

	// enable timer
	if ((pwmMask & 0xfc00) && (pwmMask & 0x2ff))
	{
		__HAL_TIM_MOE_ENABLE(&htim1);
		hhrtim.Instance->sMasterRegs.MCR |= (th_tim_sel);
		__HAL_TIM_ENABLE(&htim1);
	}
	else if (pwmMask & 0xfc00)
	{
		__HAL_TIM_MOE_ENABLE(&htim1);
		__HAL_TIM_ENABLE(&htim1);
	}
	else if (pwmMask & 0x2ff)
		hhrtim.Instance->sMasterRegs.MCR |= (th_tim_sel);

}
/**
 * @brief Stops the PWM on required PWM pins
 * @code
 * // Stop PWM for channel 1
 * BSP_PWM_Stop(0x1, false);
 * // Stop PWM for channel 1 and channel 2
 * BSP_PWM_Stop(0x3, false);
 * // Stop PWM for channel n and channel m, where n & m are between 1 & 16
 * BSP_PWM_Stop((1U << (n - 1)) | (1U << (m - 1)), bool);
 * @endcode
 * @param pwmMask Set the PWM channels needed to be stopped.<br>
 * 				<b>Valid Range</b> =  (0x0001 - 0xffff)
 * @param masterHRTIM <c>true</c> if masterHRTIM to be disabled synchronously else <c>false</c>
 */
void BSP_PWM_Stop(uint32_t pwmMask, bool masterHRTIM)
{
	if (pwmMask & 0x400)
		TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
	if (pwmMask & 0x800)
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCxN_DISABLE);
	if (pwmMask & 0x1000)
		TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
	if (pwmMask & 0x2000)
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCxN_DISABLE);
	if (pwmMask & 0x4000)
		TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCx_DISABLE);
	if (pwmMask & 0x8000)
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCxN_DISABLE);

	HAL_HRTIM_WaveformOutputStop(&hhrtim,
			(pwmMask & 0x1 ? HRTIM_OUTPUT_TA1 : 0) |
			(pwmMask & 0x2 ? HRTIM_OUTPUT_TA2 : 0) |
			(pwmMask & 0x4 ? HRTIM_OUTPUT_TB1 : 0) |
			(pwmMask & 0x8 ? HRTIM_OUTPUT_TB2 : 0) |
			(pwmMask & 0x10 ? HRTIM_OUTPUT_TC1 : 0) |
			(pwmMask & 0x20 ? HRTIM_OUTPUT_TC2 : 0) |
			(pwmMask & 0x40 ? HRTIM_OUTPUT_TD1 : 0) |
			(pwmMask & 0x80 ? HRTIM_OUTPUT_TD2 : 0) |
			(pwmMask & 0x100 ? HRTIM_OUTPUT_TE1 : 0) |
			(pwmMask & 0x200 ? HRTIM_OUTPUT_TE2 : 0));

	if (pwmMask & 0xfc00)
	{
		__HAL_TIM_MOE_DISABLE(&htim1);
		__HAL_TIM_DISABLE(&htim1);
	}
	else if (pwmMask & 0x2ff)
	{
		hhrtim.Instance->sMasterRegs.MCR &= ~
				((pwmMask & 0x3 ? HRTIM_TIMERID_TIMER_A : 0) |
						(pwmMask & 0xc ? HRTIM_TIMERID_TIMER_B : 0) |
						(pwmMask & 0x30 ? HRTIM_TIMERID_TIMER_C : 0) |
						(pwmMask & 0xc0 ? HRTIM_TIMERID_TIMER_D : 0) |
						(pwmMask & 0x300 ? HRTIM_TIMERID_TIMER_E : 0) |
						(masterHRTIM ? HRTIM_TIMERID_MASTER : 0));
	}
}

/**
 * @brief Populates the provided @ref pwm_module_config_t parameter with the default configuration
 * @details <b>Default Configuration</b>:
 * -# alignment = CENTER_ALIGNED
 * -# deadtime.on = false
 * -# deadtime.nanoSec = 1000
 * -# f = 25000Hz
 * @param moduleConfig module configuration to be updated
 */
void BSP_PWM_GetDafaultModuleConfig(pwm_module_config_t* moduleConfig)
{
	moduleConfig->alignment = CENTER_ALIGNED;
	moduleConfig->deadtime.on = false;
	moduleConfig->deadtime.nanoSec = 1000;
	moduleConfig->f = 25000;
}

/**
 * @brief Populates the provided @ref pwm_config_t parameter with the default configuration
 * @details <b>Default Configuration</b>:
 * -# dutyMode = OUTPUT_DUTY_AT_PWMH
 * -# lim.min = 0
 * -# lim.max = 1
 * -# lim.minMaxDutyCycleBalancing = false
 * -# slaveOpts = NULL
 * @param pwmConfig PWM configuration structure to be updated
 * @param moduleConfig module configuration used by this module. Make sure to call
 * @ref BSP_PWM_GetDafaultModuleConfig() before calling this function
 */
void BSP_PWM_GetDefaultConfig(pwm_config_t* pwmConfig, pwm_module_config_t* moduleConfig)
{
	pwmConfig->module = moduleConfig;
	pwmConfig->dutyMode = OUTPUT_DUTY_AT_PWMH;
	pwmConfig->lim.min = 0;
	pwmConfig->lim.max = 1;
	pwmConfig->lim.minMaxDutyCycleBalancing = false;
	pwmConfig->slaveOpts = NULL;
}
/**
 * @brief Enable / disable the output for required PWM channels
 * @code
 * // Enable PWM output for channel 1
 * BSP_PWMOut_Enable(0x1, true);
 * // Enable PWM output for channel 1 and channel 2
 * BSP_PWMOut_Enable(0x3, true);
 * // Disable PWM output for channel n and channel m, where n & m are between 1 & 16
 * BSP_PWMOut_Enable((1U << (n - 1)) | (1U << (m - 1)), false);
 * @endcode
 * @param pwmMask Set the PWM channels needed to be run.<br>
 * 				<b>Valid Range</b> =  (0x0001 - 0xffff)
 * @param en <c>true</c> if needs to be enabled else <c>false</c>
 */
void BSP_PWMOut_Enable(uint32_t pwmMask, bool en)
{
	if (en)
	{
		if (pwmMask & 0xC00)
		{TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_ENABLE);
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCxN_ENABLE);}
		if (pwmMask & 0x3000)
		{TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCx_ENABLE);
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCxN_ENABLE);}
		if (pwmMask & 0xC000)
		{TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCx_ENABLE);
		TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCxN_ENABLE);}

		HAL_HRTIM_WaveformOutputStart(&hhrtim,
				(pwmMask & 0x1 ? HRTIM_OUTPUT_TA1 : 0) |
				(pwmMask & 0x2 ? HRTIM_OUTPUT_TA2 : 0) |
				(pwmMask & 0x4 ? HRTIM_OUTPUT_TB1 : 0) |
				(pwmMask & 0x8 ? HRTIM_OUTPUT_TB2 : 0) |
				(pwmMask & 0x10 ? HRTIM_OUTPUT_TC1 : 0) |
				(pwmMask & 0x20 ? HRTIM_OUTPUT_TC2 : 0) |
				(pwmMask & 0x40 ? HRTIM_OUTPUT_TD1 : 0) |
				(pwmMask & 0x80 ? HRTIM_OUTPUT_TD2 : 0) |
				(pwmMask & 0x100 ? HRTIM_OUTPUT_TE1 : 0) |
				(pwmMask & 0x200 ? HRTIM_OUTPUT_TE2 : 0));
	}
	else
	{
		if (pwmMask & 0x400)
			TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCx_DISABLE);
		if (pwmMask & 0x800)
			TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_1, TIM_CCxN_DISABLE);
		if (pwmMask & 0x1000)
			TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCx_DISABLE);
		if (pwmMask & 0x2000)
			TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_2, TIM_CCxN_DISABLE);
		if (pwmMask & 0x4000)
			TIM_CCxChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCx_DISABLE);
		if (pwmMask & 0x8000)
			TIM_CCxNChannelCmd(htim1.Instance, TIM_CHANNEL_3, TIM_CCxN_DISABLE);

		HAL_HRTIM_WaveformOutputStop(&hhrtim,
				(pwmMask & 0x1 ? HRTIM_OUTPUT_TA1 : 0) |
				(pwmMask & 0x2 ? HRTIM_OUTPUT_TA2 : 0) |
				(pwmMask & 0x4 ? HRTIM_OUTPUT_TB1 : 0) |
				(pwmMask & 0x8 ? HRTIM_OUTPUT_TB2 : 0) |
				(pwmMask & 0x10 ? HRTIM_OUTPUT_TC1 : 0) |
				(pwmMask & 0x20 ? HRTIM_OUTPUT_TC2 : 0) |
				(pwmMask & 0x40 ? HRTIM_OUTPUT_TD1 : 0) |
				(pwmMask & 0x80 ? HRTIM_OUTPUT_TD2 : 0) |
				(pwmMask & 0x100 ? HRTIM_OUTPUT_TE1 : 0) |
				(pwmMask & 0x200 ? HRTIM_OUTPUT_TE2 : 0));
	}
}

/* EOF */
