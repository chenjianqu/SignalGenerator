#include "menu.h"
#include "math.h"

Menu menu;
Menu menuLast={255,255,255,255};


GUIMenu menuItemsLayer0;
GUIMenu menuItemsLayer1;
GUIMenu menuItemsLayer2;


void ShowLayer0(void)
{
	GUIMenu gMenu=menuItemsLayer0;
	
	gMenu.itemList[menu.Layer0_Selected].backgroundColor=BLUE;
	gMenu.itemList[menu.Layer0_Selected].fontColor=WHITE;

	GUI_ShowMenuItem(&gMenu);
}


void ShowLayer1(void)
{
	GUIMenu gMenu=menuItemsLayer1;	
	//选中的项
	gMenu.itemList[menu.Layer1_Selected].backgroundColor=BLUE;
	gMenu.itemList[menu.Layer1_Selected].fontColor=WHITE;
	
	GUI_ShowMenuItem(&gMenu);
}

//软件说明
void ShowSoftwareAbout(void)
{
	POINT_COLOR=BLUE;//设置字体为蓝色 
	BACK_COLOR=WHITE; 
		LCD_ShowString(10,40,210,16,16,"Software version: v0.1");
		LCD_ShowString(10,70,210,16,16,"Coded by ChenJianqv");
}


//最底层
void ShowLayer2(void)
{
	u8* topicName=menuItemsLayer1.itemList[menu.Layer1_Selected].name;
	
	u16 y=GUI_ITEM_FONTSIZE+2*GUI_ITEM_FONT_MARGIN;
	u16 w=0;
	
//绘制标题
	LCD_Fill(0,0,LCD_WIDTH,y,BLACK);
	POINT_COLOR=WHITE;
	BACK_COLOR=BLACK;
  LCD_ShowString(GUI_ITEM_MARGIN,GUI_ITEM_FONT_MARGIN,LCD_WIDTH,GUI_ITEM_FONTSIZE,GUI_ITEM_FONTSIZE,topicName);
	
	y+=GUI_ITEM_FONT_MARGIN;
	
	//绘制菜单项
	
	/************OUTPUT***************/
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE; 
	LCD_ShowString(GUI_ITEM_MARGIN,y,8*6,16,16,"Output");
	
	if(menu.Layer2_Selected==Item_IsEnable)
	{
		POINT_COLOR=WHITE;	
		BACK_COLOR=BLUE;  
	}
	else
	{
		POINT_COLOR=BLUE;	
		BACK_COLOR=WHITE;  	
	}
	
//	u16 x=GUI_ITEM_MARGIN+8*6+8;
		u16 x=GUI_ITEM_MARGIN+16;
	y+=16;
	POINT_COLOR=RED;
	if(pm.isOutputEnable==true){
		w=6*12;
		LCD_ShowString(x,y,w,24,24,"Enable");
	}
	else{
		w=7*12;
		LCD_ShowString(x,y,w,24,24,"Disable");
	}
	
	y=9*8+8;
	POINT_COLOR=BLUE;	
	LCD_DrawLine(0,y,LCD_WIDTH,y);
	
	
	//2
	/************幅值***************/
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE;  
	y+=4;
	LCD_ShowString(GUI_ITEM_MARGIN,y,w,16,16,"Amplitude");
	
	y+=16;
	POINT_COLOR=RED;
	if(menu.Layer2_Selected==Item_Amplitude){
		POINT_COLOR=WHITE;	
		BACK_COLOR=BLUE; 
	}
	else{
		POINT_COLOR=RED;
		BACK_COLOR=WHITE;
	}
	//显示幅值数字
	x=GUI_ITEM_MARGIN;
		LCD_ShowChar(x,y,pm.amArray[0]+'0',32,0);
		x+=16;
		LCD_ShowChar(x,y,'.',32,0);
		x+=16;
		for(u8 i=1;i<pm.amLen;i++){
			LCD_ShowChar(x,y,pm.amArray[i]+'0',32,0);
			x+=16;
		}
	//LCD_ShowNum(GUI_ITEM_MARGIN,y,pm.am,7,32);
	
	pm.amCoordinateY=y;
	pm.amCoordinateX=GUI_ITEM_MARGIN;
	
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE;  
	
	w=GUI_ITEM_MARGIN+7*16;
	
	LCD_ShowString(w+10,y+16,32,16,16,"V");
	
	
	
	//3
	/************频率***************/
	y+=32;
	POINT_COLOR=BLUE;
	LCD_DrawLine(0,y,LCD_WIDTH,y);
	
	y+=10;
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE;  
	w=9*8;
	LCD_ShowString(GUI_ITEM_MARGIN,y,w,16,16,"Frequency");
	
	y+=16;
	POINT_COLOR=RED;
	if(menu.Layer2_Selected==Item_Frequency){
		POINT_COLOR=WHITE;	
		BACK_COLOR=BLUE; 
	}
	LCD_ShowNum(GUI_ITEM_MARGIN,y,pm.fq,7,32);
	pm.fqCoordinateX=GUI_ITEM_MARGIN;
	pm.fqCoordinateY=y;
	
	
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE; 
	
	w=GUI_ITEM_MARGIN+7*16;
	
	LCD_ShowString(w+10,y+16,32,16,16,"Hz");
	
	y+=32;
	POINT_COLOR=BLUE;
	LCD_DrawLine(0,y,LCD_WIDTH,y);
	
	
	//4
	/************谐波合成***************/
	y+=5;
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE;  
	LCD_ShowString(GUI_ITEM_MARGIN,y,8*8,16,16,"Harmonic");
	
	y+=16;
	POINT_COLOR=RED;
	if(menu.Layer2_Selected==Item_Harmonic){
		POINT_COLOR=WHITE;	
		BACK_COLOR=BLUE; 
	}
	x=GUI_ITEM_MARGIN;
	//LCD_ShowNum(GUI_ITEM_MARGIN,y,pm.har,7,32);
	for(u8 i=0;i<pm.harLen;i++)
	{
			LCD_ShowChar(x,y,pm.harArray[i]+'0',32,0);
			x+=16;
	}
	
	pm.harCoordinateX=GUI_ITEM_MARGIN;
	pm.harCoordinateY=y;
	
	
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE; 
	
	w=GUI_ITEM_MARGIN+7*16;
	
	LCD_ShowString(w+10,y+16,32,16,16,"n");
	
	y+=32;
	POINT_COLOR=BLUE;
	LCD_DrawLine(0,y,LCD_WIDTH,y);
	
	
	//5
	/************波形显示***************/
	y+=5;
	POINT_COLOR=BLUE;	
	BACK_COLOR=WHITE;  
	LCD_ShowString(GUI_ITEM_MARGIN,y,8*8,16,16,"Waveform");
	
	y+=16;
	y+=24;
	if(menu.Layer1_Selected==0)
		GUI_DrawSquarewave(y,RED);
	else if(menu.Layer1_Selected==1)
		GUI_DrawTrianglewave(y,RED);
	else if(menu.Layer1_Selected==2)
		GUI_DrawSineWave(y-16,RED);
	
	
	/*************显示状态*************/
	if(pm.am>500000)
	{
		POINT_COLOR=WHITE;	
		BACK_COLOR=RED; 
		LCD_ShowString(30,280,21*8,16,16,"Amplitude Unavailable");
	}
	if(pm.fq>200000)
	{
		POINT_COLOR=WHITE;	
		BACK_COLOR=RED; 
		LCD_ShowString(30,280,21*8,16,16,"Frequency Unavailable");
	}
}




//显示菜单
void ShowMenu(void)
{
		switch(menu.layer)//根据当前层数显示
		{
			case MenuLayer0:
				if(menu.Layer0_Selected!=menuLast.Layer0_Selected|| menu.layer!=menuLast.layer){//更新菜单
					LCD_Clear(WHITE);
					menuLast.Layer0_Selected=menu.Layer0_Selected;
					ShowLayer0();//显示根目录
				}
				break;
			case MenuLayer1:
				if(menu.Layer1_Selected!=menuLast.Layer1_Selected|| menu.layer!=menuLast.layer)
				{
					LCD_Clear(WHITE);
					menuLast.Layer1_Selected=menu.Layer1_Selected;
						switch(menu.Layer0_Selected)
						{
							case Item_SignalGenerator:
								ShowLayer1();
								break;
							case Item_SoftWareAbout:
								ShowSoftwareAbout();
								break;
						}
				}
				break;
			case MenuLayer2:
				if(menu.Layer2_Selected!=menuLast.Layer2_Selected || menu.layer!=menuLast.layer)
				{
					LCD_Clear(WHITE);
					menuLast.Layer2_Selected=menu.Layer2_Selected;
						switch(menu.Layer0_Selected)
						{
							case Item_SignalGenerator:
							{
								ShowLayer2();							
								break;
							case Item_SoftWareAbout:
								ShowSoftwareAbout();
								break;
						}
				}
				}
				break;
		}
		
		if(menu.layer!=menuLast.layer)
			menuLast=menu;
	
}


//显示菜单
void ShowMenuKeyUpdate(void)
{
		switch(menu.layer)//根据当前层数显示
		{
			case MenuLayer0:
					LCD_Clear(WHITE);
					ShowLayer0();//显示根目录
				break;
			case MenuLayer1:
					LCD_Clear(WHITE);
						switch(menu.Layer0_Selected)
						{
							case Item_SignalGenerator:
								ShowLayer1();
								break;
							case Item_SoftWareAbout:
								ShowSoftwareAbout();
								break;
						}
				break;
			case MenuLayer2:
					LCD_Clear(WHITE);
						switch(menu.Layer0_Selected)
						{
							case Item_SignalGenerator:
							{
								ShowLayer2();							
								break;
							case Item_SoftWareAbout:
								ShowSoftwareAbout();
								break;
						}
				}
				break;
		}	
		
		
}



void InitMenu(void)
{
	//初始化第一层
	
	menuItemsLayer0.itemList[0].name="Signal Generator";
	menuItemsLayer0.itemList[0].fontSize=24;
	menuItemsLayer0.itemList[0].fontColor=BLUE;
	menuItemsLayer0.itemList[0].backgroundColor=WHITE;
	
	menuItemsLayer0.itemList[1].name="Software About";
	menuItemsLayer0.itemList[1].fontSize=24;
	menuItemsLayer0.itemList[1].fontColor=BLUE;
	menuItemsLayer0.itemList[1].backgroundColor=WHITE;
	
	menuItemsLayer0.itemNum=ITEM_NUM_LAYER0;
	menuItemsLayer0.topicName="Main Menu";
	
	//初始化第二层
	menuItemsLayer1.itemList[0].name="Square Wave";
	menuItemsLayer1.itemList[0].fontSize=24;
	menuItemsLayer1.itemList[0].fontColor=BLUE;
	menuItemsLayer1.itemList[0].backgroundColor=WHITE;
	
	menuItemsLayer1.itemList[1].name="Triangular Wave";
	menuItemsLayer1.itemList[1].fontSize=24;
	menuItemsLayer1.itemList[1].fontColor=BLUE;
	menuItemsLayer1.itemList[1].backgroundColor=WHITE;
	
	menuItemsLayer1.itemList[2].name="Sine Wave";
	menuItemsLayer1.itemList[2].fontSize=24;
	menuItemsLayer1.itemList[2].fontColor=BLUE;
	menuItemsLayer1.itemList[2].backgroundColor=WHITE;
	
	menuItemsLayer1.itemNum=ITEM_NUM_LAYER1;
	menuItemsLayer1.topicName="Sub Menu";
}


