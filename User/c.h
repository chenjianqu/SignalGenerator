#ifndef _C_H
#define _C_H
#include "sys.h"
#include "delay.h"
#include "main.h"
#include "usart.h"
#include "tim.h"



typedef u8 bool;

#define true 1
#define false 0
	
#define PI 3.1415926535897932384626433832795


#define LED0(isOnLED)		(isOnLED?HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET):HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET))
#define LED0_Toggle() (HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin)) //LED0
#define LED1(isOnLED)		(isOnLED?HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET):HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET))
#define LED1_Toggle() (HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)) //LED1

#define BEEP(isOnBEEP)		(isOnBEEP?HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET):HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET))
#define BEEP_Toggle() (HAL_GPIO_TogglePin(BEEP_GPIO_Port, BEEP_Pin))

#define KEY0        HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)  //KEY0°´¼üPE4
#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)  //KEY1°´¼üPE3
#define WK_UP       HAL_GPIO_ReadPin(KEY_UP_GPIO_Port,KEY_UP_Pin)  //WKUP°´¼üPA0

#define KEY0_PRES 	1
#define KEY1_PRES		2
#define WKUP_PRES   4




typedef enum Key_Order_Enum{
	Key_One=1,
	Key_Two,
	Key_Three,
	Key_Four,
	Key_Five,
	Key_Six,
	Key_Seven,
	Key_Eight,
	Key_Nine,
	Key_Zero,
	Key_Back,
	Key_Power,
	Key_Alientek,
	Key_Up,
	Key_Down,
	Key_Left,
	Key_Right,
	Key_Exe,
	Key_Add,
	Key_Sub,
	Key_Null
} Key;


typedef enum ParameterSelectedEnum
{
	ParaRESET=0,
	ParaAM=1,
	ParaFQ,
	ParaHAR,
} ParameterSelected;


typedef struct ParameterManagerStruct
{
	bool isOutputEnable;
	
	ParameterSelected flagParaSelected;
	
	u32 am;
	u8 amArray[10];
	u8 amArrayPoint;
	u8 amLen;
	u16 amCoordinateX;
	u16 amCoordinateY;
	
	
	u32 fq;
	u8 fqArray[10];
	u8 fqArrayPoint;
	u8 fqLen;
	u16 fqCoordinateX;
	u16 fqCoordinateY;
	
	u32 har;
	u8 harArray[10];
	u8 harArrayPoint;
	u8 harLen;
	u16 harCoordinateX;
	u16 harCoordinateY;

} ParaMng;


extern ParaMng pm;
extern const u16 SineArrayStd[500];
extern const u16 SquareWaveArrayStd[2];
extern u16 waveDataArray[512];
extern u16 SquareWaveArray[3];


#endif
