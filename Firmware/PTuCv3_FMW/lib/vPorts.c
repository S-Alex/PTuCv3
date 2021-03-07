//File: vPorts.c
#include "vPorts.h"

/** \ingroup vPorts */
// < ������� ����� ��� ����� ����������� ������
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
// > ������� ����� ��� ����� ����������� ������

/** \ingroup vPorts */
// < ���������� ����������� �����

const u08 __flash vPort0[] = {                                     /* ���� ������ ��� LED7S */
  8,/*< ���-�� ��� � ����������� ����� */
  5, (u16)&PORTD, /* LED_A *< ����� ���� � ����� ����� */
  7, (u16)&PORTD, /* LED_B *< ����� ���� � ����� ����� */
  2, (u16)&PORTD, /* LED_C *< ����� ���� � ����� ����� */
  6, (u16)&PORTB, /* LED_D *< ����� ���� � ����� ����� */
  7, (u16)&PORTB, /* LED_E *< ����� ���� � ����� ����� */
  6, (u16)&PORTD, /* LED_F *< ����� ���� � ����� ����� */
  3, (u16)&PORTD, /* LED_G *< ����� ���� � ����� ����� */
  4, (u16)&PORTD, /* LED_H *< ����� ���� � ����� ����� */
};

const u08 __flash vPort1[] = {
  3,/*< ���-�� ��� � ����������� ����� */
  2, (u16)&PORTB, /* DIG0  *< ����� ���� � ����� ����� */
  4, (u16)&PORTB, /* DIG1  *< ����� ���� � ����� ����� */
  0, (u16)&PORTB, /* DIG2  *< ����� ���� � ����� ����� */

};
const u08 __flash vPort2[] = {
  6,/*< ���-�� ��� � ����������� ����� */
  1, (u16)&PORTB, /* RK_1  *< ����� ���� � ����� ����� */
  1, (u16)&PORTD, /* RK_2  *< ����� ���� � ����� ����� */
  0, (u16)&PORTD, /* RK_3  *< ����� ���� � ����� ����� */
  4, (u16)&PORTC, /* RK_4  *< ����� ���� � ����� ����� */
  5, (u16)&PORTC, /* RK_5  *< ����� ���� � ����� ����� */
  5, (u16)&PORTB, /* RK_6  *< ����� ���� � ����� ����� */

};
const u08 __flash vPort3[] = {
  3,/*< ���-�� ��� � ����������� ����� */
  0, (u16)&PORTB, /* RK_1  *< ����� ���� � ����� ����� */
  2, (u16)&PORTB, /* RK_2  *< ����� ���� � ����� ����� */
  4, (u16)&PORTB, /* RK_3  *< ����� ���� � ����� ����� */
};
// > ���������� ����������� �����

/** \ingroup vPorts
 * ���������� ������ �������(����������) �� ����������� �����
 */
__flash
const u08  * vPorts[] = {
  vPort0,
  vPort1,
  vPort2,
  vPort3
};
// > ���������� ����� �������(����������) �� ����������� �����

//  fOut_vPort(1,vDinCnt);
//  fOut_vPort(0,vDin[vDinCnt]);

/** \ingroup vPorts
 * \brief
 * \param nPort ����� ������������ ����� � ������� #vPorts[]
 * \param Data
 * \param Id_  ������������� ����� \n
 * #IDPORT - ��� ������� � �������� ������� ����� \n
 * #IDDDR - ��� ������� � �������� ����������� ������ ����� \n
 * #IDPIN - ��� ������� � �������� ��������� ������� ����� �����
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
 * \param nPort ����� ������������ ����� � ������� #vPorts[]
 * \param Data
 * \param Id_  ������������� ����� \n
 * #IDPORT - ��� ������� � �������� ������� ����� \n
 * #IDDDR - ��� ������� � �������� ����������� ������ ����� \n
 * #IDPIN - ��� ������� � �������� ��������� ������� ����� �����
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
