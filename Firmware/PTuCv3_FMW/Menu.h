/*Заметьте, что !defined(X) предпочтительней, чем #ifndef X.*/
#if !defined(INCLUDE_MENU_H)
#define INCLUDE_MENU_H

#include  "main.h"

//extern const char __flash fmt_3d[];
extern const char __flash fmt_3u[];

extern u08 szParamBuf[10];
extern u08 szParamVal_Buf[8];
extern u08 szParamName_Buf[8];
extern u08 szInfoBuf[16];





void fMenu(void);
void fPrintParams(u16 Prm);
void fPrintState(void);
void fPrint2LED(u16 val);

void fASCII2_LED(u08 *pBuf, u08 Size);



extern u08 TimerTaskID;
#endif /* End of INCLUDE_MENU_H */
