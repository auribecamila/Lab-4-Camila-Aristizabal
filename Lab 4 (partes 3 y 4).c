/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * LAB 4 CAMILA ARISTIZABAL 24367
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
uint8_t contador = 0;
uint8_t contadorRGB = 0;
uint8_t modo = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void mostrarContador(uint8_t valor)
{
    // Apagar todos los LEDs
    HAL_GPIO_WritePin(Led_1_GPIO_Port, Led_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Led_2_GPIO_Port, Led_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Led_3_GPIO_Port, Led_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, GPIO_PIN_RESET);

    // Encender solamente el LED correspondiente
    switch(valor)
    {
        case 1:
            HAL_GPIO_WritePin(Led_1_GPIO_Port, Led_1_Pin, GPIO_PIN_SET);
            break;

        case 2:
            HAL_GPIO_WritePin(Led_2_GPIO_Port, Led_2_Pin, GPIO_PIN_SET);
            break;

        case 4:
            HAL_GPIO_WritePin(Led_3_GPIO_Port, Led_3_Pin, GPIO_PIN_SET);
            break;

        case 8:
            HAL_GPIO_WritePin(Led_4_GPIO_Port, Led_4_Pin, GPIO_PIN_SET);
            break;

        case 0:
        default:
            // Todos permanecen apagados
            break;

    }
}
void mostrarRGB(uint8_t valor)
{
	 // Apagar los tres colores
	    HAL_GPIO_WritePin(RGB_Red_GPIO_Port, RGB_Red_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(RGB_Green_GPIO_Port, RGB_Green_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(RGB_Blue_GPIO_Port, RGB_Blue_Pin, GPIO_PIN_SET);

	    switch(valor)
	    {
	        case 0:
	            // 000 → Todo apagado
	            break;

	        case 1:
	            // 100 → Rojo
	            HAL_GPIO_WritePin(RGB_Red_GPIO_Port, RGB_Red_Pin, GPIO_PIN_RESET);
	            break;

	        case 2:
	            // 101 → Magenta
	            HAL_GPIO_WritePin(RGB_Red_GPIO_Port, RGB_Red_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(RGB_Blue_GPIO_Port, RGB_Blue_Pin, GPIO_PIN_RESET);
	            break;

	        case 3:
	            // 001 → Azul
	            HAL_GPIO_WritePin(RGB_Blue_GPIO_Port, RGB_Blue_Pin, GPIO_PIN_RESET);
	            break;

	        case 4:
	            // 011 → Cian
	            HAL_GPIO_WritePin(RGB_Green_GPIO_Port, RGB_Green_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(RGB_Blue_GPIO_Port, RGB_Blue_Pin, GPIO_PIN_RESET);
	            break;

	        case 5:
	            // 010 → Verde
	            HAL_GPIO_WritePin(RGB_Green_GPIO_Port, RGB_Green_Pin, GPIO_PIN_RESET);
	            break;

	        case 6:
	            // 110 → Amarillo
	            HAL_GPIO_WritePin(RGB_Red_GPIO_Port, RGB_Red_Pin, GPIO_PIN_RESET);
	            HAL_GPIO_WritePin(RGB_Green_GPIO_Port, RGB_Green_Pin, GPIO_PIN_RESET);
	            break;

	        default:
	            break;
	    }
	}

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // =========================================================
	     // BOTÓN 3: CAMBIAR DE MODO
	     // =========================================================

	     if (HAL_GPIO_ReadPin(Boton_3_GPIO_Port, Boton_3_Pin) == GPIO_PIN_SET)
	     {
	         modo = !modo;

	         // Actualizar indicador de modo
	         if (modo == 0)
	         {
	             // Modo contador de décadas
	             HAL_GPIO_WritePin(Led_Aparte_GPIO_Port,
	                               Led_Aparte_Pin,
	                               GPIO_PIN_RESET);

	             mostrarContador(contador);
	         }
	         else
	         {
	             // Modo RGB
	             HAL_GPIO_WritePin(Led_Aparte_GPIO_Port,
	                               Led_Aparte_Pin,
	                               GPIO_PIN_SET);

	             mostrarRGB(contadorRGB);
	         }

	         // Anti-rebote
	         HAL_Delay(200);
	     }


	     // =========================================================
	     // MODO 0: CONTADOR DE DÉCADAS
	     // =========================================================

	     if (modo == 0)
	     {
	         // -----------------------------------------------------
	         // BOTÓN 1: AUMENTAR CONTADOR
	         // -----------------------------------------------------

	         if (HAL_GPIO_ReadPin(Boton_1_GPIO_Port, Boton_1_Pin) == GPIO_PIN_SET)
	         {
	             if (contador == 0)
	             {
	                 contador = 1;
	             }
	             else if (contador == 1)
	             {
	                 contador = 2;
	             }
	             else if (contador == 2)
	             {
	                 contador = 4;
	             }
	             else if (contador == 4)
	             {
	                 contador = 8;
	             }
	             else if (contador == 8)
	             {
	                 contador = 0;
	             }

	             mostrarContador(contador);

	             // Anti-rebote
	             HAL_Delay(200);
	         }


	         // -----------------------------------------------------
	         // BOTÓN 2: DISMINUIR CONTADOR
	         // -----------------------------------------------------

	         if (HAL_GPIO_ReadPin(Boton_2_GPIO_Port, Boton_2_Pin) == GPIO_PIN_SET)
	         {
	             if (contador == 0)
	             {
	                 contador = 8;
	             }
	             else if (contador == 8)
	             {
	                 contador = 4;
	             }
	             else if (contador == 4)
	             {
	                 contador = 2;
	             }
	             else if (contador == 2)
	             {
	                 contador = 1;
	             }
	             else if (contador == 1)
	             {
	                 contador = 0;
	             }

	             mostrarContador(contador);

	             // Anti-rebote
	             HAL_Delay(200);
	         }
	     }


	     // =========================================================
	     // MODO 1: LED RGB
	     // =========================================================

	     else
	     {
	         // -----------------------------------------------------
	         // BOTÓN 1: AUMENTAR CONTADOR RGB
	         // -----------------------------------------------------

	         if (HAL_GPIO_ReadPin(Boton_1_GPIO_Port, Boton_1_Pin) == GPIO_PIN_SET)
	         {
	             // NO circular
	             if (contadorRGB < 6)
	             {
	                 contadorRGB++;
	             }

	             mostrarRGB(contadorRGB);

	             // Anti-rebote
	             HAL_Delay(200);
	         }


	         // -----------------------------------------------------
	         // BOTÓN 2: DISMINUIR CONTADOR RGB
	         // -----------------------------------------------------

	         if (HAL_GPIO_ReadPin(Boton_2_GPIO_Port, Boton_2_Pin) == GPIO_PIN_SET)
	         {
	             // NO circular
	             if (contadorRGB > 0)
	             {
	                 contadorRGB--;
	             }

	             mostrarRGB(contadorRGB);

	             // Anti-rebote
	             HAL_Delay(200);
	         }
	     }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Led_3_Pin|Led_2_Pin|RGB_Blue_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|RGB_Red_Pin|Led_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Led_1_Pin|Led_Aparte_Pin|RGB_Green_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_3_Pin Led_2_Pin RGB_Blue_Pin */
  GPIO_InitStruct.Pin = Led_3_Pin|Led_2_Pin|RGB_Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Boton_1_Pin Boton_2_Pin Boton_3_Pin */
  GPIO_InitStruct.Pin = Boton_1_Pin|Boton_2_Pin|Boton_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin RGB_Red_Pin Led_4_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|RGB_Red_Pin|Led_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_1_Pin Led_Aparte_Pin RGB_Green_Pin */
  GPIO_InitStruct.Pin = Led_1_Pin|Led_Aparte_Pin|RGB_Green_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
#ifdef USE_FULL_ASSERT
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
