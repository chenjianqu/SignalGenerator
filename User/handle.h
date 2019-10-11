#ifndef _HANDLE_H
#define _HANDLE_H
#include "c.h"
#include "irremote.h"


extern u8 RmtSta;

void KeyHandle(void);
void UsartHandle(void);
void IRHandle(void);
u8 KEY_Scan(u8 mode);

#endif

