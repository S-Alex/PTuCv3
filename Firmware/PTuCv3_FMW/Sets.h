#ifndef INCLUDE_SETS_H
#define INCLUDE_SETS_H


#include  "../sets_crc16/CRC16_for_set.h "

#define LEVEL_EMPTY 22000
#define LEVEL_FULL  60000

typedef enum {
  SETS_MIN,
  SETS_MID,
  SETS_MAX,
  SETS_USR1,
  SETS_USR2,
  SETS_USR3,
  SETS_USR4,
  SETS_USR5
} eSETS_t;


typedef struct {
  u16 T_Pause;      /* 1 Пауза между подачами топлива [sec] */
  u16 N_Unload;     /* 2 Кол-во оборотов шнека выгрузки топлива в топку горелки [n] */
  u16 T_TEN;        /* 3 Время включения ТЭНа для розжига пеллеты. [sec] */
  u16 Temp1;        /* 4 Температура котла установка [°C] */
  u16 dTemp1;       /* 5 дельта Температуры котла, ошибка [°C]*/
//  u16 N_Grate;      /* 6 Ворошим решетку через заданное количество подач топлива [n] */
//  u16 T_Grate;      /* 7 Ворошим решетку заданное время. [sec] */
  u16 N_Ignition;   /* 8 Кол-во оборотов шнека выгрузки перед розжигом [n] */
  u16 T_Ignition;   /* 9 Время розжига [sec] */
  u16 Power;        /*  */
  u16 CRC;

} Sets_t;

typedef struct {
  u16 AutoRun       ; /**< Автоматический запуск горелки при подаче питания */
  u16 TimeOut       ; /**< Время меню. Время простоя меню, выход без сохранения параметров. */
  u16 BlowTime      ; /**< Время продувки горелки во время дожига остатков топлива */
  u16 Uref          ; /**< Опорное напряжение мВ. 4096 */
  s16 T_Offset      ; /**< Смещение температуры. */
//  u16 ScrewTimeOut  ; /**< Время через которое шнек считать заклиненным, [sec] */
//  u16 T_Alarm       ; /**< Время выдачи сигнала аварии. */
//  u16 Level_Empty   ; /**<  */
//  u16 Level_Full    ; /**<  */

  u16 CRC;
} Sets_com_t;

//{ Настройки для задания температуры по расписанию
#define MAX_SETS_TIMER 8
typedef struct {
  u08 Weeks;
  u08 On_Hour;
  u08 On_Minutes;
  u08 Off_Hour;
  u08 Off_Minutes;
  u08 NoUse;
  s16 TS_Sets;
} Timer_t;

typedef struct {
  Timer_t Timer[MAX_SETS_TIMER];
  u16 CRC;
} Sets_Timer_t ;

extern Sets_Timer_t vSets_Timers;
extern Sets_Timer_t EEMEM evSets_Timers;
//}

extern EEMEM Sets_com_t evSets_com;

extern EEMEM Sets_t evSets_Usr1;




#define PARAM_MAX sizeof(Sets_t)/2
extern  Sets_t vSets;
extern  Sets_com_t vSets_com;

void fSetsRead(void);
void fSetsWrite(void);

#endif // INCLUDE_SETS_H
