//File RTOSA.h
//RTOSA Ver. 0.0.0.1 - S_Alex 2011.
//This file is part of the RTOSA distribution.
//Updated: "2011-04-05" "14:27"

#ifndef RTOSA_H
#define RTOSA_H 1


#include  <avr/io.h>
#include  <stdlib.h>
#include  <avr/interrupt.h>
#include  <util/atomic.h>

#include  "types.h"

#include  "../MacroSA.h"
#include  "../HW_def.h"


//##############################################################################
#ifndef TIMERCNTRS_H
//#include  "RTOSA\TimerCntrs.h"
#include  "TimerCntrs.h"
#endif





;
//##############################################################################
/**

 * \ingroup grpRTOSA
 * \~russian
 * \addtogroup grpRTOSA_set Параметры настройки операционной системы.
 * \~english
 * \addtogroup grpRTOSA_set TODO
 * \~
 */


/** \ingroup grpRTOSA_set
 * @{
 */

/**
 * \~russian
 * \brief
 * Размер очереди задач. Возможные значения 2, 4, 8, 16.
 *
 * Определяет максимальное колличество задач находящихся в отложеном состоянии. \n
 * Т.е. задач которые ждут своей очереди.
 * \~english
 * TODO
 * \~
 * \~russian
 * \note При иных значениях работоспособность программы не гарантируется.
 * \~english
 * \note TODO
 * \~
 */
#define TASKQUEUESIZE   8
/**
 * \~russian
 * \brief
 * Количество одновременно работающий таймеров.
 *
 * Определяет максимальное колличество одновременно работающий таймеров \n
 * \~english
 * TODO
 * \~

 * \~russian
 * \note При иных значениях работоспособность программы не гарантируется.
 * \~english
 * \note TODO
 * \~
 */
#define TIMERSPOOLSIZE  8

/**
 * \~russian
 * \brief
 * Частота работы таймерной службы.
 *
 * Определяет частоту опроса таймеров т.е. шаг квантования по времени. \n
 * \~english
 * TODO
 * \~
 * T = 1/#FreqOS.
 */
#define FreqOS 100UL

/**
 * \~russian
 * Определения для облегчения задания времени таймеров.
 * \~english
 * TODO
 * \~
 * \code
 * mSetTimerTask(fIdle,100 _ms);
 * \endcode
 */
#define _ms *FreqOS/1000

/**
 * \~russian
 * Определения для облегчения задания времени таймеров.
 * \~english
 * TODO
 * \~
 * \code
 * mSetTimerTask(fIdle,1 _s);
 * \endcode
 */
#define _s *FreqOS

/** @} */

#define MAX_TASK 0xFF

typedef void (*TPTR)(void);

extern const TPTR __flash TaskProcs[];


void krSendTask(u08 TaskID);
void krProcessTaskQueue(void);
void krClearTimers(void);
void krClearTaskQueue(void);

void krSetTimer(u08 TaskID, u16 Time);
void krTimerRun(u08 TaskID,u08 Stp);

u16 krGetTimer(u08 TaskID);

void krClrTimer(u08 TaskID);

void krMemFill(u08 *aMem, u08 bVal, u08 bSize);
//#define krMemFill(aMem, bVal, bSize)  memset(aMem, bVal, bSize)

void krMemCopyR2R(u08* aMemS, u08 *aMemD, u08 bSize);
void krMemCopyF2R(const u08 __flash *aMemS, u08* aMemD, u08 bSize);
//inline void mTimerService(void);
inline u08 mInitTicOS(const u64 F_T0_Ovf);
inline void krRTOSA_Init(void);
u08 krRand(void);

void krCallTaskID(u08 TaskID);


// Структура информации о таймерах
typedef struct TIMERSPOOL {
  u08 TaskID; // ID задачи
  u08 TStp;                                                             /* Остановка таймера */
  u16 Time;   // Выдержка
} T_TIMERSPOOL, *pTIMERSPOOL;



//###############################################################################
//######################## Макросы ядра РТОС ####################################
//###############################################################################





//#define  Tpod  7500 ms
//#define  Tkz   50 ms
//#define  Tstick  2000 ms
//#define  TReklama  2000 ms
//#define  TMenu   2000 ms


//#define dTask(fTask)  u16 TP_##fTask = &fTask

//#define Task(fTask) u16 TP_##fTask
#define aTask(fTask)  fTask

#define Task(fTask)   void * fTask
//#define aTask(fTask) fTask

/* #define GetTaskID(func)\
//  (u08)((u16)(&TaskProcs.TP_ ## func)-(u16)(&TaskProcs))/2
*/

/*#define GetTaskID(func)\
//  (u08)((u16)(&TaskProcs.func)-(u16)(&TaskProcs))/2
*/

/** TODO (Admin#1#): GetTaskID */

#define GetTaskID(func)\
  (u08) (offsetof(TaskProcsPtr_t,func)/sizeof(void*))


//mSetTimerTask({ProcName},{Time (min: 1// max: 65535UL)})
//Example: mSetTimerTask(fInitRisCurrentI,50 ms);
#define mSetTimerTask(ProcName,Time)\
  {\
    typedef char Time_out_range [(((Time) > 65535UL) || ((Time)==0))?-1:1];\
    krSetTimer(GetTaskID(ProcName),Time);\
  }

/**
 mGetTimerTask({ProcName}) \n
 Example:
 \code
 u16 Time_fIdle = mGetTimerTask(fIdle);
 \endcode
*/
#define mGetTimerTask(ProcName) krGetTimer(GetTaskID(ProcName));

//mSetTimerTaskID({TaskID},{Time (min: 1// max: 65535UL)})
//Example: mSetTimerTaskID(GetTaskID(fInitRisCurrentI),50 ms);
#define mSetTimerTaskID(TaskID,Time)\
  {\
    typedef char Time_out_range [(((Time) > 65535UL) || ((Time)==0))?-1:1];\
    krSetTimer(TaskID,Time);\
  }


//mClrTimerID({TaskID})
//Example: mClrTimerID(GetTaskID(fInitRisCurrentI));
#define mClrTimerID(TaskID)\
  krClrTimer(TaskID)

//mClrTimer({ProcName})
//Example: mClrTimer(fInitRisCurrentI);
#define mClrTimer(ProcName)\
  krClrTimer(GetTaskID(ProcName))


//mSendTask({ProcName})
//Example: mSendTask(fInitRisCurrentI);
#define mSendTask(ProcName)\
  krSendTask(GetTaskID(ProcName))



volatile u08 TaskQueue[TASKQUEUESIZE]; // Адрес очереди задач в SRAM
volatile T_TIMERSPOOL TimersPool[TIMERSPOOLSIZE];  // Очередь таймеров

extern u08 r_TaskS;
extern u08 r_CntTask;
extern u08 T0_Reload;

extern u08 r_RND;
extern u32 vOS_Tick;



/**
 * \~russian
 * \brief
 * Расчет предделителя таймера.
 *
 * Запуск таймера с расчитанным предделителем.
 * \~english
 * TODO
 * \~
 * \~russian
 * \return Значение которое используется для презагрузки таймера.
 * \note Или значение для регистра OCR таймера. Если таковой есть.
 * \~english
 * \note TODO
 * \~
 */
inline u08 mInitTicOS(const u64 F_T0_Ovf)
{
#define  N_Cnt 8
#define  FnMin  0
  u08   Val_TCCR0;
  u16  PreDiv;
  u16 PreDivMin = F_CPU / (F_T0_Ovf * ((1 << N_Cnt) - FnMin));
#if   defined(__AVR_ATmega8__)\
    ||defined(__AVR_ATmega16__)\
    ||defined(__AVR_ATmega32__)\
    ||defined(__AVR_ATmega64__)\
    ||defined(__AVR_ATtiny261__)

  if (PreDivMin < 1) {
    PreDiv = 1;
    Val_TCCR0 = T0Div1;
  } else if (PreDivMin < 8) {
    PreDiv = 8;
    Val_TCCR0 = T0Div8;
  } else if (PreDivMin < 64) {
    PreDiv = 64;
    Val_TCCR0 = T0Div64;
  } else if (PreDivMin < 256) {
    PreDiv = 256;
    Val_TCCR0 = T0Div256;
  } else if (PreDivMin < 1024) {
    PreDiv = 1024;
    Val_TCCR0 = T0Div1024;
  }

#if defined(__AVR_ATtiny261__)
  TCCR0A = 0;
  TCCR0B = Val_TCCR0 & 0b111;
#elif defined(__AVR_ATmega32__)\
    ||defined(__AVR_ATmega16__)
  // FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
  TCCR0 |= (1 << WGM01) | (0 << WGM00) | (Val_TCCR0 & 0b111);
#else
  TCCR0 |= Val_TCCR0 & 0b111;
#endif
#else
#error "Контроллер не поддерживается"
#endif
  u08 tmp;
  tmp = (F_CPU / (PreDiv * F_T0_Ovf));
  return tmp;
}

/**
 * \~russian
 * \brief
 * Запуск операционной системы.
 *
 * Очистка очередей задач и таймеров. Настройка таймеров.
 * \~english
 * TODO
 * \~
 * \~russian
 * \note Для отсчета времени используется Timer/Counter0. \n
 * Используется прерывание по переполнению или OVF совпадению OCR таймера.
 * \~english
 * \note TODO
 * \~
 */
inline void krRTOSA_Init(void)
{
  r_TaskS = 0;        // Очистить регистр
  r_CntTask = 0;      // Очистить кол-во задач стоящих в очереди событий
  krClearTimers();    // Очистить список таймеров РТОС
  krClearTaskQueue(); // Очистить очередь событий РТОС
  T0_Reload = 256UL - mInitTicOS(FreqOS);
#if defined(__AVR_ATmega8__)
  TIMSK |= (1 << TOIE0); //Bit 0 - TOIE0: Timer/Counter0 Overflow Interrupt Enable
#elif   defined(__AVR_ATmega32__)\
      ||defined(__AVR_ATmega64__)\
    ||defined(__AVR_ATmega16__)
  OCR0 = 256 - T0_Reload;
  TIMSK |= (1 << OCIE0); //Bit 1 - OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
#elif defined(__AVR_ATtiny261__)
  //TIMSK |= (1<<OCIE0A);//Bit 1 - OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
#endif
}

void krCallTaskID(u08 TaskID);

#include  "Debug.h"


#endif // RTOSA_H





//S_Alex



