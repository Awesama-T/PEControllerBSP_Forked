/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32h7xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define maxCS1_Pin GPIO_PIN_2
#define maxCS1_GPIO_Port GPIOE
#define maxCS2_Pin GPIO_PIN_3
#define maxCS2_GPIO_Port GPIOE
#define maxWrite_Pin GPIO_PIN_8
#define maxWrite_GPIO_Port GPIOI
#define maxRead_Pin GPIO_PIN_13
#define maxRead_GPIO_Port GPIOC
#define maxD0_Pin GPIO_PIN_0
#define maxD0_GPIO_Port GPIOF
#define maxD1_Pin GPIO_PIN_1
#define maxD1_GPIO_Port GPIOF
#define maxD2_Pin GPIO_PIN_2
#define maxD2_GPIO_Port GPIOF
#define maxD3_Pin GPIO_PIN_3
#define maxD3_GPIO_Port GPIOF
#define maxD4_Pin GPIO_PIN_4
#define maxD4_GPIO_Port GPIOF
#define maxD5_Pin GPIO_PIN_5
#define maxD5_GPIO_Port GPIOF
#define maxD6_Pin GPIO_PIN_6
#define maxD6_GPIO_Port GPIOF
#define maxD7_Pin GPIO_PIN_7
#define maxD7_GPIO_Port GPIOF
#define maxD8_Pin GPIO_PIN_8
#define maxD8_GPIO_Port GPIOF
#define maxD9_Pin GPIO_PIN_9
#define maxD9_GPIO_Port GPIOF
#define maxD10_Pin GPIO_PIN_10
#define maxD10_GPIO_Port GPIOF
#define CTP_I2C_SCL_Pin GPIO_PIN_4
#define CTP_I2C_SCL_GPIO_Port GPIOH
#define CTP_I2C_SDA_Pin GPIO_PIN_5
#define CTP_I2C_SDA_GPIO_Port GPIOH
#define CS1_Pin GPIO_PIN_2
#define CS1_GPIO_Port GPIOB
#define maxD11_Pin GPIO_PIN_11
#define maxD11_GPIO_Port GPIOF
#define maxD12_Pin GPIO_PIN_12
#define maxD12_GPIO_Port GPIOF
#define maxD13_Pin GPIO_PIN_13
#define maxD13_GPIO_Port GPIOF
#define maxD14_Pin GPIO_PIN_14
#define maxD14_GPIO_Port GPIOF
#define maxD15_Pin GPIO_PIN_15
#define maxD15_GPIO_Port GPIOF
#define CTP_INT_Pin GPIO_PIN_2
#define CTP_INT_GPIO_Port GPIOG
#define LCD_Disp_Pin GPIO_PIN_2
#define LCD_Disp_GPIO_Port GPIOI
#define CS2_Pin GPIO_PIN_15
#define CS2_GPIO_Port GPIOA
#define RD_Pin GPIO_PIN_10
#define RD_GPIO_Port GPIOC
#define VAL_Pin GPIO_PIN_11
#define VAL_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
