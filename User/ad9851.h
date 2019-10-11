#ifndef _AD9851_H
#define _AD9851_H
#include "c.h"

#define ad9851_rest_l HAL_GPIO_WritePin(AD9851_RESET_GPIO_Port, AD9851_RESET_Pin, GPIO_PIN_RESET)
#define ad9851_rest_h HAL_GPIO_WritePin(AD9851_RESET_GPIO_Port, AD9851_RESET_Pin, GPIO_PIN_SET)
#define ad9851_fq_up_l HAL_GPIO_WritePin(AD9851_FQ_UP_GPIO_Port, AD9851_FQ_UP_Pin, GPIO_PIN_RESET)
#define ad9851_fq_up_h HAL_GPIO_WritePin(AD9851_FQ_UP_GPIO_Port, AD9851_FQ_UP_Pin, GPIO_PIN_SET)
#define ad9851_w_clk_l HAL_GPIO_WritePin(AD9851_W_CLK_GPIO_Port, AD9851_W_CLK_Pin, GPIO_PIN_RESET)
#define ad9851_w_clk_h HAL_GPIO_WritePin(AD9851_W_CLK_GPIO_Port, AD9851_W_CLK_Pin, GPIO_PIN_SET)
#define ad9851_data_l HAL_GPIO_WritePin(AD9851_DATA_GPIO_Port, AD9851_DATA_Pin, GPIO_PIN_RESET)
#define ad9851_data_h HAL_GPIO_WritePin(AD9851_DATA_GPIO_Port, AD9851_DATA_Pin, GPIO_PIN_SET)


void ad9851_wr_serial(u8 w0,u32 frequence);
void ad9851_reset_serial(void);
void ad9851_wr_parrel(u8 w0,u32 frequency);
void ad9851_reset(void);

#endif

