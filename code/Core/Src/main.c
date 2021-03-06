/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>

// Servo
#include "Servo.h"

// LED screen
#include "lcd_menu.h"

// Pumps
#include "pumps.h"

// Distance sensor
#include "vl53l0x_api.h"

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
// Distance sensor
VL53L0X_RangingMeasurementData_t RangingData;
VL53L0X_Dev_t vl53l0x_c;
VL53L0X_DEV Dev = &vl53l0x_c;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  uint32_t refSpadCount;
  uint8_t isApertureSpads;
  uint8_t VhvSettings;
  uint8_t PhaseCal;
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
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM7_Init();
  MX_TIM3_Init();
  MX_TIM9_Init();
  /* USER CODE BEGIN 2 */

  // Init settings variables
  liquid1 = 50;
  liquid2 = 50;

  // Start servo's PWM
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
  servo_set_angle(0, 0);

  // Start encoder channels
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

  // Init of LCD and menu
  menu_init(8, 12);

  // Start pumps
  pumps_init();

  // Init VL53L0X
  Dev->I2cHandle = &hi2c1;
  Dev->I2cDevAddr = 0x52;
  HAL_NVIC_DisableIRQ(EXTI1_IRQn);
  VL53L0X_WaitDeviceBooted( Dev );
  VL53L0X_DataInit( Dev );
  VL53L0X_StaticInit( Dev );
  VL53L0X_PerformRefCalibration(Dev, &VhvSettings, &PhaseCal);
  VL53L0X_PerformRefSpadManagement(Dev, &refSpadCount, &isApertureSpads);
  VL53L0X_SetDeviceMode(Dev, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING);
  VL53L0X_SetInterMeasurementPeriodMilliSeconds(Dev, 200);
  VL53L0X_SetGpioConfig(Dev, TOF_EXTI_Pin, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING, VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_LOW, VL53L0X_INTERRUPTPOLARITY_LOW);
  VL53L0X_StartMeasurement(Dev);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    menu_update();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // Handle distance sensor interrupts
  if(GPIO_Pin == TOF_EXTI_Pin) {
    VL53L0X_GetRangingMeasurementData(Dev, &RangingData);
    VL53L0X_ClearInterruptMask(Dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
    distance_milimeters = RangingData.RangeMilliMeter;
  }

  // Handle encoder interrupts - debounce pressed encoder
  else if(GPIO_Pin == ENCDR_SW_Pin) {
    if(encoder_is_pressed == 0) {
      encoder_is_pressed = 1;
      HAL_TIM_Base_Start_IT(&htim7);
    }
  }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Handle pressed, debounced encoder
  if(htim->Instance == TIM7) {
    if(HAL_GPIO_ReadPin(ENCDR_SW_GPIO_Port, ENCDR_SW_Pin) == GPIO_PIN_RESET) {
      encoder_handle_click();
      encoder_is_pressed = 0;
      HAL_TIM_Base_Stop_IT(&htim7);
    }
  }
  // Measurement & pouring timer
  else if(htim->Instance == TIM3) {
    if(menu_state == MENU_STATE_MEASUREMENT)
      perform_cup_height_measurement();
    else if(menu_state == MENU_STATE_POURING)
      perform_pouring();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
