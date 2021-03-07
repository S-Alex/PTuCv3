#include  "main.h"



#ifndef PSTR
# define PSTR(s) (__extension__({static const u08 __flash __c[] = (s); &__c[0];}))
#endif

u08 szParamVal_Buf[8];
u08 szParamName_Buf[8];
const char __flash szt[]  = {S_t, S_BLNK, S_BLNK};


//const char __flash fmt_3d[] = "%03d";
const char __flash fmt_3u[] = "%03u";

void fMenu(void)
{
  mSetTimerTask(fMenu, 71 _ms);
  fControl();
  //  fStrScroll_Run(1, &szMenu_SStr, &v_LCDBuf[0], 10, 0);
  //  fStrScroll_Run(1, "01234567890", &v_LCDBuf[0], 9, 0);
  eKBD_MSG tmpMSG;
  tmpMSG = fKBD_GetKey();

  if (tmpMSG != KBD_NO) {
    mSetTimerTask(fMenuInit, vSets_com.TimeOut * FreqOS);

    switch (vState) {
      case FAULT_TS2:
      case FAULT_TS2_1:
      case FAULT_SCREW:
      case FAULT: {
          vState = STOP;
          break;
        }

      case IGNITION:
      case IGN_TEN: {
          vState = vStateNext;
          return;
          break;
        }

      case AUTORUN: {
          mClrTimer(fRunStop);
          vState = STOP;
          break;
        }

      default: {
        }
        break;
    }

    if (v_Menu.vMode == IDLE) {
      v_Menu.vMode = NORMAL;
    } else {
      switch (tmpMSG) {
        case KBD_UP: {
            if (vState == STOP) fMenuSendMsg(MSG_NEXT);

            break;
          }

        case KBD_DN: {
            if (vState == STOP) fMenuSendMsg(MSG_PREV);

            break;
          }

        case KBD_SWDN: {
            fMenuSendMsg(MSG_SWDN);
            break;
          }

        case KBD_SWUP: {
            fMenuSendMsg(MSG_SWUP);
            break;
          }

        default: {
            break;
          }
      }/* switch (tmpMSG) */
    }
  }

  krCallTaskID(v_Menu.TaskID);

  switch (v_Menu.vMode) {
    case IDLE: {
        fPrintState();
        memcpy(vDinam, szParamVal_Buf, 3);
        break;
      }

    case NORMAL: {
        if (vFlash & 0b01) {
          memcpy(vDinam, szParamName_Buf, 3);
        } else {
          memcpy(vDinam, szParamVal_Buf, 3);
        }

        break;
      }

    case EDIT: {
        memcpy(vDinam, szParamVal_Buf, 3);
        break;
      }
  }

  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */

  if (pFlg->FuelOK == 0) {
    vDinam[2] |= S_Dot;
  }

  if (pFlg->Screw == 0) {
    vDinam[0] |= S_Dot;
  }
}





void fPrintParams(u16 Prm)
{
  fPrint2LED(Prm);
}


void fPrint2LED(u16 val)
{
  xsprintf((char*)szParamVal_Buf, fmt_3u, val);
  fASCII2_LED(szParamVal_Buf, 3);
}

void fASCII2_LED(u08 *pBuf, u08 Size)
{
  u08 cnt = 0;
  u08 tmp;

  while (cnt < Size) {
    tmp = fB27S(*pBuf - '0');
    *pBuf = tmp;
    cnt++;
    pBuf++;
  }
}


void fPrintState(void)
{
  switch (vState) {
    case FAULT_SCREW:
    case FAULT_TS2:
    case FAULT: {
        krMemCopyF2R(pszError, szParamVal_Buf, 3);
        break;
      }

    case IGN_UNLOAD:
    case BRN_UNLOAD: {
        u08 LeftUnload;

        if (v_N_Unload >= v_CntUnld) {
          LeftUnload = v_N_Unload - v_CntUnld;
        } else {
          LeftUnload = 0;
        }

        fPrintParams(LeftUnload);
        szParamVal_Buf[0] = S_n;
        break;
      }

    case IGN_TEN:
    case IGNITION: {
        u16 tmpTime;
        u08 tmpMin;
        u08 tmpSec;
        tmpTime = krGetTimer(TimerTaskID);

        if (tmpTime) {
          tmpTime /= FreqOS;
          tmpMin  = tmpTime / 60;
          tmpSec = tmpTime % 60;
          fPrintParams(tmpMin * 100 + tmpSec);

          if ((vFlash & 0b001)) {
            szParamVal_Buf[0] ^= S_Dot;
          }
        } else {
          fPrintParams(v_Param.TS1 - 273);

        }

        break;
      }

    default: {
        fPrintParams(v_Param.TS1 - 273);
        break;
      }
  }

  //  if ((vFlash & 0b1) == 0x01) {
  //    krMemCopyF2R(pszState, szParamVal_Buf, 3);
  //  }
}

