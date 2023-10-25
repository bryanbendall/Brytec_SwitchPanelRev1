/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define CanSilent_Pin GPIO_PIN_13
#define CanSilent_GPIO_Port GPIOC
#define Sw3_Pin GPIO_PIN_0
#define Sw3_GPIO_Port GPIOA
#define Sw5_Pin GPIO_PIN_1
#define Sw5_GPIO_Port GPIOA
#define Sw4_Pin GPIO_PIN_2
#define Sw4_GPIO_Port GPIOA
#define PowerSwitchStatus_Pin GPIO_PIN_3
#define PowerSwitchStatus_GPIO_Port GPIOA
#define Memory_Hold_Pin GPIO_PIN_4
#define Memory_Hold_GPIO_Port GPIOA
#define Memory_SS_Pin GPIO_PIN_4
#define Memory_SS_GPIO_Port GPIOC
#define Memory_Wp_Pin GPIO_PIN_0
#define Memory_Wp_GPIO_Port GPIOB
#define Sw1_Pin GPIO_PIN_14
#define Sw1_GPIO_Port GPIOB
#define Sw6_Pin GPIO_PIN_15
#define Sw6_GPIO_Port GPIOA
#define Sw7_Pin GPIO_PIN_10
#define Sw7_GPIO_Port GPIOC
#define Sw8_Pin GPIO_PIN_11
#define Sw8_GPIO_Port GPIOC
#define Sw2_Pin GPIO_PIN_4
#define Sw2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
