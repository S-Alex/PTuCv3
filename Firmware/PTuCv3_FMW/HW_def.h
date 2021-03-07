//File: HW_def.h для проекта PelletsTorchMicroControl PTuC
#ifndef HW_DEF_H_INCLUDED
#define HW_DEF_H_INCLUDED

#include  "RTOSA/types.h"

#define RIGHTS_TIMEOUT 650 _s


//#define "MacroSA.h"
//#define TEST_MENU
//#define PROTEUS

//;< Define Pin for Proteus debug
#ifdef PROTEUS
#define Stop PORTC,0,1
#endif
//;> Define Pin for Proteus debug

//;< Define mStop for Proteus debug
#ifdef PROTEUS
#define mStop mPinOut(Stop); mPinClr(Stop); mPinSet(Stop);
#else
#define mStop
#endif
//;> Define mStop for Proteus debug

#define T_BUNKER (30 _s)


//#define LED_WR   PORTB,4,1   /**< Выход. Строб записи в сдвигающие регистры */
//#define FUEL      PORTD,2,1   /**< Вход. Датчик наличия топлива для подачи в топку */
//#define SCREW     PORTD,4,1   /**< Выход. Включение шнека выгрузки */
//#define RELE_ST   PORTC,6,1   /**< Выход. Строб записи в сдвигающие регистры */
//#define ZCD_      PORTD,6,1   /**< Вход. Детектор нуля */

#define BUZ       PORTB,3,1   /**< Выход. Пьезокерамический излучатель */

//{ ===== Global Var =====

volatile u08 rCRC8;

u08 v_OLed;
u08 v_OLed_Manual;
#define LED_STOP      (1<<0) /**< Индикатор режима работы контроллера. "Останов" */
#define LED_IGNITION  (1<<2) /**< Индикатор режима работы контроллера. "Розжиг" */
#define LED_BURNING   (1<<3) /**< Индикатор режима работы контроллера. "Горение" */
#define LED_AFTERBURN (1<<6) /**< Индикатор режима работы контроллера. "Дожиг" */
#define LED_FAULT     (1<<7) /**< Индикатор режима работы контроллера. "Авария" */
#define LED_GRATE     (1<<5) /**< Индикатор режима работы контроллера. "Подача" */
#define LED_UNLOAD    (1<<4) /**< Индикатор режима работы контроллера. "Выгрузка" */
#define LED_TEN       (1<<1) /**< Индикатор режима работы контроллера. "ТЭН" */


u08 v_ORele;
u08 v_ORele_Manual;





/* Входы контроллера версии 3 */
#define SQ1       PORTC,3,0   /**< Вход. Конечник SQ1  */
//#define SQ2       PORTA,5,0   /**< Вход. Конечник SQ2  */
//
#define SQ1_MSK   0x01   /**< Маска для конечника SQ1 */
//#define SQ2_MSK   0x10   /**< Маска для конечника SQ2 */




/* Выходы контроллера версии 3 */
#define RK1      (1<<0) /**< Бит управления ключом реле K1. */
#define RK2      (1<<1) /**< Бит управления ключом реле K2. */
#define RK3      (1<<2) /**< Бит управления ключом реле K3. */
#define RK4      (1<<3) /**< Бит управления ключом реле K4. */
#define RK5      (1<<4) /**< Бит управления ключом реле K5. */
#define RK6      (1<<5) /**< Бит управления ключом реле K6. */
#define RK7      (1<<6) /**< Бит управления ключом реле K7. */
#define RK8      (1<<7) /**< Бит управления ключом реле K8. */

#define K_TEN       RK1 /**< ~~~ ТЭНа. */
#define K_FAN       RK2 /**< ~~~ DC двигателя вентилятора */
#define K_R_SCREW   RK3 /**< ~~~ DC двигателя выгрузки топлива. Шнек право*/
#define K_L_SCREW   RK4 /**< ~~~ DC двигателя выгрузки топлива. Шнек лево*/
#define K_GRATE     RK5 /**< ~~~ DC двигателя привода колосниковой решетки. */
#define K_BUNKER    RK6 /**< ~~~ AC двигателя подачи топлива из бункера. */


//{ /* Определение портов кнопок управления */
#define KEY_01    PORTB,0,0
#define KEY_02    PORTB,2,0
#define KEY_03    PORTB,4,0
//} /* Определение портов кнопок управления */








//} ===== Global Var =====






/* Для уменьшения кода и ускорения его работы флаговые переменные
    можно разместить в SFR регистрах с адресами 0x00..0x1F
    Например:
    Если УАПП не используется, то для таких целей можно использовать
    регистр скорости связи (UBRR), а, если не задействовано ЭСППЗУ, то для
    хранения глобальных переменных можно использовать регистр данных (EEDR) и
    регистр адреса ЭСППЗУ (EEAR).

  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /
  pFlg->AC_Err=1; // Установка флага /
  pFlg->AC_Err=0; // Сброс флага /

*/

#define gFlagsL TWBR

#ifndef gFlagsL
u08 gFlagsL;
#endif

#define mIpFlg() volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL) /* Инициализация указателя на структуру флагов */

typedef struct sFlg {
  unsigned char FuelOK:     1; /* Bit 0 */
  unsigned char CfgOK:      1; /* Bit 1 */
  unsigned char Buzer:      1; /* Bit 2 */
  unsigned char Screw:      1; /* Bit 3 */
  unsigned char Grate:      1; /* Bit 4 */
  unsigned char BIT_5:      1; /* Bit 5 */
  unsigned char FRAMEOK:    1; /* Bit 6 */
  unsigned char ZCD:        1; /* Bit 7 */
} volatile Flg_t;

#endif // HW_DEF_H_INCLUDED
