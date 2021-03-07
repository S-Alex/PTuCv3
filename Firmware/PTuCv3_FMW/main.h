/*Заметьте, что !defined(X) предпочтительней, чем #ifndef X.*/
#if !defined(INCLUDE_MAIN_H)
#define INCLUDE_MAIN_H
#include  <h:\avr\include\stdio.h>
#include  <h:\avr\include\stdlib.h>
//#include  <h:\avr\include\time.h>
#include  <h:\avr\include\avr\eeprom.h>
#include  <h:\avr\include\util\crc16.h>
#include  <h:\avr\include\avr\wdt.h>
#include  <h:\avr\include\string.h>
#include  "RTOSA\RTOSA.h"
#include  "tasks.h"
#include  "HW_def.h"


#include  "lib\ADC.h"

#include  "lib\MenuHAL.h"
#include  "lib\bcd.h"
#include  "Menu.h"
#include  "control.h"
#include  "Sets.h"
#include  "lib\KBD_3x1.h"



#include  "lib/LedDin.h"
#include  "lib/vPorts.h"


#include  "version.h"

#include  "Sets.h"

#ifndef PSTR
# define PSTR(s) (__extension__({static const u08 __flash __c[] = (s); &__c[0];}))
#endif

#ifndef PFSTR
# define PFSTR(s) {const u08 __flash __c[] = (s); &__c[0];}
#endif

#include "lib/xitoa.h"

#define SERVICE_MENU
//#define NORMAL 0
//#define PROGRAMM 1
//#define SAVE 2
typedef enum {
  STOP,         /**< #LED_STOP */
  BNKR_LOAD,
  IGN_UNLOAD,                                 /**< Выгрузка топлива в горелку перед розжигом */
  IGN_TEN,                                    /**< */
  IGN_TEN_ULD_5MIN,                           /**< */
  IGN_TEN_ULD_10MIN,                          /**< */
  IGN_ULD_12MIN,                          /**< */
  IGNITION,     /**< #LED_IGNITION */

  BURNING,      /**< #LED_BURNING */
  BRN_BNKR_FILL,
  BRN_UNLOAD,   /**< #LED_BURNING & LED_UNLOAD */
  BRN_GRATE,   /**< #LED_BURNING */

  AFTERBURN,  /**< #LED_AFTERBURN */
  FAULT,      /**< #LED_FAULT */
  FAULT_SCREW,      /**< #LED_FAULT */
  FAULT_TS2,      /**< Перегрев корпуса. Выгрузка 10 сек.*/
  FAULT_TS2_1,    /**< Перегрев корпуса. Ожидание падения температуры 3 мин. Повтор 5 раз с FAULT_TS2*/
  FAULT_TS2_2,    /**< Перегрев корпуса. Ожидание падения температуры 3 мин. Повтор 5 раз с FAULT_TS2*/
  FAULT_TS2_3,    /**< Перегрев корпуса. Ожидание падения температуры 3 мин. Повтор 5 раз с FAULT_TS2*/
  FAULT_LOAD,
//  COOLING,       /**< #LED_BURNING Flashing */
  AUTORUN,       /**<  */
  TEST,
  WAIT,

} eSTATE_t;


typedef struct {
  u16 T_Pause;      /* 1 Пауза между подачами топлива [sec] */
  u16 N_Unload;     /* 2 Кол-во оборотов шнека выгрузки топлива в топку горелки [n] */
  u16 ADC_Temp;
  u16 Temp;
  u16 Kpow;
} RegParam_t;

extern RegParam_t vRegParam;

extern  eSTATE_t vState;
extern  eSTATE_t vStateForWait;

extern  eSTATE_t vStateNext;
extern u16 vStateNextTime;

extern u16 vInType;

extern u08 vFlame;

extern u08 vFlash;
extern u08 v_N_Unload;
extern u08 v_cnt_FultTS2_Unload;


void fIdle(void);
void fFlash(void);





void fBuzInit(void);
void fBuzOnTime(const u16 t_on);

void fBuzOn(void);
void fBuzOff(void);
void fBuzer(void);




u16 fCRC16(u08 * pBuff, u16 nByte);

void f_Go2IGN_UNLOAD(u08 N_Uld, eSTATE_t Wait2Next, eSTATE_t NextTime,u16 Time);




#endif /* End of INCLUDE_MAIN_H */
