#include "paramanager.h"


void InitParaManager(void)
{

	pm.am=499999;
		pm.amArray[0]=4;
		pm.amArray[1]=9;
		pm.amArray[2]=9;
		pm.amArray[3]=9;
		pm.amArray[4]=9;
		pm.amArray[5]=9;
		pm.amArrayPoint=5;
		pm.flagParaSelected=0;    
		pm.amLen=6;
		
		pm.fq=1234;
		pm.fqArray[0]=0;
		pm.fqArray[1]=0;
		pm.fqArray[2]=0;
		pm.fqArray[3]=1;
		pm.fqArray[4]=2;
		pm.fqArray[5]=3;
		pm.fqArray[6]=4;
		pm.fqArrayPoint=6;
		pm.fqLen=7;
		
		pm.harArray[0]=1;
		pm.harArray[1]=0;
		pm.harArray[2]=0;
		pm.harArray[3]=0;
		pm.harArray[4]=0;
		pm.harArray[5]=0;
		pm.harArray[6]=0;

		pm.harArrayPoint=6;
		pm.harLen=7;
}


void PM_SetArrayFromValue(void)
{
	u32 n=pm.am;
	
	for(u8 j=0;j<10;j++){
		pm.amArray[j]=0;
		pm.fqArray[j]=0;
	}
	
	u8 i=0;
	
	while(n>0){
		pm.amArray[i]=n%10;
		n/=10;
		i++;
	}
	pm.amLen=i;
	
	n=pm.fq;
	i=0;
	while(n>0){
		pm.fqArray[i]=n%10;
		n/=10;
		i++;
	}
	pm.fqLen=i;
}


void PM_SetValueFromArray(void)
{
	u32 t=0;
	for(u8 i=0;i<pm.amLen;i++)
		t=t*10+pm.amArray[i];
	pm.am=t;
	
	t=0;
	for(u8 i=0;i<pm.fqLen;i++)
		t=t*10+pm.fqArray[i];
	pm.fq=t;
}


