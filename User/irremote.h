#ifndef _IRREMOTE_H
#define _IRREMOTE_H
#include "sys.h"
#include "delay.h"
#include "main.h"
#include "c.h"
#include "gui.h"

u8 RemoteScan(void);

extern u8 RmtSta;
extern u8 RmtCnt;	        //按键按下的次数

#endif
