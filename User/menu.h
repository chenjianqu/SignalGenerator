#ifndef _MENU_H
#define _MENU_H
#include "sys.h"
#include "delay.h"
#include "main.h"
#include "c.h"
#include "gui.h"

typedef enum MenuLayerEnum{
	MenuLayer0=0,
	MenuLayer1,
	MenuLayer2
} MenuLayer;

typedef enum MenuLayer0_ItemEnum{
	Item_SignalGenerator=0,
	Item_SoftWareAbout=1
} MenuLayer0_Item;

typedef enum MenuLayer1_ItemEnum{
	Item_SquareWave=0,
	Item_TriangleWave,
	Item_SineWave
} MenuLayer1_Item;

typedef enum MenuLayer2_ItemEnum{
	Item_IsEnable=0,
	Item_Amplitude,
	Item_Frequency,
	Item_Harmonic
} MenuLayer2_Item;


typedef struct MenuStruct{
	MenuLayer layer;
	u8 Layer0_Selected;
	u8 Layer1_Selected;
	u8 Layer2_Selected;
} Menu;



#define ITEM_NUM_LAYER0 2
#define ITEM_NUM_LAYER1 3
#define ITEM_NUM_LAYER2 4


extern GUIMenu menuItemsLayer0;
extern GUIMenu menuItemsLayer1;
extern GUIMenu menuItemsLayer2;

extern Menu menu;
extern Menu menuLast;

void InitMenu(void);
void ShowMenu(void);
void ShowLayer0(void);
void ShowLayer1(void); 
void ShowLayer2(void);
void ShowSoftwareAbout(void);


void ShowMenuKeyUpdate(void);


#endif
