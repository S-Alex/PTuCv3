/*Заметьте, что !defined(X) предпочтительней, чем #ifndef X.*/
#if !defined(INCLUDE_CONTROL_H)
#define INCLUDE_CONTROL_H
#include  "main.h"
#include  "lib/LedDin.h"
/**
 * \addtogroup grpControl Всё что связанно с управлением.
 * @{
 */

#define     N_ULD_FAULT_TS2 3                /* Кол-во повторов проверки падения температуры */
#define     T_ULD_FAULT_TS2 10                 /* Время подачи шнека. Выгрузка тлеющих углей */
#define     T_WAIT_FAULT_TS2 90                  /* Время повтора опроса датчика температуры */
#define     TEMP_HOT 90                                   /* Критическая температура бункера */


typedef enum {
  UNLD_INIT = 1,
  UNLD_ACT,
  UNLD_CLR,
  UNLD_FILL_BNKR,
  UNLD_WAIT,


} eFSM_Unload_t;

typedef enum {
  CLR_INIT = 1,
  CLR_CCW,        /* counterclockwise */
  CLR_CCW_PAUSE,  /* counterclockwise */
  CLR_CW,         /* clockwise */
  CLR_CW_PAUSE,   /* clockwise */
  CLR_FAULT,      /* clockwise */



} eFSM_CleanScrew_t;

typedef enum {
  //  GRT_NC,
  GRT_INIT = 1,
  GRT_ON,
  GRT_PAUSE,

} eFSM_Grate_t;

typedef enum {
  CLN_INIT = 1,
  CLN_ON,
  CLN_PAUSE,

} eFSM_Clean_t;

typedef enum {
  ALARM_INIT = 1,
  ALARM_ON,
} eFSM_Alarm_t;

typedef struct {
  u16 TS1;        /* Температура котла [°K] */
  u16 TS2;        /* Температура котла [°K] */
  u16 AI_Pellet;  /* Уровень топлива */
  u08 Fuel;     /* Наличие топлива в горелке */
} Param_t;

extern Param_t v_Param;   /* Данные от датчиков */

extern const u08 __flash *pszState;
extern const u08 __flash *pszError;


extern const u08 __flash szFaultCRCc[];
extern const u08 __flash szFaultCRCs[];
extern const u08 __flash szFaultCRC[];
extern const u08 __flash szErrCRCTimer[];


extern u08 v_CntUnld;

extern u08 vSQ_State;        /**< Состояние конечных выключателей SQ2 и SQ1 биты 1 и 0 */
extern u08 SQ1_On_TaskID;    /**< ID задачи при сработке конечного выключателя SQ1 (включение)*/
extern u08 SQ1_Off_TaskID;   /**< ID задачи при сработке конечного выключателя SQ1 (отключение)*/
extern u08 SQ2_On_TaskID;    /**< ID задачи при сработке конечного выключателя SQ2 (включение)*/
extern u08 SQ2_Off_TaskID;   /**< ID задачи при сработке конечного выключателя SQ2 (отключение)*/


#define mLED_On(LED)  v_OLed |= LED
#define mLED_Off(LED) v_OLed &= ~LED
#define mLED_Cpl(LED) v_OLed ^= LED

//#define mRK_On(RKn)  v_ORele |=  RKn
//#define mRK_Off(RKn) v_ORele &= ~RKn

//#define mRK_On(name)  v_ORele |=  (fOuts_GetMsk(##name))
//#define mRK_Off(name) v_ORele &= ~(fOuts_GetMsk(##name))

//#define mRK_On(name)  v_ORele |=  (fOuts_GetMsk(name))
//#define mRK_Off(name) v_ORele &= ~(fOuts_GetMsk(name))

#define mRK_On(name)  v_ORele |=  (name)
#define mRK_Off(name) v_ORele &= ~(name)

/**
 * \~russian
 * Функция реализующая управление. \n
 * Проверку всех параметров и расчет управления.
 * \~english
 * TODO
 * \~
 */
void fControl(void);

//void fGetFuel(void);

/*! \brief Функция преобрасования кода АЦП в температуру от 0 до 100 градусов.
 *
 * Функция - t = ((Uref*adc)/(2^n*a[B/K])) - 273
 *
 * \param [in] adc - переменная кода АЦП.
 */
u16 fGetTempLM335(u16 adc);
u16 fGetTempPt100(u16 adc);

u16 fGetADC_from_TempLM335(u16 Temp);


void f_Test(void);
void fFaultIgnition(void);

void fBuzSound(u08 msk);


void fLed_Fault_On(void);
void fLed_Fault_Off(void);


void fSupply_On(void);
void fSupply_Off(void);

void fScrew_R_On(void);
void fScrew_L_On(void);

void fGrate_On(void);
void fClean_On(void);


void fAlarm_On(void);


void fTEN_On(void);

void fFan_On(void);
void fPump_On(void);
void fWait_Time_2Next(void);

void fManual_Off(void);

void fBunker_Load_TimeOut(void);
void fTEN_AirOn(void);


void f_Test_old(void);

void fRunStop(void);

void fSupply(void);
void fReUnload_On(void);

void fTEN(void);
void fFuelOn(void);
void fTEN_OnTimeLeft(void);
void fFlame(void);
void fSQGet(void);
void fSQInit(void);

void f_Output(void);


void f_Input(void);
void fCntScrew(void);
u08 f_FSM_Unload(eFSM_Unload_t vFSM);
u08 f_FSM_CleanScrew(eFSM_CleanScrew_t vFSM);
u08 f_FSM_Grate(eFSM_Grate_t vFSM);
u08 f_FSM_Clean(eFSM_Clean_t vFSM);
u08 f_FSM_Alarm(u08 vFSM);




u08 f_CheckTempr(void);  /* Контроль границ температурного режима объекта */
void f_T_Critic(void);   /*  */
void fBunker(void);

void fOffAllRele(void);
//void f_IGN_UNLOAD(u08 N_Uld, eSTATE_t Next, u16 Time);



/**@}*/  /* \addtogroup grpControl */


#endif /* End of INCLUDE_CONTROL_H */
