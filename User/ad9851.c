#include "ad9851.h"

//串xing口初始化
void ad9851_reset_serial()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = AD9851_RESET_Pin|AD9851_FQ_UP_Pin|AD9851_W_CLK_Pin|AD9851_DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
	
	ad9851_w_clk_l;
	ad9851_fq_up_l;
	//rest ??
	ad9851_rest_l;
	ad9851_rest_h;
	ad9851_rest_l;
	//w_clk ??
	ad9851_w_clk_l;
	ad9851_w_clk_h;
	ad9851_w_clk_l;
	//fq_up ??
	ad9851_fq_up_l;
	ad9851_fq_up_h;
	ad9851_fq_up_l;
}


//串口写入
//w0 是9851w0寄存器的值
void ad9851_wr_serial(u8 w0,u32 frequence)
{
	u8 i,w;
	frequence=frequence*4294967296/180000000;
	//? w4 ??
	w=(frequence>>=0);
	for(i=0;i<8;i++)
	{
		if((w>>i)&0x01)
		ad9851_data_h;
		else ad9851_data_l;
		ad9851_w_clk_h;
		ad9851_w_clk_l;
	}
	//? w3 ??
	w=(frequence>>8);
	for(i=0;i<8;i++)
	{
		if((w>>i)&0x01)
		ad9851_data_h;
		else ad9851_data_l;
		ad9851_w_clk_h;
		ad9851_w_clk_l;
	}
	//? w2 ??
	w=(frequence>>16);
	for(i=0;i<8;i++)
	{
		if((w>>i)&0x01)
		ad9851_data_h;
		else ad9851_data_l;
		ad9851_w_clk_h;
		ad9851_w_clk_l;
	}
	//? w1 ??
	w=(frequence>>24);
	for(i=0;i<8;i++)
	{
		if((w>>i)&0x01)
		ad9851_data_h;
		else ad9851_data_l;
		ad9851_w_clk_h;
		ad9851_w_clk_l;
	}
	//? w0 ??
	w=w0;
	for(i=0;i<8;i++)
	{
		if((w>>i)&0x01)
		ad9851_data_h;
		else ad9851_data_l;
		ad9851_w_clk_h;
		ad9851_w_clk_l;
	}
	//????
	ad9851_fq_up_h;
	ad9851_fq_up_l;
}


void ad9851_wr_parrel(u8 w0,u32 frequency)
{

}


void ad9851_reset()
{

}
