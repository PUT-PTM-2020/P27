/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f4xx_hal.h"
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
#define TOF_EXTI_Pin GPIO_PIN_1
#define TOF_EXTI_GPIO_Port GPIOA
#define TOF_EXTI_EXTI_IRQn EXTI1_IRQn
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define ENCDR_SIA_Pin GPIO_PIN_9
#define ENCDR_SIA_GPIO_Port GPIOE
#define ENCDR_SIB_Pin GPIO_PIN_11
#define ENCDR_SIB_GPIO_Port GPIOE
#define ENCDR_SW_Pin GPIO_PIN_12
#define ENCDR_SW_GPIO_Port GPIOB
#define ENCDR_SW_EXTI_IRQn EXTI15_10_IRQn
#define L293D_PWM_1_Pin GPIO_PIN_12
#define L293D_PWM_1_GPIO_Port GPIOD
#define L293D_PWM_2_Pin GPIO_PIN_13
#define L293D_PWM_2_GPIO_Port GPIOD
#define LCD_BL_Pin GPIO_PIN_7
#define LCD_BL_GPIO_Port GPIOC
#define LCD_DC_Pin GPIO_PIN_8
#define LCD_DC_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_9
#define LCD_RST_GPIO_Port GPIOA
#define TOF_XSHUT_Pin GPIO_PIN_10
#define TOF_XSHUT_GPIO_Port GPIOA
#define L293D_PUMP1_1_Pin GPIO_PIN_4
#define L293D_PUMP1_1_GPIO_Port GPIOB
#define L293D_PUMP1_2_Pin GPIO_PIN_5
#define L293D_PUMP1_2_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
