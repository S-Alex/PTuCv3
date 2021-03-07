#include  "main.h"
//#include  "lib/ADC.h"
//#include <avr/sleep.h>



//c:\tmp\!>h:\bin\avr-objcopy --rename-section .data=.text.rodata -I binary -O elf32-avr -B avr tst.txt tst.o

//main.c|237|warning: implicit declaration of function 'fRTC_Init' [-Wimplicit-function-declaration]|

//#define __AVR_ATmega8__

//-gdwarf-2
//-std=gnu99
//-ffunction-sections
//-fdata-sections
//-Wno-unused-local-typedefs
//-fshort-enums


//#include "RTOSA/types.h"

// * GoFlame [shape=box,label="Розжиг \n пеллеты"];

/* ----------------------- Static variables ---------------------------------*/
//eMODE_t vMode = NORMAL;    /* Текущий режим работы. 0 - нормальный; 1 - программирование. */
eSTATE_t vState = STOP;
eSTATE_t vStateNext = STOP;
u16 vStateNextTime;
eSTATE_t vStateForWait;




#define mGetSetsIndx(MEMBER) (((u16)&MEMBER - (u16)&vSets)>>1)

void BCD_3LED(u16 value, u08 *buf);

void fZCD(void);
void fProgramm(void);

u16 fGetTemp(u16 adc);

void fFlash(void);


u16 vInType;
u08 vFlash;
u08 v_N_Unload;
RegParam_t vRegParam;

u08 v_cnt_FultTS2_Unload;


//

////;                            |0123456789012345|
//const u08 __flash szAutor[]  = "Серов А.В. 2015 "
//                               "WM U199984787041";





int main(void)
{
  /* Join my output function and xitoa module */
  // xdev_out(send);
  //
  //  mPinOut(SCREW);
  //  mPinClr(SCREW);
  fOut_vPort(2, 0xff, IDDDR);
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /
  (*(u08*)pFlg) = 0x00;                                                /* Очистка всех флагов*/
//  pFlg->FuelOK = 1;
//  v_ORele_Manual = 0;
//  v_OLed_Manual = 0;
  fDin_Init();
  krRTOSA_Init();
  fMenuInit();                                       /* Инициализация меню и Чтение настроек */
  fADCInit();                                                               /* Настройка АЦП */
//  TIFR = -1;
//  GIFR = -1;
  fBuzInit();
  sei();
  fMenu();                                                         /*  !!!!! */
  fFlash();
  fIdle();
  fKBD_Init();

//  if (vSets_com.AutoRun) {          /* Установлен параметр автоматического запуска горелки */
//    mSetTimerTask(fRunStop, 10 _s);       /* Время отсрочки автоматического запуска горелки*/
//    TimerTaskID = GetTaskID(fRunStop);
//    vState = AUTORUN;
//  }

  //  wdt_enable(WDTO_2S);
  //  wdt_disable();
  wdt_enable(WDTO_2S);
  fSQInit();

// vRegParam.ADC_Temp = fGetADC_from_TempLM335(1);
// vRegParam.Temp = fGetTempLM335(65535)-273;

  while (1) {
    krProcessTaskQueue();
#ifndef PROTEUS

    if (1){
    //if (TIFR & (1 << TOV2)) {
      fDin_Fresh();
    }

#endif
    fADC_Exe();
    fBuzer();
    wdt_reset();
  }

  return 0;
}



void fProgramm(void)
{
}


void fIdle(void)
{
  mSetTimerTask(fIdle, 10 _ms);
  v_KBD.wt = 1;
#ifdef PROTEUS
  fDin_Fresh();
#endif
}

void fFlash(void)
{
  vFlash++;
  mSetTimerTask(fFlash, 300 _ms);
  //  switch (v_Menu.vMode) {
  //    case EDIT: {
  //        vDinOff ^= 1;
  //        break;
  //      }
  //
  //    default: {
  //        vDinOff = 0;
  //        break;
  //      }
  //  }
}











ISR(BADISR_vect, ISR_NAKED)
{
  // user code here
  reti();
}







u16 fCRC16(u08 * pBuff, u16 nByte)
{
  u16 tmpCRC16;
  tmpCRC16 = 0xffff;

  while (nByte--) {
    tmpCRC16 = _crc16_update(tmpCRC16, *pBuff++);
  }

  return tmpCRC16;
}


void fBuzInit(void)
{
  TCCR2 = 0 << COM21 | 1 << COM20 | mGetT2_Div(4000, 8, 1);
  mPinIn(BUZ);
}
void fBuzOnTime(const u16 t_on)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /
  pFlg->Buzer = 1;
  mPinOut(BUZ);
  mSetTimerTask(fBuzOff, t_on);
}

void fBuzOn(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /
  pFlg->Buzer = 1;
  mPinOut(BUZ);
}

void fBuzOff(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /
  pFlg->Buzer = 0;
  mPinIn(BUZ);
}

inline void fBuzer(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /

  if (pFlg->Buzer) {
    mPinOut(BUZ);
  } else {
    mPinIn(BUZ);
  }
}





