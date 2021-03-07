//File: HW_def.h ��� ������� PelletsTorchMicroControl PTuC
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


//#define LED_WR   PORTB,4,1   /**< �����. ����� ������ � ���������� �������� */
//#define FUEL      PORTD,2,1   /**< ����. ������ ������� ������� ��� ������ � ����� */
//#define SCREW     PORTD,4,1   /**< �����. ��������� ����� �������� */
//#define RELE_ST   PORTC,6,1   /**< �����. ����� ������ � ���������� �������� */
//#define ZCD_      PORTD,6,1   /**< ����. �������� ���� */

#define BUZ       PORTB,3,1   /**< �����. ����������������� ���������� */

//{ ===== Global Var =====

volatile u08 rCRC8;

u08 v_OLed;
u08 v_OLed_Manual;
#define LED_STOP      (1<<0) /**< ��������� ������ ������ �����������. "�������" */
#define LED_IGNITION  (1<<2) /**< ��������� ������ ������ �����������. "������" */
#define LED_BURNING   (1<<3) /**< ��������� ������ ������ �����������. "�������" */
#define LED_AFTERBURN (1<<6) /**< ��������� ������ ������ �����������. "�����" */
#define LED_FAULT     (1<<7) /**< ��������� ������ ������ �����������. "������" */
#define LED_GRATE     (1<<5) /**< ��������� ������ ������ �����������. "������" */
#define LED_UNLOAD    (1<<4) /**< ��������� ������ ������ �����������. "��������" */
#define LED_TEN       (1<<1) /**< ��������� ������ ������ �����������. "���" */


u08 v_ORele;
u08 v_ORele_Manual;





/* ����� ����������� ������ 3 */
#define SQ1       PORTC,3,0   /**< ����. �������� SQ1  */
//#define SQ2       PORTA,5,0   /**< ����. �������� SQ2  */
//
#define SQ1_MSK   0x01   /**< ����� ��� ��������� SQ1 */
//#define SQ2_MSK   0x10   /**< ����� ��� ��������� SQ2 */




/* ������ ����������� ������ 3 */
#define RK1      (1<<0) /**< ��� ���������� ������ ���� K1. */
#define RK2      (1<<1) /**< ��� ���������� ������ ���� K2. */
#define RK3      (1<<2) /**< ��� ���������� ������ ���� K3. */
#define RK4      (1<<3) /**< ��� ���������� ������ ���� K4. */
#define RK5      (1<<4) /**< ��� ���������� ������ ���� K5. */
#define RK6      (1<<5) /**< ��� ���������� ������ ���� K6. */
#define RK7      (1<<6) /**< ��� ���������� ������ ���� K7. */
#define RK8      (1<<7) /**< ��� ���������� ������ ���� K8. */

#define K_TEN       RK1 /**< ~~~ ����. */
#define K_FAN       RK2 /**< ~~~ DC ��������� ����������� */
#define K_R_SCREW   RK3 /**< ~~~ DC ��������� �������� �������. ���� �����*/
#define K_L_SCREW   RK4 /**< ~~~ DC ��������� �������� �������. ���� ����*/
#define K_GRATE     RK5 /**< ~~~ DC ��������� ������� ������������ �������. */
#define K_BUNKER    RK6 /**< ~~~ AC ��������� ������ ������� �� �������. */


//{ /* ����������� ������ ������ ���������� */
#define KEY_01    PORTB,0,0
#define KEY_02    PORTB,2,0
#define KEY_03    PORTB,4,0
//} /* ����������� ������ ������ ���������� */








//} ===== Global Var =====






/* ��� ���������� ���� � ��������� ��� ������ �������� ����������
    ����� ���������� � SFR ��������� � �������� 0x00..0x1F
    ��������:
    ���� ���� �� ������������, �� ��� ����� ����� ����� ������������
    ������� �������� ����� (UBRR), �, ���� �� ������������� ������, �� ���
    �������� ���������� ���������� ����� ������������ ������� ������ (EEDR) �
    ������� ������ ������ (EEAR).

  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // ������������� ��������� �� ��������� ������ /
  pFlg->AC_Err=1; // ��������� ����� /
  pFlg->AC_Err=0; // ����� ����� /

*/

#define gFlagsL TWBR

#ifndef gFlagsL
u08 gFlagsL;
#endif

#define mIpFlg() volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL) /* ������������� ��������� �� ��������� ������ */

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
