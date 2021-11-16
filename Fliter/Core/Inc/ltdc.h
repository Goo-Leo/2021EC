/**
  ******************************************************************************
  * @file    ltdc.h
  * @brief   This file contains all the function prototypes for
  *          the ltdc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LTDC_H__
#define __LTDC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "fonts.h"
/* USER CODE END Includes */

extern LTDC_HandleTypeDef hltdc;

/* USER CODE BEGIN Private defines */
#define 	LCD_NUM_LAYERS  1

#define	ColorMode_0   LTDC_PIXEL_FORMAT_RGB565




// 显示方向参数
// 使用示例：LCD_DisplayDirection(Direction_H) ，设置屏幕横屏显�??
// 使用示例：LCD_DisplayDirection(Direction_V) ，设置屏幕竖直显�??

#define	Direction_H	0		//LCD横屏显示
#define	Direction_V	1		//LCD竖屏显示

// 设置变量显示时多余位�??0还是补空�??
// 只有 LCD_DisplayNumber() 显示整数 �?? LCD_DisplayDecimals()显示小数 这两个函数用�??
// 使用示例�?? LCD_ShowNumMode(Fill_Zero) 设置多余位填�??0，例�?? 123 可以显示�?? 000123
//
#define  Fill_Zero  0		//填充0
#define  Fill_Space 1		//填充空格


/*---------------------------------------- 常用颜色 ------------------------------------------------------

 1. 这里为了方便用户使用，定义的�??32位颜色，然后再�?�过代码自动转换成对应颜色格式所�??要的的颜�??
 2. 32位的颜色中，从高位到低位分别对应 A、R、G、B  4个颜色�?�道，其中A表示透明通道
 3. �??多可设置255级�?�明色，ff表示不�?�明�??0表示完全透明
 4. 除非使用ARGB1555和ARGB8888等支持�?�明色的颜色格式，不然�?�明色不起作用，其中ARGB1555仅支持一�??
	 透明色，即仅有�?�明和不透明两种状�?�，ARGB4444�??16级�?�明度，ARGB8888支持255级�?�明�??
 5. 用户可以在电脑用调色板获�??24位RGB颜色，然后再补充透明通道得到32位的颜色，再将此32位颜色输�??
	 LCD_SetColor()或LCD_SetBackColor()就可以显示出相应的颜色�??
 6. 使用示例：纯蓝色的RGB值为0x0000FF，如果不�??要�?�明色，则对应的32位颜色�?�为 0xff0000FF
 7. 以下定义的颜色都设置为不透明，用户可根据�??求自行定义对应的颜色								*/

#define 	LCD_WHITE       0xffFFFFFF		// 纯白�??
#define 	LCD_BLACK       0xff000000

#define 	LCD_BLUE        0xff0000FF
#define 	LCD_GREEN       0xff00FF00    //	纯绿�??
#define 	LCD_RED         0xffFF0000    //	纯红�??
#define 	LCD_CYAN        0xff00FFFF    //	蓝绿�??
#define 	LCD_MAGENTA     0xffFF00FF    //	紫红�??
#define 	LCD_YELLOW      0xffFFFF00    //	黄色
#define 	LCD_GREY        0xff2C2C2C    //	灰色

#define 	LIGHT_BLUE      0xff8080FF    //	亮蓝�??
#define 	LIGHT_GREEN     0xff80FF80    //	亮绿�??
#define 	LIGHT_RED       0xffFF8080    //	亮红�??
#define 	LIGHT_CYAN      0xff80FFFF    //	亮蓝绿色
#define 	LIGHT_MAGENTA   0xffFF80FF    //	亮紫红色
#define 	LIGHT_YELLOW    0xffFFFF80    //	亮黄�??
#define 	LIGHT_GREY      0xffA3A3A3    //	亮灰�??

#define 	DARK_BLUE       0xff000080    //	暗蓝�??
#define 	DARK_GREEN      0xff008000    //	暗绿�??
#define 	DARK_RED        0xff800000    //	暗红�??
#define 	DARK_CYAN       0xff008080    //	暗蓝绿色
#define 	DARK_MAGENTA    0xff800080    //	暗紫红色
#define 	DARK_YELLOW     0xff808000    //	暗黄�??
#define 	DARK_GREY       0xff404040    //	暗灰�??

/*---------------------------------------------------------- 函数声明 -------------------------------------------------------*/

void MX_LTDC_Init(void);		// LTDC以及层初始化
void LCD_Clear(void);			// 清屏函数
void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// �??部清屏函�??

void  LCD_SetLayer(uint8_t Layerx); 					//	设置�??
void  LCD_SetColor(uint32_t Color); 				   //	设置画笔颜色
void  LCD_SetBackColor(uint32_t Color);  				//	设置背景颜色
void  LCD_DisplayDirection(uint8_t direction);  	//	设置显示方向

//>>>>>	显示ASCII字符
void  LCD_SetFont(pFONT *fonts);												//	设置ASCII字体
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	显示单个ASCII字符
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	显示ASCII字符�??

//>>>>>	显示中文字符，包括ASCII�??
void 	LCD_SetTextFont(pFONT *fonts);										// 设置文本字体，包括中文和ASCII字体
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// 显示单个汉字
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// 显示字符串，包括中文和ASCII字符

//>>>>>	显示整数或小�??
void  LCD_ShowNumMode(uint8_t mode);		// 设置显示模式，多余位填充空格还是填充0
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// 显示整数
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// 显示小数

//>>>>>	绘制图片

void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage)  ;

//>>>>>	2D图形绘制函数

void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   								//画点
uint32_t 	LCD_ReadPoint(uint16_t x,uint16_t y);												//读点
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);					//画线
void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//画矩�??
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									//画圆
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											//画椭�??

//>>>>>	区域填充函数

void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			//填充矩形
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									//填充�??

/*-------------------------------------------------------- LCD相关参数 -------------------------------------------------------*/

#define HBP  43	// 根据屏幕的手册进行设�??
#define VBP  12
#define HSW  1
#define VSW  1
#define HFP  8
#define VFP  8

#define LCD_Width     	480						//	LCD的像素长�??
#define LCD_Height    	272						//	LCD的像素宽�??
#define LCD_MemoryAdd   0xD0000000 		//	显存的起始地�??

// layer0 每个像素�??占字�??

#if ( ColorMode_0 == LTDC_PIXEL_FORMAT_RGB565 || ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB1555 || ColorMode_0 ==LTDC_PIXEL_FORMAT_ARGB4444 )
#define BytesPerPixel_0		2		//16位色模式每个像素�??2字节
#elif ColorMode_0 == LTDC_PIXEL_FORMAT_RGB888
#define BytesPerPixel_0		3		//24位色模式每个像素�??3字节
#elif ColorMode_0 == LTDC_PIXEL_FORMAT_ARGB8888
	#define BytesPerPixel_0		4		//32位色模式每个像素�??4字节
#endif

/* USER CODE END Private defines */

void MX_LTDC_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __LTDC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
