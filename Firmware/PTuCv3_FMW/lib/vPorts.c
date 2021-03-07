//File: vPorts.c
#include "vPorts.h"

/** \ingroup vPorts */
// < Ѕитовые маски дл€ пинов виртуальных портов
__flash
const u08  vBits[] = {
  1 << 0,
  1 << 1,
  1 << 2,
  1 << 3,
  1 << 4,
  1 << 5,
  1 << 6,
  1 << 7
};
// > Ѕитовые маски дл€ пинов виртуальных портов

/** \ingroup vPorts */
// < ќпредел€ем виртуальные порты

const u08 __flash vPort0[] = {                                     /* ѕорт данных дл€ LED7S */
  8,/*<  ол-во бит в виртуальном порте */
  5, (u16)&PORTD, /* LED_A *< номер бита и адрес порта */
  7, (u16)&PORTD, /* LED_B *< номер бита и адрес порта */
  2, (u16)&PORTD, /* LED_C *< номер бита и адрес порта */
  6, (u16)&PORTB, /* LED_D *< номер бита и адрес порта */
  7, (u16)&PORTB, /* LED_E *< номер бита и адрес порта */
  6, (u16)&PORTD, /* LED_F *< номер бита и адрес порта */
  3, (u16)&PORTD, /* LED_G *< номер бита и адрес порта */
  4, (u16)&PORTD, /* LED_H *< номер бита и адрес порта */
};

const u08 __flash vPort1[] = {
  3,/*<  ол-во бит в виртуальном порте */
  2, (u16)&PORTB, /* DIG0  *< номер бита и адрес порта */
  4, (u16)&PORTB, /* DIG1  *< номер бита и адрес порта */
  0, (u16)&PORTB, /* DIG2  *< номер бита и адрес порта */

};
const u08 __flash vPort2[] = {
  6,/*<  ол-во бит в виртуальном порте */
  1, (u16)&PORTB, /* RK_1  *< номер бита и адрес порта */
  1, (u16)&PORTD, /* RK_2  *< номер бита и адрес порта */
  0, (u16)&PORTD, /* RK_3  *< номер бита и адрес порта */
  4, (u16)&PORTC, /* RK_4  *< номер бита и адрес порта */
  5, (u16)&PORTC, /* RK_5  *< номер бита и адрес порта */
  5, (u16)&PORTB, /* RK_6  *< номер бита и адрес порта */

};
const u08 __flash vPort3[] = {
  3,/*<  ол-во бит в виртуальном порте */
  0, (u16)&PORTB, /* RK_1  *< номер бита и адрес порта */
  2, (u16)&PORTB, /* RK_2  *< номер бита и адрес порта */
  4, (u16)&PORTB, /* RK_3  *< номер бита и адрес порта */
};
// > ќпредел€ем виртуальные порты

/** \ingroup vPorts
 * ќпредел€ем массив адресов(указателей) на виртуальные порты
 */
__flash
const u08  * vPorts[] = {
  vPort0,
  vPort1,
  vPort2,
  vPort3
};
// > ќпредел€ем масив адресов(указателей) на виртуальные порты

//  fOut_vPort(1,vDinCnt);
//  fOut_vPort(0,vDin[vDinCnt]);

/** \ingroup vPorts
 * \brief
 * \param nPort Ќомер виртуального порта в массиве #vPorts[]
 * \param Data
 * \param Id_  »дентификатор порта \n
 * #IDPORT - дл€ доступа к регистру защЄлке порта \n
 * #IDDDR - дл€ доступа к регистру направлени€ данных порта \n
 * #IDPIN - дл€ доступа к регистру состо€ни€ входных линий порта
 * \return -
 *
 */
void fOut_vPort(u08 nPort, u08 Data, ID_Port_t Id_)
{
  u08 tmp;
  //volatile
  u08 pPORT;
  volatile const __flash u08 *pvPort;
  u08 BitMsk;
  u08 BitCnt;
  u08 BitMskD;
  pvPort = vPorts[nPort];
  BitCnt = *pvPort;
  pvPort++;
  BitMskD = 1;

  while (BitCnt) {
    BitMsk = vBits[*pvPort];
    pvPort++;
    pPORT = *pvPort - Id_;
    pvPort++;
    tmp = *(u08*)pPORT;

    if (Data & BitMskD) {
      tmp |= BitMsk;
    } else {
      tmp &= ~BitMsk;
    }

    *(u08*)pPORT = tmp;
    BitMskD <<= 1;
    BitCnt--;
  }
}
/** \ingroup vPorts
 * \brief
 * \param nPort Ќомер виртуального порта в массиве #vPorts[]
 * \param Data
 * \param Id_  »дентификатор порта \n
 * #IDPORT - дл€ доступа к регистру защЄлке порта \n
 * #IDDDR - дл€ доступа к регистру направлени€ данных порта \n
 * #IDPIN - дл€ доступа к регистру состо€ни€ входных линий порта
 * \return -
 *
 */
u08 fIn_vPort(u08 nPort, ID_Port_t Id_)
{
  u08 tmp;
  u08 Data;
  //volatile
  u08 pPORT;
  volatile const __flash u08 *pvPort;
  u08 BitMsk;
  u08 BitCnt;
  u08 BitMskD;
  pvPort = vPorts[nPort];
  BitCnt = *pvPort;
  pvPort++;
  BitMskD = 1;
  Data = 0;

  while (BitCnt) {
    BitMsk = vBits[*pvPort];
    pvPort++;
    pPORT = *pvPort - Id_;
    pvPort++;
    tmp = *(u08*)pPORT;

    if (tmp & BitMsk) {
      Data |= BitMskD;
    }

    BitMskD <<= 1;
    BitCnt--;
  }

  return Data;
}

#if 0

void fOut_pvPort(const u08 __flash *pvPort, u08 Data, ID_Port_t Id_)
{
  u08 tmp;
  //volatile
  u08 pPORT;
  u08 BitMsk;
  u08 BitCnt;
  u08 BitMskD;
  BitCnt = *pvPort;
  pvPort++;
  BitMskD = 1;

  while (BitCnt) {
    BitMsk = vBits[*pvPort];
    pvPort++;
    pPORT = *pvPort - Id_;
    pvPort++;
    tmp = *(u08*)pPORT;

    if (Data & BitMskD) {
      tmp |= BitMsk;
    } else {
      tmp &= ~BitMsk;
    }

    *(u08*)pPORT = tmp;
    BitMskD <<= 1;
    BitCnt--;
  }
}
#endif // 0



//;S_Alex
