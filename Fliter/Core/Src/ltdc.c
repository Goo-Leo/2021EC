/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ltdc.h"

/* USER CODE BEGIN 0 */
static pFONT *LCD_Fonts;		// Ӣ������
struct
{
    uint32_t Color; 				//	LCD��ǰ������ɫ
    uint32_t BackColor;			//	����ɫ
    uint32_t ColorMode;			//	��ɫ��ʽ
    uint32_t LayerMemoryAdd;	//	���Դ��ַ
    uint8_t  BytesPerPixel;		//	ÿ��������ռ�ֽ���
    uint8_t  Layer; 				//	��ǰ��
    uint8_t  Direction;			//	��ʾ����
    uint8_t  ShowNum_Mode;		// ���ñ�����ʾʱ����λ��0���ǲ��ո�
}LCD;
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 43;
  hltdc.Init.AccumulatedVBP = 12;
  hltdc.Init.AccumulatedActiveW = 523;
  hltdc.Init.AccumulatedActiveH = 284;
  hltdc.Init.TotalWidth = 531;
  hltdc.Init.TotalHeigh = 292;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 272;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0xD0000000;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 272;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
    LCD_DisplayDirection(Direction_H); 	//	���ú�����ʾ
    LCD_SetFont(&Font24); 				 	//	����Ĭ������
    LCD_ShowNumMode(Fill_Space);			//	����������ʾĬ�����ո�

    LCD_SetLayer(0);  						// �л��� layer0
    LCD_SetBackColor(LCD_BLACK); 			//	���ñ���ɫ
    LCD_Clear(); 								//	������ˢ����ɫ
  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 180;
    PeriphClkInitStruct.PLLSAI.PLLSAIR = 6;
    PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PB1     ------> LTDC_R6
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PB1     ------> LTDC_R6
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11);

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void LCD_SetLayer(uint8_t layer) {
    LCD.LayerMemoryAdd = LCD_MemoryAdd;        // ��ȡ layer0 ���Դ��ַ
    LCD.ColorMode = ColorMode_0;      // ��ȡ layer0 ����ɫ��ʽ
    LCD.BytesPerPixel = BytesPerPixel_0;    // ��ȡ layer0 ��ÿ�����������ֽ����Ĵ�С
    LCD.Layer = 0;        // ��������Ϊ layer0

}
/***************************************************************************************************************
*	�� �� ��:	LCD_SetColor
*
*	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0xff0000FF ��ʾ��͸������ɫ��0xAA0000FF ��ʾ͸����Ϊ66.66%����ɫ
*
*	��������:	�˺�������������ʾ�ַ������㻭�ߡ���ͼ����ɫ
*
*	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
*					2. 32λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ A��R��G��B  4����ɫͨ��
*					3. ��8λ��͸��ͨ���У�ff��ʾ��͸����0��ʾ��ȫ͸��
*					4. ����ʹ��ARGB1555��ARGB8888��֧��͸��ɫ����ɫ��ʽ����Ȼ͸��ɫ�������ã�����ARGB1555��֧��һλ
*						͸��ɫ��������͸���Ͳ�͸������״̬��ARGB8888֧��255��͸����
*					5. ����˵����͸������ָ �����㡢layer0��layer1 ֮���͸��
*
***************************************************************************************************************/

void LCD_SetColor(uint32_t Color)
{
    uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ

    if( LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB565	)	//��32λɫת��Ϊ16λɫ
    {
        Red_Value   = (uint16_t)((Color&0x00F80000)>>8);
        Green_Value = (uint16_t)((Color&0x0000FC00)>>5);
        Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);
        LCD.Color = (uint16_t)(Red_Value | Green_Value | Blue_Value);
    }
    else if( LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB1555 )	//��32λɫת��ΪARGB1555��ɫ
    {
        if( (Color & 0xFF000000) == 0 )	//�ж��Ƿ�ʹ��͸��ɫ
            Alpha_Value = 0x0000;
        else
            Alpha_Value = 0x8000;

        Red_Value   = (uint16_t)((Color&0x00F80000)>>9);
        Green_Value = (uint16_t)((Color&0x0000F800)>>6);
        Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);
        LCD.Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else if( LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB4444 )	//��32λɫת��ΪARGB4444��ɫ
    {

        Alpha_Value = (uint16_t)((Color&0xf0000000)>>16);
        Red_Value   = (uint16_t)((Color&0x00F00000)>>12);
        Green_Value = (uint16_t)((Color&0x0000F000)>>8);
        Blue_Value  = (uint16_t)((Color&0x000000F8)>>4);
        LCD.Color = (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else
        LCD.Color = Color;	//24λɫ��32λɫ����Ҫת��
}

/***************************************************************************************************************
*	�� �� ��:	LCD_SetBackColor
*
*	��ڲ���:	Color - Ҫ��ʾ����ɫ��ʾ����0xff0000FF ��ʾ��͸������ɫ��0xAA0000FF ��ʾ͸����Ϊ66.66%����ɫ
*
*	��������:	���ñ���ɫ,�˺������������Լ���ʾ�ַ��ı���ɫ
*
*	˵    ��:	1. Ϊ�˷����û�ʹ���Զ�����ɫ����ڲ��� Color ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
*					2. 32λ����ɫ�У��Ӹ�λ����λ�ֱ��Ӧ A��R��G��B  4����ɫͨ��
*					3. ��8λ��͸��ͨ���У�ff��ʾ��͸����0��ʾ��ȫ͸��
*					4. ����ʹ��ARGB1555��ARGB8888��֧��͸��ɫ����ɫ��ʽ����Ȼ͸��ɫ�������ã�����ARGB1555��֧��һλ
*						͸��ɫ��������͸���Ͳ�͸������״̬��ARGB8888֧��255��͸����
*					5. ����˵����͸������ָ �����㡢layer0��layer1֮���͸��
*
***************************************************************************************************************/

void LCD_SetBackColor(uint32_t Color)
{
    uint16_t Alpha_Value = 0, Red_Value = 0, Green_Value = 0, Blue_Value = 0;  //������ɫͨ����ֵ

    if( LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB565	)	//��32λɫת��Ϊ16λɫ
    {
        Red_Value   	= (uint16_t)((Color&0x00F80000)>>8);
        Green_Value 	= (uint16_t)((Color&0x0000FC00)>>5);
        Blue_Value  	= (uint16_t)((Color&0x000000F8)>>3);
        LCD.BackColor	= (uint16_t)(Red_Value | Green_Value | Blue_Value);
    }
    else if( LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB1555 )	//��32λɫת��ΪARGB1555��ɫ
    {
        if( (Color & 0xFF000000) == 0 )	//�ж��Ƿ�ʹ��͸��ɫ
            Alpha_Value = 0x0000;
        else
            Alpha_Value = 0x8000;

        Red_Value   	= (uint16_t)((Color&0x00F80000)>>9);
        Green_Value 	= (uint16_t)((Color&0x0000F800)>>6);
        Blue_Value  	= (uint16_t)((Color&0x000000F8)>>3);
        LCD.BackColor 	= (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }
    else if( LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB4444 )	//��32λɫת��ΪARGB4444��ɫ
    {

        Alpha_Value 	= (uint16_t)((Color&0xf0000000)>>16);
        Red_Value   	= (uint16_t)((Color&0x00F00000)>>12);
        Green_Value 	= (uint16_t)((Color&0x0000F000)>>8);
        Blue_Value  	= (uint16_t)((Color&0x000000F8)>>4);
        LCD.BackColor 	= (uint16_t)(Alpha_Value | Red_Value | Green_Value | Blue_Value);
    }

    else
        LCD.BackColor = Color;	//24λɫ��32λɫ����Ҫת��

}

/***************************************************************************************************************
*	�� �� ��:	LCD_SetFont
*
*	��ڲ���:	*fonts - Ҫ���õ�ASCII����
*
*	��������:	����ASCII���壬��ѡ��ʹ�� 3216/2412/2010/1608/1206 ���ִ�С������
*
*	˵    ��:	1. ʹ��ʾ�� LCD_SetFont(&Font24) �������� 2412�� ASCII����
*					2. �����ģ����� lcd_fonts.c
*
***************************************************************************************************************/

void LCD_SetFont(pFONT *fonts)
{
    LCD_Fonts = fonts;
}

/***************************************************************************************************************
*	�� �� ��:	LCD_DisplayDirection
*
*	��ڲ���:	direction - Ҫ��ʾ�ķ���
*
*	��������:	����Ҫ��ʾ�ķ��򣬿�������� Direction_H ���������ʾ��Direction_V ������ֱ��ʾ
*
*	˵    ��:   ʹ��ʾ�� LCD_DisplayDirection(Direction_H) ����������Ļ������ʾ
*
***************************************************************************************************************/

void LCD_DisplayDirection(uint8_t direction)
{
    LCD.Direction = direction;
}

/***************************************************************************************************************
*	�� �� ��:	LCD_Clear
*
*	��������:	������������LCD���Ϊ LCD.BackColor ����ɫ��ʹ��DMA2Dʵ��
*
*	˵    ��:	���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
*
***************************************************************************************************************/

void LCD_Clear(void)
{

    DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	�Ĵ�����SDRAM
    DMA2D->OPFCCR	=	LCD.ColorMode;						//	������ɫ��ʽ
    DMA2D->OOR		=	0;										//	������ƫ��
    DMA2D->OMAR		=	LCD.LayerMemoryAdd ;				// ��ַ
    DMA2D->NLR		=	(LCD_Width<<16)|(LCD_Height);	//	�趨���ȺͿ��
    DMA2D->OCOLR	=	LCD.BackColor;						//	��ɫ

/******
�ȴ� ��ֱ����ʹ����ʾ״̬ ����LTDC����ˢ��һ�������ݵ�ʱ��
��Ϊ����Ļû��ˢ��һ֡ʱ����ˢ��������˺�ѵ�����
�û�Ҳ����ʹ�� �Ĵ��������ж� �����жϣ�����Ϊ�˱�֤���̵ļ���Լ���ֲ�ķ����ԣ�����ֱ��ʹ���жϼĴ����ķ���

��������жϣ�DMA2Dˢ���ٶ�����

��ɫ��ʽ	RGB565	 RGB888	 ARGB888
��ʱ	   1.2ms	    2.0ms	  2.7ms


����֮�󣬲������ָ�ʽ������Ҫ15.5msˢһ����������Ļ�����ˢ����ֻ��60֡��
15.5ms���ٶ��Ѿ��㹻�ˣ������Ƕ��ٶ�Ҫ���ر�ߵĳ��ϣ���Ȼ��������жϴ�ֱ�ȴ�����䣬���Ա���˺��ЧӦ

******/
    while( LTDC->CDSR != 0X00000001);	// �ж� ��ʾ״̬�Ĵ���LTDC_CDSR �ĵ�0λ VDES����ֱ����ʹ����ʾ״̬

    DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;				//	�ȴ��������

}

/***************************************************************************************************************
*	�� �� ��:	LCD_ClearRect
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					width  - Ҫ�������ĺ��򳤶�
*					height - Ҫ��������������
*
*	��������:	�ֲ�������������ָ��λ�ö�Ӧ���������Ϊ LCD.BackColor ����ɫ
*
*	˵    ��:	1. ���� LCD_SetBackColor() ����Ҫ����ı���ɫ���ٵ��øú�����������
*					2. ʹ��ʾ�� LCD_ClearRect( 10, 10, 100, 50) ���������(10,10)��ʼ�ĳ�100��50������
*
***************************************************************************************************************/

void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

    DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	�Ĵ�����SDRAM
    DMA2D->OPFCCR	=	LCD.ColorMode;						//	������ɫ��ʽ
    DMA2D->OCOLR	=	LCD.BackColor ;					//	��ɫ

    if(LCD.Direction == Direction_H)  //�������
    {
        DMA2D->OOR		=	LCD_Width - width;				//	������ƫ��
        DMA2D->OMAR		=	LCD.LayerMemoryAdd + LCD.BytesPerPixel*(LCD_Width * y + x);	// ��ַ;
        DMA2D->NLR		=	(width<<16)|(height);			//	�趨���ȺͿ��
    }
    else	//�������
    {
        DMA2D->OOR		=	LCD_Width - height;		//	������ƫ��
        DMA2D->OMAR		=	LCD.LayerMemoryAdd + LCD.BytesPerPixel*((LCD_Height - x - 1 - width)*LCD_Width + y);	// ��ַ
        DMA2D->NLR		=	(width)|(height<<16);	//	�趨���ȺͿ��
    }

    DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;			//	�ȴ��������

}


/***************************************************************************************************************
*	�� �� ��:	LCD_DrawPoint
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					color  - Ҫ���Ƶ���ɫ��ʹ��32λ����ɫ��ʽ���û����������ɫ��ʽ��ת��
*
*	��������:	��ָ���������ָ����ɫ�ĵ�
*
*	˵    ��:	1. ֱ���ڶ�Ӧ���Դ�λ��д����ɫֵ������ʵ�ֻ���Ĺ���
*					2. ʹ��ʾ�� LCD_DrawPoint( 10, 10, 0xff0000FF) ��������(10,10)������ɫ�ĵ�
*
***************************************************************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color)
{

/*----------------------- 32λɫ ARGB8888 ģʽ ----------------------*/

    if( LCD.ColorMode == LTDC_PIXEL_FORMAT_ARGB8888 )
    {
        if (LCD.Direction == Direction_H) //ˮƽ����
        {
            *(__IO uint32_t*)( LCD.LayerMemoryAdd + 4*(x + y*LCD_Width) ) = color ;
        }
        else if(LCD.Direction == Direction_V)	//��ֱ����
        {
            *(__IO uint32_t*)( LCD.LayerMemoryAdd + 4*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
        }
    }
/*----------------------------- 24λɫ RGB888 ģʽ -------------------------*/

    else if ( LCD.ColorMode == LTDC_PIXEL_FORMAT_RGB888 )
    {
        if (LCD.Direction == Direction_H) //ˮƽ����
        {
            *(__IO uint16_t*)( LCD.LayerMemoryAdd + 3*(x + y*LCD_Width) ) = color ;
            *(__IO uint8_t*)( LCD.LayerMemoryAdd + 3*(x + y*LCD_Width) + 2 ) = color>>16 ;
        }
        else if(LCD.Direction == Direction_V)	//��ֱ����
        {
            *(__IO uint16_t*)( LCD.LayerMemoryAdd + 3*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
            *(__IO uint8_t*)( LCD.LayerMemoryAdd + 3*((LCD_Height - x - 1)*LCD_Width + y) +2) = color>>16 ;
        }
    }

/*----------------------- 16λɫ ARGB1555��RGB565����ARGB4444 ģʽ ----------------------*/
    else
    {
        if (LCD.Direction == Direction_H) //ˮƽ����
        {
            *(__IO uint16_t*)( LCD.LayerMemoryAdd + 2*(x + y*LCD_Width) ) = color ;
        }
        else if(LCD.Direction == Direction_V)	//��ֱ����
        {
            *(__IO uint16_t*)( LCD.LayerMemoryAdd + 2*((LCD_Height - x - 1)*LCD_Width + y) ) = color ;
        }
    }
}



/***************************************************************************************************************
*	�� �� ��:	LCD_DisplayChar
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					c  - ASCII�ַ�
*
*	��������:	��ָ��������ʾָ�����ַ�
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetFont(&Font24) ����Ϊ 2412��ASCII����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayChar( 10, 10, 'a') ��������(10,10)��ʾ�ַ� 'a'
*
***************************************************************************************************************/

void LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c)
{
    uint16_t  index = 0, counter = 0;		// ��������
    uint8_t   disChar;		//�洢�ַ��ĵ�ַ
    uint16_t  Xaddress = x; //ˮƽ����

    c = c - 32; 	// ����ASCII�ַ���ƫ��

    for(index = 0; index < LCD_Fonts->Sizes; index++)
    {
        disChar = LCD_Fonts->pTable[c*LCD_Fonts->Sizes + index]; //��ȡ�ַ���ģֵ
        for(counter = 0; counter < 8; counter++)
        {
            if(disChar & 0x01)
            {
                LCD_DrawPoint(Xaddress,y,LCD.Color);		//��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
            }
            else
            {
                LCD_DrawPoint(Xaddress,y,LCD.BackColor);	//����ʹ�ñ���ɫ���Ƶ�
            }
            disChar >>= 1;
            Xaddress++;  //ˮƽ�����Լ�

            if( (Xaddress - x)==LCD_Fonts->Width ) //���ˮƽ����ﵽ���ַ���ȣ����˳���ǰѭ��
            {													//������һ�еĻ���
                Xaddress = x;
                y++;
                break;
            }
        }
    }
}

/***************************************************************************************************************
*	�� �� ��:	LCD_DisplayString
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					p - ASCII�ַ������׵�ַ
*
*	��������:	��ָ��������ʾָ�����ַ���
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetFont(&Font24) ����Ϊ 2412��ASCII����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayString( 10, 10, "FANKE") ������ʼ����Ϊ(10,10)�ĵط���ʾ�ַ���"FANKE"
*
***************************************************************************************************************/

void LCD_DisplayString( uint16_t x, uint16_t y, char *p)
{
    while ((x < LCD_Width) && (*p != 0))	//�ж���ʾ�����Ƿ񳬳���ʾ�������ַ��Ƿ�Ϊ���ַ�
    {
        LCD_DisplayChar( x,y,*p);
        x += LCD_Fonts->Width; //��ʾ��һ���ַ�
        p++;	//ȡ��һ���ַ���ַ
    }
}

/***************************************************************************************************************
*	�� �� ��:	LCD_SetTextFont
*
*	��ڲ���:	*fonts - Ҫ���õ��ı�����
*
*	��������:	�����ı����壬�������ĺ�ASCII�ַ���
*
*	˵    ��:	1. ��ѡ��ʹ�� 3232/2424/2020/1616/1212 ���ִ�С���������壬
*						���Ҷ�Ӧ������ASCII����Ϊ 3216/2412/2010/1608/1206
*					2. �����ģ����� lcd_fonts.c
*					3. �����ֿ�ʹ�õ���С�ֿ⣬���õ��˶�Ӧ�ĺ�����ȥȡģ
*					4. ʹ��ʾ�� LCD_SetTextFont(&CH_Font24) �������� 2424�����������Լ�2412��ASCII�ַ�����
*
***************************************************************************************************************/

void LCD_SetTextFont(pFONT *fonts)
{
    switch(fonts->Width )
    {
        case 12:	LCD_Fonts = &Font12;	break;	// ����ASCII�ַ�������Ϊ 1206
        case 16:	LCD_Fonts = &Font16;	break;	// ����ASCII�ַ�������Ϊ 1608
        case 20:	LCD_Fonts = &Font20;	break;	// ����ASCII�ַ�������Ϊ 2010
        case 24:	LCD_Fonts = &Font24;	break;	// ����ASCII�ַ�������Ϊ 2412
        case 32:	LCD_Fonts = &Font32;	break;	// ����ASCII�ַ�������Ϊ 3216
        default: break;
    }

}


/***************************************************************************************************************
*	�� �� ��:	LCD_DisplayText
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					pText - �ַ�����������ʾ���Ļ���ASCII�ַ�
*
*	��������:	��ָ��������ʾָ�����ַ���
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayChinese( 10, 10, "���ͿƼ�STM32") ��������(10,10)��ʾ�ַ���"���ͿƼ�STM32"
*
***************************************************************************************************************/

void LCD_DisplayText(uint16_t x, uint16_t y, char *pText)
{

    while(*pText != 0)	// �ж��Ƿ�Ϊ���ַ�
    {
        if(*pText<=0x7F)	// �ж��Ƿ�ΪASCII��
        {
            LCD_DisplayChar(x,y,*pText);	// ��ʾASCII
            x+=LCD_Fonts->Width;				// ˮƽ���������һ���ַ���
            pText++;								// �ַ�����ַ+1
        }
    }
}


/***************************************************************************************************************
*	�� �� ��:	LCD_ShowNumMode
*
*	��ڲ���:	mode - ���ñ�������ʾģʽ
*
*	��������:	���ñ�����ʾʱ����λ��0���ǲ��ո񣬿�������� Fill_Space ���ո�Fill_Zero �����
*
*	˵    ��:   1. ֻ�� LCD_DisplayNumber() ��ʾ���� �� LCD_DisplayDecimals()��ʾС�� �����������õ�
*					2. ʹ��ʾ�� LCD_ShowNumMode(Fill_Zero) ���ö���λ���0������ 123 ������ʾΪ 000123
*
***************************************************************************************************************/

void LCD_ShowNumMode(uint8_t mode)
{
    LCD.ShowNum_Mode = mode;
}

/*****************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayNumber
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					number - Ҫ��ʾ������,��Χ�� -2147483648~2147483647 ֮��
*					len - ���ֵ�λ�������λ������len��������ʵ�ʳ�������������������š��������Ҫ��ʾ��������Ԥ��һ��λ�ķ�����ʾ�ռ�
*
*	��������:	��ָ��������ʾָ������������
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayNumber( 10, 10, a, 5) ��������(10,10)��ʾָ������a,�ܹ�5λ������λ��0��ո�
*						���� a=123 ʱ������� LCD_ShowNumMode()����������ʾ  123(ǰ�������ո�λ) ����00123
*
*****************************************************************************************************************************************/

void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number, uint8_t len)
{
    char   Number_Buffer[15];				// ���ڴ洢ת������ַ���

    if( LCD.ShowNum_Mode == Fill_Zero)	// ����λ��0
    {
        sprintf( Number_Buffer , "%0.*d",len, number );	// �� number ת�����ַ�����������ʾ
    }
    else			// ����λ���ո�
    {
        sprintf( Number_Buffer , "%*d",len, number );	// �� number ת�����ַ�����������ʾ
    }

    LCD_DisplayString( x, y,(char *)Number_Buffer) ;  // ��ת���õ����ַ�����ʾ����

}

/***************************************************************************************************************************************
*	�� �� ��:	LCD_DisplayDecimals
*
*	��ڲ���:	x - ��ʼˮƽ���꣬ȡֵ��Χ0~479
*					y - ��ʼ��ֱ���꣬ȡֵ��Χ0~271
*					decimals - Ҫ��ʾ������, double��ȡֵ1.7 x 10^��-308��~ 1.7 x 10^��+308����������ȷ��׼ȷ����Чλ��Ϊ15~16λ
*
*       			len - ������������λ��������С����͸��ţ�����ʵ�ʵ���λ��������ָ������λ��������ʵ�ʵ��ܳ���λ�����
*							ʾ��1��С�� -123.123 ��ָ�� len <=8 �Ļ�����ʵ���ճ���� -123.123
*							ʾ��2��С�� -123.123 ��ָ�� len =10 �Ļ�����ʵ�����   -123.123(����ǰ����������ո�λ)
*							ʾ��3��С�� -123.123 ��ָ�� len =10 �Ļ��������ú��� LCD_ShowNumMode() ����Ϊ���0ģʽʱ��ʵ����� -00123.123
*
*					decs - Ҫ������С��λ������С����ʵ��λ��������ָ����С��λ����ָ���Ŀ�������������
*							 ʾ����1.12345 ��ָ�� decs Ϊ4λ�Ļ�����������Ϊ1.1235
*
*	��������:	��ָ��������ʾָ���ı���������С��
*
*	˵    ��:	1. ������Ҫ��ʾ�����壬����ʹ�� LCD_SetTextFont(&CH_Font24) ����Ϊ 2424�����������Լ�2412��ASCII�ַ�����
*					2.	������Ҫ��ʾ����ɫ������ʹ�� LCD_SetColor(0xff0000FF) ����Ϊ��ɫ
*					3. �����ö�Ӧ�ı���ɫ������ʹ�� LCD_SetBackColor(0xff000000) ����Ϊ��ɫ�ı���ɫ
*					4. ʹ��ʾ�� LCD_DisplayDecimals( 10, 10, a, 5, 3) ��������(10,10)��ʾ�ֱ���a,�ܳ���Ϊ5λ�����б���3λС��
*
*****************************************************************************************************************************************/

void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double decimals, uint8_t len, uint8_t decs)
{
    char  Number_Buffer[20];				// ���ڴ洢ת������ַ���

    if( LCD.ShowNum_Mode == Fill_Zero)	// ����λ���0ģʽ
    {
        sprintf( Number_Buffer , "%0*.*lf",len,decs, decimals );	// �� number ת�����ַ�����������ʾ
    }
    else		// ����λ���ո�
    {
        sprintf( Number_Buffer , "%*.*lf",len,decs, decimals );	// �� number ת�����ַ�����������ʾ
    }

    LCD_DisplayString( x, y,(char *)Number_Buffer) ;	// ��ת���õ����ַ�����ʾ����
}


/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawImage
*
*	��ڲ���: x - ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 width  - ͼƬ��ˮƽ��ȣ����ȡֵ480
*				 height - ͼƬ�Ĵ�ֱ��ȣ����ȡֵ272
*				*pImage - ͼƬ���ݴ洢�����׵�ַ
*
*	��������: ��ָ�����괦��ʾͼƬ
*
*	˵    ��: Ҫ��ʾ��ͼƬ��Ҫ���Ƚ���ȡģ����ֻ����ʾһ����ɫ��ʹ�� LCD_SetColor() �������û���ɫ
*
*****************************************************************************************************************************************/

void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)
{
    uint8_t   disChar;	//��ģ��ֵ
    uint16_t  Xaddress = x; //ˮƽ����
    uint16_t  i=0,j=0,m=0;

    for(i = 0; i <height; i++)
    {
        for(j = 0; j <(float)width/8; j++)
        {
            disChar = *pImage;

            for(m = 0; m < 8; m++)
            {
                if(disChar & 0x01)
                {
                    LCD_DrawPoint(Xaddress,y,LCD.Color);	//��ǰģֵ��Ϊ0ʱ��ʹ�û���ɫ���
                }
                else
                {
                    LCD_DrawPoint(Xaddress,y,LCD.BackColor);	//����ʹ�ñ���ɫ���Ƶ�
                }
                disChar >>= 1;
                Xaddress++;  //ˮƽ�����Լ�

                if( (Xaddress - x)==width ) //���ˮƽ����ﵽ���ַ���ȣ����˳���ǰѭ��
                {													//������һ�еĻ���
                    Xaddress = x;
                    y++;
                    break;
                }
            }
            pImage++;
        }
    }
}
/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawLine
*
*	��ڲ���: x1 - ��� ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y1 - ��� ��ֱ���꣬ȡֵ��Χ 0~271
*
*				 x2 - �յ� ˮƽ���꣬ȡֵ��Χ 0~479
*            y2 - �յ� ��ֱ���꣬ȡֵ��Χ 0~271
*
*	��������: ������֮�仭��
*
*	˵    ��: �ú�����ֲ��ST�ٷ������������
*
*****************************************************************************************************************************************/

#define ABS(X)  ((X) > 0 ? (X) : -(X))

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
            yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
            curpixel = 0;

    deltax = ABS(x2 - x1);        /* The difference between the x's */
    deltay = ABS(y2 - y1);        /* The difference between the y's */
    x = x1;                       /* Start x off at the first pixel */
    y = y1;                       /* Start y off at the first pixel */

    if (x2 >= x1)                 /* The x-values are increasing */
    {
        xinc1 = 1;
        xinc2 = 1;
    }
    else                          /* The x-values are decreasing */
    {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1)                 /* The y-values are increasing */
    {
        yinc1 = 1;
        yinc2 = 1;
    }
    else                          /* The y-values are decreasing */
    {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay)         /* There is at least one x-value for every y-value */
    {
        xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
        yinc2 = 0;                  /* Don't change the y for every iteration */
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;         /* There are more x-values than y-values */
    }
    else                          /* There is at least one y-value for every x-value */
    {
        xinc2 = 0;                  /* Don't change the x for every iteration */
        yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;         /* There are more y-values than x-values */
    }
    for (curpixel = 0; curpixel <= numpixels; curpixel++)
    {
        LCD_DrawPoint(x,y,LCD.Color);             /* Draw the current pixel */
        num += numadd;              /* Increase the numerator by the top of the fraction */
        if (num >= den)             /* Check if numerator >= denominator */
        {
            num -= den;               /* Calculate the new numerator value */
            x += xinc1;               /* Change the x as appropriate */
            y += yinc1;               /* Change the y as appropriate */
        }
        x += xinc2;                 /* Change the x as appropriate */
        y += yinc2;                 /* Change the y as appropriate */
    }
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawRect
*
*	��ڲ���: x - ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 width  - ͼƬ��ˮƽ��ȣ����ȡֵ480
*				 height - ͼƬ�Ĵ�ֱ��ȣ����ȡֵ272
*
*	��������: ��ָ��λ�û���ָ������ľ�������
*
*	˵    ��: �ú�����ֲ��ST�ٷ������������
*
*****************************************************************************************************************************************/

void LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    /* draw horizontal lines */
    LCD_DrawLine(x, y, x+width, y);
    LCD_DrawLine(x, y+height, x+width, y+height);

    /* draw vertical lines */
    LCD_DrawLine(x, y, x, y+height);
    LCD_DrawLine(x+width, y, x+width, y+height);
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawCircle
*
*	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 r  - �뾶
*
*	��������: ������ (x,y) ���ư뾶Ϊ r ��Բ������
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r)
{
    int Xadd = -r, Yadd = 0, err = 2-2*r, e2;
    do {

        LCD_DrawPoint(x-Xadd,y+Yadd,LCD.Color);
        LCD_DrawPoint(x+Xadd,y+Yadd,LCD.Color);
        LCD_DrawPoint(x+Xadd,y-Yadd,LCD.Color);
        LCD_DrawPoint(x-Xadd,y-Yadd,LCD.Color);

        e2 = err;
        if (e2 <= Yadd) {
            err += ++Yadd*2+1;
            if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
        }
        if (e2 > Xadd) err += ++Xadd*2+1;
    }
    while (Xadd <= 0);

}

/***************************************************************************************************************************************
*	�� �� ��: LCD_DrawEllipse
*
*	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 r1  - ˮƽ����ĳ���
*				 r2  - ��ֱ����ĳ���
*
*	��������: ������ (x,y) ����ˮƽ����Ϊ r1 ��ֱ����Ϊ r2 ����Բ����
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_DrawEllipse(int x, int y, int r1, int r2)
{
    int Xadd = -r1, Yadd = 0, err = 2-2*r1, e2;
    float K = 0, rad1 = 0, rad2 = 0;

    rad1 = r1;
    rad2 = r2;

    if (r1 > r2)
    {
        do {
            K = (float)(rad1/rad2);

            LCD_DrawPoint(x-Xadd,y+(uint16_t)(Yadd/K),LCD.Color);
            LCD_DrawPoint(x+Xadd,y+(uint16_t)(Yadd/K),LCD.Color);
            LCD_DrawPoint(x+Xadd,y-(uint16_t)(Yadd/K),LCD.Color);
            LCD_DrawPoint(x-Xadd,y-(uint16_t)(Yadd/K),LCD.Color);

            e2 = err;
            if (e2 <= Yadd) {
                err += ++Yadd*2+1;
                if (-Xadd == Yadd && e2 <= Xadd) e2 = 0;
            }
            if (e2 > Xadd) err += ++Xadd*2+1;
        }
        while (Xadd <= 0);
    }
    else
    {
        Yadd = -r2;
        Xadd = 0;
        do {
            K = (float)(rad2/rad1);

            LCD_DrawPoint(x-(uint16_t)(Xadd/K),y+Yadd,LCD.Color);
            LCD_DrawPoint(x+(uint16_t)(Xadd/K),y+Yadd,LCD.Color);
            LCD_DrawPoint(x+(uint16_t)(Xadd/K),y-Yadd,LCD.Color);
            LCD_DrawPoint(x-(uint16_t)(Xadd/K),y-Yadd,LCD.Color);

            e2 = err;
            if (e2 <= Xadd) {
                err += ++Xadd*3+1;
                if (-Yadd == Xadd && e2 <= Yadd) e2 = 0;
            }
            if (e2 > Yadd) err += ++Yadd*3+1;
        }
        while (Yadd <= 0);
    }
}

/***************************************************************************************************************************************
*	�� �� ��: LCD_FillRect
*
*	��ڲ���: x - ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 width  - ͼƬ��ˮƽ��ȣ����ȡֵ480
*				 height - ͼƬ�Ĵ�ֱ��ȣ����ȡֵ272
*
*	��������: ������ (x,y) ���ָ�������ʵ�ľ���
*
*	˵    ��: 1. ʹ��DMA2Dʵ��
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{

    DMA2D->CR	  &=	~(DMA2D_CR_START);				//	ֹͣDMA2D
    DMA2D->CR		=	DMA2D_R2M;							//	�Ĵ�����SDRAM
    DMA2D->OPFCCR	=	LCD.ColorMode;						//	������ɫ��ʽ
    DMA2D->OCOLR	=	LCD.Color;							//	��ɫ

    if(LCD.Direction == Direction_H)  //�������
    {
        DMA2D->OOR		=	LCD_Width - width;				//	������ƫ��
        DMA2D->OMAR		=	LCD.LayerMemoryAdd + LCD.BytesPerPixel*(LCD_Width * y + x);	// ��ַ;
        DMA2D->NLR		=	(width<<16)|(height);			//	�趨���ȺͿ��
    }
    else	//�������
    {
        DMA2D->OOR		=	LCD_Width - height;		//	������ƫ��
        DMA2D->OMAR		=	LCD.LayerMemoryAdd + LCD.BytesPerPixel*((LCD_Height - x - 1 - width)*LCD_Width + y);	// ��ַ
        DMA2D->NLR		=	(width)|(height<<16);	//	�趨���ȺͿ��
    }

    DMA2D->CR	  |=	DMA2D_CR_START;					//	����DMA2D

    while (DMA2D->CR & DMA2D_CR_START) ;			//	�ȴ��������

}

/***************************************************************************************************************************************
*	�� �� ��: LCD_FillCircle
*
*	��ڲ���: x - Բ�� ˮƽ���꣬ȡֵ��Χ 0~479
*			 	 y - Բ�� ��ֱ���꣬ȡֵ��Χ 0~271
*			 	 r  - �뾶
*
*	��������: ������ (x,y) ���뾶Ϊ r ��Բ������
*
*	˵    ��: 1. �ú�����ֲ��ST�ٷ������������
*				 2. Ҫ���Ƶ������ܳ�����Ļ����ʾ����
*
*****************************************************************************************************************************************/

void LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r)
{
    int32_t  D;    /* Decision Variable */
    uint32_t  CurX;/* Current X Value */
    uint32_t  CurY;/* Current Y Value */

    D = 3 - (r << 1);

    CurX = 0;
    CurY = r;

    while (CurX <= CurY)
    {
        if(CurY > 0)
        {
            LCD_DrawLine(x - CurX, y - CurY,x - CurX,y - CurY + 2*CurY);
            LCD_DrawLine(x + CurX, y - CurY,x + CurX,y - CurY + 2*CurY);
        }

        if(CurX > 0)
        {
            LCD_DrawLine(x - CurY, y - CurX,x - CurY,y - CurX + 2*CurX);
            LCD_DrawLine(x + CurY, y - CurX,x + CurY,y - CurX + 2*CurX);
        }
        if (D < 0)
        {
            D += (CurX << 2) + 6;
        }
        else
        {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }

    LCD_DrawCircle(x, y, r);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
