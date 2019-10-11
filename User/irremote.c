#include "irremote.h"
#include "tim.h"


#define RDATA PBin(9)		//红外数据输入脚

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0

//遥控器接收状态
//[7]:收到了引导码标志
//[6]:得到了一个按键的所有信息
//[5]:保留	
//[4]:标记上升沿是否已经被捕获								   
//[3:0]:溢出计时器
u8 	RmtSta=0;	  	  
u16 Dval;		//下降沿时计数器的值
u32 RmtRec=0;	//红外接收到的数据	   		    
u8  RmtCnt=0;	//按键按下的次数	 


//定时器4中端服务函数
void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim4);//定时器共用处理函数
} 


//定时器输入捕获中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	if(htim->Instance==TIM4)
	{
		if(RDATA)//上升沿捕获
		{
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   //一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);//CC4P=1 设置为下降沿捕获
			__HAL_TIM_SET_COUNTER(&htim4,0);  	//清空定时器值   	  
		  	RmtSta|=0X10;							//标记上升沿已经被捕获
		}else //下降沿捕获
		{
			Dval=HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_4);//读取CCR4也可以清CC4IF标志位
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   	//一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);//配置TIM4通道4上升沿捕获
			if(RmtSta&0X10)							//完成一次高电平捕获 
			{
 				if(RmtSta&0X80)//接收到了引导码
				{
					
					if(Dval>300&&Dval<800)			//560为标准值,560us
					{
						RmtRec<<=1;					//左移一位.
						RmtRec|=0;					//接收到0	   
					}else if(Dval>1400&&Dval<1800)	//1680为标准值,1680us
					{
						RmtRec<<=1;					//左移一位.
						RmtRec|=1;					//接收到1
					}else if(Dval>2200&&Dval<2600)	//得到按键键值增加的信息 2500为标准值2.5ms
					{
						RmtCnt++; 					//按键次数增加1次
						RmtSta&=0XF0;				//清空计时器		
					}
 				}else if(Dval>4200&&Dval<4700)		//4500为标准值4.5ms
				{
					RmtSta|=1<<7;					//标记成功接收到了引导码
					RmtCnt=0;						//清除按键次数计数器
				}						 
			}
			RmtSta&=~(1<<4);
		}
	}
}


//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
u8 RemoteScan(void)
{
	u8 sta=0;       
	u8 t1,t2;  
	if(RmtSta&(1<<6))//得到一个按键的所有信息了
	{ 
	    t1=RmtRec>>24;			//得到地址码
	    t2=(RmtRec>>16)&0xff;	//得到地址反码 
 	    if((t1==(u8)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址 
	    { 
	        t1=RmtRec>>8;
	        t2=RmtRec; 	
	        if(t1==(u8)~t2)sta=t1;//键值正确	 
		}   
		if((sta==0)||((RmtSta&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	RmtSta&=~(1<<6);//清除接收到有效按键标识
			RmtCnt=0;		//清除按键次数计数器
		}
	}  
    return sta;

}

