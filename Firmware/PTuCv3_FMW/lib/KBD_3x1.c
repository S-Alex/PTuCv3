//;File KBD_3x1.c
//;Updated: "2015-07-16"
#include <avr/io.h>
#include "RTOSA\types.h"
#include  "MacroSA.h"

#include  "main.h"
#include "KBD_3x1.h"
t_KBD v_KBD;



void fKBD_Init(void)
{
  v_KBD.Last = 0;
  v_KBD.AutoRep = KEY_TIME_REPEAT;
}

u08 fKBD_Scan(void)
{
  u08 tmp_v, tmp_k1, tmp_k2, tmp_k3;
  //  fOut_vPort(3, 0x00, IDDDR);                                         /* ���� ������ �� ���� */
  //  fOut_vPort(3, 0xff, IDPORT);                         /* ���������� ������������� ��������� */
  //  mDelay_us(4);
  //  tmp_v = fIn_vPort(3, IDPIN);                              /* ������ ��������� ������ ����� */
  //  tmp_v ^= 0b0111;
  //  fOut_vPort(3, 0x00, IDPORT);                          /* ��������� ������������� ��������� */
  //  fOut_vPort(3, 0xff, IDDDR);                                        /* ���� ������ �� ����� */
  //static
#define volatile
#undef volatile
  asm volatile("":::"memory");
  mPinIn(KEY_01);
  mPinIn(KEY_02);
  mPinIn(KEY_03);
  mPinSet(KEY_01);
  mPinSet(KEY_02);
  mPinSet(KEY_03);
  mDelay_us(4);
#define volatile
#undef volatile
  asm volatile("":::"memory");
  tmp_k1 = mPinIs(KEY_01);
  tmp_k2 = mPinIs(KEY_02);
  tmp_k3 = mPinIs(KEY_03);
  tmp_v = tmp_k1 >> 0; /* Bit 0 to Bit 0 */
  tmp_v |= tmp_k2 >> 1; /* Bit 2 to Bit 1 */
  tmp_v |= tmp_k3 >> 2; /* Bit 4 to Bit 2 */
  tmp_v ^= 0b111;
  mPinClr(KEY_01);
  mPinClr(KEY_02);
  mPinClr(KEY_03);
  mPinOut(KEY_01);
  mPinOut(KEY_02);
  mPinOut(KEY_03);
  return tmp_v;
}

void fKBD_Exe(void)
{
  u08 tmpKey;

  if (v_KBD.wt == 0) {
    return;
  }

  v_KBD.wt = 0;
  tmpKey = fKBD_Scan();

  if (v_KBD.Last == tmpKey) {
    v_KBD.Tick++;

    if (v_KBD.Tick == KEY_TIME_SHORT) {
      v_KBD.act = v_KBD.Last | 0x40;
      return;
    }

    if (v_KBD.Tick > KEY_TIME_REPEAT) {                                    /* ������� ������ */
      v_KBD.AutoRep += 2;

      if (v_KBD.AutoRep > KEY_TIME_AREPEAT2) {       /* �������� ����������� ��� ����������� */
        v_KBD.AutoRep = KEY_TIME_AREPEAT2;
      }

      v_KBD.Tick = v_KBD.AutoRep;
      //v_KBD.act = v_KBD.Last | 0x40;

      if (tmpKey != 0) {
        v_KBD.act = v_KBD.Last | 0x40;
      } else {
        v_KBD.Tick = 0;
      }

      return;
    }

    if (tmpKey == 0) {
      v_KBD.Tick = 0;
    }
  }

  if (v_KBD.Last != tmpKey) {
    if ((v_KBD.Tick > KEY_TIME_SHORT) && (v_KBD.Tick < KEY_TIME_AREPEAT1)) {
      v_KBD.Tick = 0;
      //v_KBD.Last = tmpKey;
      v_KBD.act = v_KBD.Last;
      return;
    }

    if ((v_KBD.Tick > KEY_TIME_AREPEAT1)) {
      v_KBD.Tick = 0;
      //v_KBD.Last = tmpKey;
      v_KBD.Last |= 0x80;
      v_KBD.act = v_KBD.Last;
      return;
    }

    v_KBD.AutoRep = KEY_TIME_AREPEAT1;
    v_KBD.Tick = 0;
    v_KBD.Last = tmpKey;
    return;
  }

  return;
}




u08 fKBD_GetKey(void)
{
  eKBD_MSG tmpMSG;

  if (v_KBD.act) {
    switch (v_KBD.act & 0b00111111) {
      case 0b0100: {
          //case 0b0010: {
          if (v_KBD.act & 0x40) {
            tmpMSG = KBD_UP;                                             /* �������� ������� */
          } else {
            tmpMSG = KBD_NO;                                            /* ��������� ������� */
          }

          break;
        }

      case 0b0010: {
          //case 0b0100: {
          if (v_KBD.act & 0x40) {
            tmpMSG = KBD_DN;                                             /* �������� ������� */
          } else {
            tmpMSG = KBD_NO;                                            /* ��������� ������� */
          }

          break;
        }

      case 0b0001: {
          if (v_KBD.act & (0x40)) {
            tmpMSG = KBD_SWDN ;                                           /* �������� ������� */
          } else {
            tmpMSG = KBD_SWUP;                                       /* ��������� ������� */
          }

          break;
        }

      default: {
          tmpMSG = KBD_NO;
        }
        break;
    }

    v_KBD.act = 0;
    fBuzOnTime(20 _ms);
    return tmpMSG;
  } else {
    return KBD_NO;
  }
}
