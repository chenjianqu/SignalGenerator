#ifndef _GUI_H
#define _GUI_H
#include "sys.h"
#include "delay.h"
#include "main.h"
#include "c.h"
#include "lcd.h"


typedef struct GUI_Rect{
	u16 x;
	u16 y;
	u16 w;
	u16 h;
} Rect;

typedef struct GUIMenuItem{
	u8 *name;
	u8 fontSize;
	u32 fontColor;
	u32 backgroundColor;
} GUI_Item;

typedef struct GUIMenuTypedef
{
	GUI_Item itemList[10];
	u8 itemNum;
	u8 *topicName;
} GUIMenu;



//LCD大小
#define LCD_WIDTH 240
#define LCD_HEIGHT 380

//菜单项高度
#define GUI_ITEM_HEIGHT 30

//菜单项字体大小
#define GUI_ITEM_FONTSIZE 24

//边缘大小
#define GUI_ITEM_MARGIN 10
#define GUI_ITEM_FONT_MARGIN 4


void GUI_ShowPowerOn(void);
void GUI_ShowMenuItem(GUIMenu *gMenu);

void GUI_DrawSineWave(u16 middleY,u32 color);
void GUI_DrawSquarewave(u16 middleY,u32 color);
void GUI_DrawTrianglewave(u16 middleY,u32 color);
void ShowParameterNumber(void);



#endif
