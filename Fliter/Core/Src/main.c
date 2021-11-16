/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "dma2d.h"
#include "ltdc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "stdio.h"
#include "stdarg.h"
#include "window.h"
#include "math.h"
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
axishander axis;
uint16_t sampleCplt = 0;
arm_rfft_fast_instance_f32 fftIns;

uint16_t adcBuf[2048];
float32_t fftIn[2048], fftOut[2048];
float32_t amplFreq[1024];
uint32_t freqDst[5];
float32_t amplDst[5], normalAmplDst[5];
float32_t THDx = 0.0;
float phase[5] = {};
float32_t RMS[5];
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_DMA2D_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

    WinInit(&axis, 0, 136, 23);
    LIB_RFFT_Init();
    LCD_Clear();
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adcBuf, 2048);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
        if (LIB_RFFT_Process()) {
            HAL_Delay(1000);
            HAL_ADC_Start_DMA(&hadc1, (uint32_t *) adcBuf, 2048);
            Packageup(fftIn, THDx, normalAmplDst);
        }

        /*TODO:*//*HAL_UART_*/
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
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
    if (&hadc1 == hadc) {
        sampleCplt = 1;
        for (int i = 0; i < fftIns.fftLenRFFT; ++i) {
            fftIn[i] = adcBuf[i] * 3.3 / 4096.0;
        }

/*        printf("hello\r\n");
        for (int i = 0; i < 2048; ++i) {
            printf("%d\r\n", adcBuf[i]);
        }*/
    }
}

void LIB_RFFT_Init() {
    arm_rfft_fast_init_f32(&fftIns, 2048);
    sampleCplt = 0;
    HAL_TIM_Base_Start(&htim3);
}

uint8_t LIB_RFFT_Process() {
    if (sampleCplt == 1) {
        uint32_t offset = 0;
        float32_t th;
        uint32_t domain;
        uint32_t limit;

        arm_rfft_fast_f32(&fftIns, fftIn, fftOut, 0);
        arm_cmplx_mag_f32(fftOut, amplFreq, fftIns.fftLenRFFT / 2);

        arm_max_f32(amplFreq + 1, fftIns.fftLenRFFT / 2 - 1, amplDst, freqDst);
        ++freqDst[0];
        phase[0] = atan2(fftOut[freqDst[0] * 2 + 1], fftOut[freqDst[0] * 2]);

        //flush
        amplFreq[0] = 0.0;
        th = amplDst[0] / 100.0;
        for (int i = 1; i < fftIns.fftLenRFFT / 2; ++i) {
            if (amplFreq[i] < th) {
                amplFreq[i] = 0.0;
            }
        }

        offset = sqrt(freqDst[0]);
        for (int i = 1; i < 5; ++i) {
            arm_max_f32(amplFreq + freqDst[0] * (i + 1) - offset,
                        offset * 2 + 1,
                        amplDst + i,
                        freqDst + i);
            freqDst[i] += freqDst[0] * (i + 1) - offset;
            phase[i] = atan2(fftOut[freqDst[i] * 2 + 1], fftOut[freqDst[i] * 2]);
        }

        //rms
        domain = freqDst[0] / 4;
        for (int i = 0; i < 4; ++i) {
            arm_power_f32(amplFreq + freqDst[i] - domain, domain * 2 + 1, RMS + i);
            RMS[i] = sqrt(RMS[i]);
            normalAmplDst[i] = RMS[i] / RMS[0];
        }
        limit = fftIns.fftLenRFFT / 2 - (freqDst[4] - domain) - 1;
        limit = limit < (domain * 2 + 1) ? limit : (2 * domain + 1);
        arm_power_f32(amplFreq + freqDst[4] - domain, limit, RMS + 4);
        RMS[4] = sqrt(RMS[4]);
        normalAmplDst[4] = RMS[4] / RMS[0];

        THDx = sqrt(pow(normalAmplDst[1], 2) + pow(normalAmplDst[2], 2) + pow(normalAmplDst[3], 2) + pow(normalAmplDst[4], 2));
        Painting(&axis, fftIn, freqDst, phase, THDx, normalAmplDst);
        sampleCplt = 0;
        return 1;
    }
    return 0;
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
    while (1) {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
