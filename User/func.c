#include "func.h"
#include "c.h"
#include "irremote.h"
#include "menu.h"
#include "dac.h"
#include "math.h"
#include "lcd.h"
#include "ad9851.h"


#define FqToCycle(fq) (49999+1)*100/fq


u16 testArray[16]={600,1200,1800,2400,3000,3600,4200,4800,4200,3600,3000,2400,1800,1200,600,0};



//开启信号输出
void EnableOutput(void)
{
	SetAmplitude();
	SetFrequency();
	
	ad9851_reset_serial();
	ad9851_wr_serial(0x01,pm.fq);
	
	//方波
	if(menu.Layer1_Selected==0)
	{
		HAL_TIM_Base_Start(&htim6);
		HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(u32 *)SquareWaveArray,2,DAC_ALIGN_12B_R);
	}
	//三角波
	else if(menu.Layer1_Selected==1)
	{
		HAL_TIM_Base_Start(&htim6);
		//HAL_DAC_Start(&hdac,DAC_CHANNEL_1);//使能dac通道
		HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(u32 *)waveDataArray,512,DAC_ALIGN_12B_R);
	}
	//正弦波
	else if(menu.Layer1_Selected==2)
	{
		HAL_TIM_Base_Start(&htim6);
		HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(u32 *)waveDataArray,512,DAC_ALIGN_12B_R);
	}
}


//关闭信号输出
void DisableOutput(void)
{
	ad9851_reset_serial();
	HAL_TIM_Base_Stop(&htim6);
	HAL_DAC_Stop_DMA(&hdac,DAC_CHANNEL_2);
}



//幅值设置
void SetAmplitude(void)
{
	if(pm.am>500000)
		pm.am=500000;
	//方波
	if(menu.Layer1_Selected==0)
	{
		SquareWaveArray[0]=1;
		SquareWaveArray[1]=(u16)pm.am*4096/500000-1;//500000是活得的最大参数
		SquareWaveArray[2]=1;
		
	}
	//三角波
	else if(menu.Layer1_Selected==1)
	{
		SetTriangleWaveData();
	}
	//正弦波
	else if(menu.Layer1_Selected==2)
	{
		SetSineWaveData();
	}
	

}

//设置三角波幅值
void SetTriangleWaveData(void)
{
	double d = (4096.0/2) / (512.0 / 4);
	double t = (double)pm.am / 500000.0;
	int bias = (int)(4096.0*pm.am / 500000.0) / 2;
	for (int i = 0; i < 128; i++)
		waveDataArray[i]=(u16)(i*d*t)+bias+1;//加1是为了防止负数

	bias = (int)(127*d*t) + bias;
	for (int i = 0; i < 256; i++)
		waveDataArray[i+128]=bias - (int)(i*d*t)+1;

	bias = bias - (int)(255*d*t);
	for (int i = 0; i < 128; i++)
		waveDataArray[i+384]=(int)(i*d*t) + bias+1;

}

//设置正弦波幅值
void SetSineWaveData(void)
{
	double d = 2.0*PI / 512.0;
//	/double d = 2.0*PI / 412.0;
	double t = (double)pm.am / 500000.0;
	int bias = 4096* pm.am / 500000.0/2;
	for (int i = 0; i < 512; i++)
		waveDataArray[i]=(u16)(sin(i*d)*t*4096.0/2)+bias;
}








//频率设置
void SetFrequency(void)
{
	ad9851_reset_serial();
	ad9851_wr_serial(0x01,pm.fq);
	
	if(menu.Layer1_Selected==0)
	{
		if(pm.fq<=100)
		{
			TIM6->PSC=7199;
			TIM6->ARR=(u16)((10000/pm.fq)/2)-1;//因为是方波 所以除以2
		}
		else if(pm.fq<=10000)
		{
			TIM6->PSC=71;
			TIM6->ARR=(u16)((1000000/pm.fq)/2)-1;
		}
		else
		{
			TIM6->PSC=1;
			TIM6->ARR=(u16)((72000000/pm.fq)/2)-1;
		}
	}
	//三角波
	else if(menu.Layer1_Selected==1)
	{
		TIM6->PSC=71;
		TIM6->ARR=(u16)((1000000/pm.fq)/2)-1;
	}
	//正弦波
	else if(menu.Layer1_Selected==2)
	{
		TIM6->PSC=71;
		TIM6->ARR=(u16)((1000000/pm.fq)/2)-1;
	}
}


void SetOrder(Key order)
{
	if(menu.layer==MenuLayer0)
	{
		switch(order)
		{
			case Key_Up:
				menu.Layer0_Selected--;
				break;
			case Key_Down:
				menu.Layer0_Selected++;
				break;
			case Key_Exe:
				menu.layer=MenuLayer1;
				break;
			default:
				break;
		}
		menu.Layer0_Selected=menu.Layer0_Selected%ITEM_NUM_LAYER0;
	}
	else if(menu.layer==MenuLayer1)
	{
		switch(order)
		{
			case Key_Up:
				menu.Layer1_Selected--;
				break;
			case Key_Down:
				menu.Layer1_Selected++;
				break;
			case Key_Exe:
				menu.layer=MenuLayer2;
				LED1_Toggle();
			case Key_Back:
				menu.layer=MenuLayer0;
				break;
			default:
				break;
		}
		menu.Layer1_Selected=menu.Layer1_Selected%ITEM_NUM_LAYER1;
	}
	else if(menu.layer==MenuLayer2)
	{
		switch(order)
		{
			case Key_Up:
				menu.Layer2_Selected--;
				break;
			case Key_Down:
				menu.Layer2_Selected++;
				break;
			case Key_Exe:
				break;
			case Key_Back:
				menu.layer=MenuLayer1;
				break;
			default:
				break;
		}
		menu.Layer2_Selected=menu.Layer2_Selected%ITEM_NUM_LAYER2;
	}
		
}
