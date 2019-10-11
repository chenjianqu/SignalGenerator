#include "handle.h"
#include "menu.h"
#include "func.h"
#include "paramanager.h"

u8 irkey;

u8 len;

void KeyHandle(void)
{
	u8 t=KEY_Scan(0);
	if(t>0){
		
		switch(t)//按键扫描
		{
			//按下"下"键
			case WKUP_PRES: 
				{
					if(pm.flagParaSelected==ParaRESET)
					{
						//切换下一行
						if(menu.layer==MenuLayer0)
							menu.Layer0_Selected=(menu.Layer0_Selected+1)%ITEM_NUM_LAYER0;
						else if(menu.layer==MenuLayer1)
							menu.Layer1_Selected=(menu.Layer1_Selected+1)%ITEM_NUM_LAYER1;
						else if(menu.layer==MenuLayer2)
							menu.Layer2_Selected=(menu.Layer2_Selected+1)%ITEM_NUM_LAYER2;
					}
					else if(pm.flagParaSelected==ParaAM)//设置参数的状态
						pm.amArrayPoint=(pm.amArrayPoint+1)%pm.amLen;
					else if(pm.flagParaSelected==ParaFQ)
						pm.fqArrayPoint=(pm.fqArrayPoint+1)%pm.fqLen;
					else if(pm.flagParaSelected==ParaHAR)
						pm.harArrayPoint=(pm.harArrayPoint+1)%pm.harLen;
				}
				if(pm.flagParaSelected!=ParaRESET)ShowParameterNumber();
				break;
			//按下确认键
			case KEY1_PRES:
					if(menu.layer==MenuLayer0)
					{
						menu.layer=MenuLayer1;
					}
					else if(menu.layer==MenuLayer1)
						menu.layer=MenuLayer2;
					else if(menu.layer==MenuLayer2)//信号发生器详情界面
					{
						if(menu.Layer2_Selected==Item_IsEnable)//打开/关闭信号发生
						{
							if(pm.isOutputEnable==false)
							{
								pm.isOutputEnable=true;
								EnableOutput();
							}
							else
							{
								pm.isOutputEnable=false;
								DisableOutput();
							}
						}
						else if(menu.Layer2_Selected==Item_Amplitude)//修改幅值参数
						{
							if(pm.flagParaSelected!=ParaAM)
								pm.flagParaSelected=ParaAM;
							else{
								pm.flagParaSelected=ParaRESET;
								PM_SetValueFromArray();
								SetAmplitude();
							}
						}
						else if(menu.Layer2_Selected==Item_Frequency)//修改频率参数
						{
							if(pm.flagParaSelected!=ParaFQ)
								pm.flagParaSelected=ParaFQ;
							else{
								pm.flagParaSelected=ParaRESET;
								PM_SetValueFromArray();
								SetFrequency();
							}
						}
						else if(menu.Layer2_Selected==Item_Harmonic)//修改
						{
							if(pm.flagParaSelected!=ParaHAR)
								pm.flagParaSelected=ParaHAR;
							else{
								pm.flagParaSelected=ParaRESET;
							}
						}
					}
					
				break;
			//按下返回键
			case KEY0_PRES:
			{
				if(pm.flagParaSelected==ParaRESET)
				{
						if(menu.layer==MenuLayer1)
							menu.layer=MenuLayer0;
						else if(menu.layer==MenuLayer2){
							menu.layer=MenuLayer1;
							DisableOutput();
						}
				}
				else if(pm.flagParaSelected==ParaAM)
				{
					pm.amArray[pm.amArrayPoint]=(pm.amArray[pm.amArrayPoint]+1)%10;
				}
				else if(pm.flagParaSelected==ParaFQ)
				{
					pm.fqArray[pm.fqArrayPoint]=(pm.fqArray[pm.fqArrayPoint]+1)%10;
				}
				else if(pm.flagParaSelected==ParaHAR)
				{
					pm.harArray[pm.harArrayPoint]=(pm.harArray[pm.harArrayPoint]+1)%10;
				}				
			}
			if(pm.flagParaSelected!=ParaRESET)ShowParameterNumber();
			break;
		}
		LED0_Toggle();
		ShowMenuKeyUpdate();

	}
}







//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
    if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
    {
        delay_ms(10);
        key_up=0;
        if(KEY0==0)       return KEY0_PRES;
        else if(KEY1==0)  return KEY1_PRES;
        else if(WK_UP==1) return WKUP_PRES;          
    }else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1;
    return 0;   //无按键按下
}


void IRHandle(void)
{
	static Key irOrder=Key_Null;
	
	irkey=RemoteScan();	

	if(irkey)
	{	 
		LCD_ShowNum(86,130,irkey,3,16);		//显示键值
		LCD_ShowNum(86,150,RmtCnt,3,16);	//显示按键次数		  
		switch(irkey)
		{
			case 0:irOrder=Key_Null;break;			   
			case 162:irOrder=Key_Power;break;	    
			case 98:irOrder=Key_Up;break;	    
			case 2:irOrder=Key_Exe;break;		 
			case 226:irOrder=Key_Alientek;break;		  
			case 194:irOrder=Key_Right;break;	   
			case 34:irOrder=Key_Left;break;		  
			case 224:irOrder=Key_Sub;break;		  
			case 168:irOrder=Key_Down;break;		   
			case 144:irOrder=Key_Add;break;		    
			case 104:irOrder=Key_One;break;		  
			case 152:irOrder=Key_Two;break;	   
			case 176:irOrder=Key_Three;break;	    
			case 48:irOrder=Key_Four;break;		    
			case 24:irOrder=Key_Five;break;		    
			case 122:irOrder=Key_Six;break;		  
			case 16:irOrder=Key_Seven;break;			   					
			case 56:irOrder=Key_Eight;break;	 
			case 90:irOrder=Key_Nine;break;
			case 66:irOrder=Key_Zero;break;
			case 82:irOrder=Key_Back;break;		 
			default:irOrder=Key_Null;break;
		}
	}
	else
		irOrder=Key_Null;
	
	
	
		if(irOrder!=Key_Null)
		{
		SetOrder(irOrder);
			
		POINT_COLOR=BLACK;
		LCD_ShowNum(86,130,irOrder,3,16);		//显示键值		
		}
		
		POINT_COLOR=BLACK;
		BACK_COLOR=WHITE;
}





void UsartHandle(void)
{
    if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			HAL_UART_Transmit(&huart1,(uint8_t*)USART_RX_BUF,len,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}

}


//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==(&htim2))
	{
			LED0_Toggle();
	}
	else if(htim->Instance==TIM4)
	{
 		if(RmtSta&0x80)//上次有数据被接收到了
		{	
			RmtSta&=~0X10;						//取消上升沿已经被捕获标记
			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;//标记已经完成一次按键的键值信息采集
			if((RmtSta&0X0F)<14)RmtSta++;
			else
			{
				RmtSta&=~(1<<7);//清空引导标识
				RmtSta&=0XF0;	//清空计数器	
			}						 	   	
		}	
	}
}


