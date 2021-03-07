#include  "control.h"
/* 06.05.2015 00:44
 Добавлено:
  очистка таймера mClrTimer(fMenuInit); в функциях:
    fUnload_On(void);
    fSupply_Off(void);
  устраняет ошибку при истечении редактирования меню,
*/


u08 vSQ_State;
u08 SQ1_On_TaskID;
u08 SQ1_Off_TaskID;

u08 TimerTaskID;

//u08 flg_BRN_GRATE;
u08 v_CntUnld;
u32 v_Time;

const u08 __flash *pszState;
const u08 __flash *pszError;

/*                                *01234*/
//const char __flash szState_F[]  = "Пламя";
//const char __flash szState_S[]  = "Подча";
const char __flash szState_L[]  = {S_L, S_D, S_BLNK}; /*"Загр бункера";*/
const char __flash szState_I[]  = {S_i, S_G, S_n}; /*"Рзжиг*";*/
const char __flash szState_U[]  = {S_U, S_L, S_D}; /*"ВыгрзB";*/
const char __flash szState_T[]  = {S_t, S_E, S_n}; /*" ТЭН T";*/
const char __flash szState_P[]  = {S_P, S_A, S_U}; /*"ПаузаП";*/
const char __flash szState_B[]  = {S_B, S_r, S_n};
const char __flash szState_G[]  = {S_G, S_r, S_t}; /*"РешетP";*/
const char __flash szState_D[]  = {S_A, S_B, S_r}; /*"ДожигД";*/
const char __flash szState_H[]  = {S_H, S_0, S_t}; /*"ОхлажО";*/
const char __flash szState_x[]  = {S_S, S_t, S_P}; /*" Стоп ";*/
//const char __flash szState_AR[] = {,,}; /*" ПускA";*/
//const char __flash szState_G[]  = {,,}; /*"РешетP";*/
//const char __flash szState_W[]  = {,,}; /*"ХолодX";*/
//const char __flash szState_S[]  = {,,}; /*"Шнек!Ш";*/

//const char __flash szState_V[]  = "Ворош";

//const u08 __flash szFaultStuck[]    =  " Датчик топлива?";
//const u08 __flash szFaultSupply[]   =  "  Бункер пуст?  ";

/*                                     *0123456789012345*/
const u08 __flash szFaultCRCs[]     =  {S_F, S_L, S_S};
const u08 __flash szFaultCRCc[]     =  {S_F, S_L, S_C};
const u08 __flash szFaultTS2[]      =  {S_F, S_t, S_2};  /* "Перегрев корпуса" */
const u08 __flash szFaultCRC[]      =  {S_F, S_E, S_E};  /*"Error EEPROM CRC"  */
const u08 __flash szFaultCleaning[] =  {S_F, S_S, S_H};  /*"Заклинило шнек:("  */
const u08 __flash szFaultFuel[]     =  {S_F, S_F, S_L};  /*"  Срыв пламени? "; */
const u08 __flash szFaultTen[]      =  {S_F, S_t, S_n};  /*"Что-то с ТЭН-ом?"; */

//const u08 __flash szFaultTS3[]      =  "Перегрев корпуса";
//const u08 __flash szFaultTen[]      =  "Что-то с ТЭН-ом?";

//const u08 __flash szErrCRCTimer[]   =  "Error CRC Timer!";
const u08 szFaultBuf[16];


Param_t v_Param;   /* Данные от датчиков */

const __flash u08 cReleLedTest[] = {
  RK1,
  RK2,
  RK3,
  RK4,
  RK5,
  RK6,
  RK7,
  RK8,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

#ifdef TEST_MENU
void f_Test(void)
{
  static u08 cnt = mItems(cReleLedTest);

  if (cnt > mItems(cReleLedTest)) {
    cnt = mItems(cReleLedTest);
  }

  switch (vState) {  /* Включаем реле в зависимости от состояния */
    case TEST: {
        if (cnt) {
          v_ORele = cReleLedTest[cnt - 1];
          fOut_vPort(2, v_ORele, IDPORT);
          v_LED3Buf[1] = fB27S(cnt);
          v_LED3Buf[2] = fB27S(cnt);
          szParamVal_Buf[1] = fB27S(cnt);
          szParamVal_Buf[2] = fB27S(cnt);
          fPrint2LED(cnt);
          cnt--;
          fBuzOnTime(500 _ms);
          mSetTimerTask(f_Test, 1 _s);
        } else {
          vState = STOP;
        }

        break;
      }

    case STOP: {
        cnt = mItems(cReleLedTest);
        vState = TEST;
        mSendTask(f_Test);
        break;
      }

    default:
      break;
  }
}

#endif // 0

ISR(INT0_vect)
{
  //  mSetTimerTask(fGetFuel, 500 _ms);
  // fBuzOnTime(100 _ms);
}




void fFaultIgnition(void)
{
  vState = BRN_UNLOAD;                          /* Устанавливаем режим горения с выгрузкой */
}


void fBuzSound(u08 msk)
{
  if (vFlash & msk) {
    fBuzOn();
  } else {
    fBuzOff();
  }
}


void fLed_Fault_On(void)
{
  //mLED_On(LED_FAULT);
}

void fLed_Fault_Off(void)
{
  //mLED_Off(LED_FAULT);
}


void fSupply_On(void)
{
  //  //  v_ORele_Manual = (K_SUPPLY);
  //  v_OLed_Manual = LED_GRATE;
  //  mClrTimer(fMenuInit);
}

void fSupply_Off(void)
{
  //  v_ORele_Manual = (0);
  //  v_OLed_Manual = (0);
}


/* Выгрузка топлива в ручном режиме */
void fScrew_R_On(void)
{
  //  v_ORele_Manual = (K_R_SCREW);
  //  v_OLed_Manual = (LED_UNLOAD);
  //  mClrTimer(fMenuInit);
}

void fScrew_L_On(void)
{
  //  v_ORele_Manual = (K_L_SCREW);
  //  v_OLed_Manual = (LED_UNLOAD);
  //  mClrTimer(fMenuInit);
}

void fGrate_On(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  static u08 tmpGrateCnt100s;
  mSetTimerTask(fGrate_On, 100 _s);
  tmpGrateCnt100s++;

  if (tmpGrateCnt100s >= 18) {
    tmpGrateCnt100s = 0;
    pFlg->Grate = 1;
  }
}



void fClean_On(void)
{
  //  v_ORele_Manual = (K_CLEAN);
  //  v_OLed_Manual = (LED_GRATE);
  //  mClrTimer(fMenuInit);
}



void fTEN_On(void)
{
  //  v_ORele_Manual = (K_TEN);
  //  v_OLed_Manual = (LED_TEN);
  //  mClrTimer(fMenuInit);
}

void fFan_On(void)
{
  //  v_ORele_Manual = (K_FAN);
  //  v_OLed_Manual = (LED_GRATE);
  //  mClrTimer(fMenuInit);
}


void fPump_On(void)
{
  //  v_ORele_Manual = (K_PUMP);
  //  v_OLed_Manual = (LED_GRATE);
  //  mClrTimer(fMenuInit);
}

void fWait_Time_2Next(void)
{
  vState = vStateNext;
}

void fAlarm_On(void)
{
  //  v_ORele_Manual = (K_ALARM);
  //  v_OLed_Manual = (LED_FAULT);
  //  mClrTimer(fMenuInit);
}
void fManual_Off(void)
{
  v_ORele_Manual = (0);
  v_OLed_Manual = (0);
}


void fBunker_Load_TimeOut(void)
{
  mRK_Off(K_BUNKER);
  vState = FAULT_LOAD;
  pszError = (u08*)&szFaultFuel[0];
  vStateNext = FAULT;
  mSetTimerTask(fWait_Time_2Next, vSets_com.BlowTime * FreqOS);
}


void fTEN_AirOn(void)
{
}

void fTEN_OnTimeLeft(void)
{
}

void fFuelOn(void)
{
  v_Param.Fuel = 1;
}

void f_Go2IGN_UNLOAD(u08 N_Uld, eSTATE_t Wait2Next, eSTATE_t NextTime,u16 Time)
{
  v_N_Unload = N_Uld;                                     /* Кол-во оборотов шнека выгрузки */
  vStateNext = NextTime;
  vStateNextTime = Time;
  vState = IGN_UNLOAD;
  vStateForWait = Wait2Next;
}

void fRunStop(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL);  // Инициализация указателя на структуру флагов /

  switch (vState) {
    case AFTERBURN: {
        mClrTimer(fRunStop);  /* Остановим таймер  */
        vState = STOP;
        break;
      }

    case AUTORUN:
    case STOP: {
        fMenuInit();                      /* Инициализация меню, чтение сохраненных настроек */

        if (pFlg->CfgOK) {
          //          flg_BRN_GRATE = vSets.N_Grate;
          f_FSM_CleanScrew(CLN_INIT);
          f_FSM_Grate(GRT_INIT);
          f_FSM_Unload(UNLD_INIT);
          f_Go2IGN_UNLOAD(vSets.N_Ignition,IGN_TEN, IGN_TEN_ULD_5MIN, 5 * 60 _s);
          //          v_N_Unload = vSets.N_Ignition;/* 8 Кол-во оборотов шнека выгрузки перед розжигом [n] */
          //          vState = IGN_UNLOAD;
          //          vStateNext = IGN_TEN_ULD_5MIN;
          //          vStateNextTime = 5 * 60 _s;
        } else {
          //
        }

        break;
      }

    default: {
        //fBuzOff();
        mPinIn(BUZ);
        vState = AFTERBURN;
        mClrTimer(fReUnload_On);  /* Остановим таймер  */
        mSetTimerTask(fRunStop, vSets_com.BlowTime * FreqOS);
        TimerTaskID = GetTaskID(fRunStop);
        break;
      }
  }
}

void fReUnload_On(void)
{
}
void fUnload_Off(void)
{
}

/** Основная функция управления горелкой */
void fControl(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  v_Param.TS1 = fGetTempLM335(v_ADC[0]);
  v_Param.TS2 = fGetTempLM335(v_ADC[1]);

  //{ Расчет коэффициента мощности:                                              vRegParam.Kpow
  if (vRegParam.ADC_Temp >= v_ADC[0]) {
    vRegParam.Kpow = (vRegParam.ADC_Temp - v_ADC[0]) / 16;

    if (vRegParam.Kpow > 100) {
      vRegParam.Kpow = 100;
    }
  } else {
    vRegParam.Kpow = 0;
  }

  vRegParam.Kpow = vRegParam.Kpow * vSets.Power / 100;
  //} Расчет коэффициента мощности
  //{ Расчет кол-ва оборотов шнека для выгрузки топлива в топку:             vRegParam.N_Unload
  vRegParam.N_Unload = (vSets.N_Unload - 1) * vRegParam.Kpow / 100;
  vRegParam.N_Unload = 1 + vRegParam.N_Unload ;
  //} Расчет кол-ва оборотов шнека для выгрузки топлива в топку
  //{ Расчет времени паузы между подачами топлива:                            vRegParam.T_Pause
  vRegParam.T_Pause = (60 - vSets.T_Pause) * vRegParam.Kpow / 100;
  vRegParam.T_Pause = 60 - vRegParam.T_Pause ;
  //} Расчет времени паузы между подачами топлива

  switch (vState) {  /* Включаем реле в зависимости от состояния */
    case AUTORUN: {
        fOffAllRele();                                                   /* Отключаем все реле */
        break;
      }

    case STOP: {
        pszState = (u08*)&szState_x;
        fOffAllRele();                                                   /* Отключаем все реле */
        //mClrTimer(fFaultIgnition);
        mClrTimer(fRunStop);
        mClrTimer(fWait_Time_2Next);             /* */
        break;
      }

    //        case BNKR_LOAD: {
    //            pszState = (u08*)&szState_L;
    //            fOffAllRele();                                                   /* Отключаем все реле */
    //            mClrTimer(fFaultIgnition);
    //            mClrTimer(fRunStop);
    //
    //            if (pFlg->FuelOK == 1) {
    //              vState = IGN_UNLOAD;
    //              pFlg->FuelOK = 0;
    //              mRK_Off(K_BUNKER);
    //            } else {
    //              mRK_On(K_BUNKER);
    //            }
    //
    //            break;
    //          }

    case IGN_UNLOAD: {
        pszState = (u08*)&szState_U;
//        fOffAllRele();                                                 /* Отключаем все реле */
//        mRK_On(K_FAN);

        //        if (v_KBD.act) {
        //          vState = vStateNext;
        //        }

        //v_N_Unload  - !!! НЕОБХОДИМО Установить перед переходом в состояние IGN_UNLOAD !!!
        //v_N_Unload = vSets.N_Ignition;/* 8 Кол-во оборотов шнека выгрузки перед розжигом [n] */
        if (f_FSM_Unload(0)) {
          if (vState == IGN_UNLOAD) {
            vState = vStateForWait;/* Состояние Розжиг. Ждем события перехода следующее состояние */
            krSetTimer(GetTaskID(fWait_Time_2Next), vStateNextTime);           /* */
          }
        }

        break;
      }

    case IGN_TEN_ULD_5MIN: {
        f_Go2IGN_UNLOAD(1,IGN_TEN, IGN_TEN_ULD_10MIN, 5 * 60 _s);
        break;
      }

    case IGN_TEN_ULD_10MIN: {
        f_Go2IGN_UNLOAD(1,IGNITION, IGN_ULD_12MIN, 2 * 60 _s);

        break;
      }

    case IGN_ULD_12MIN: {
        f_Go2IGN_UNLOAD(1,IGNITION, BRN_UNLOAD, vSets.T_Ignition * FreqOS);


        break;
      }

    case IGN_TEN: {
        pszState = (u08*)&szState_T;
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_TEN);
        mRK_On(K_FAN);
        TimerTaskID = GetTaskID(fWait_Time_2Next);
        break;
      }

    case IGNITION: {
        pszState = (u08*)&szState_I;
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        TimerTaskID = GetTaskID(fWait_Time_2Next);
        break;
      }

    //    case BRN_BNKR_FILL: {
    //        pszState = (u08*)&szState_L;
    //        fOffAllRele();                                                   /* Отключаем все реле */
    //        mRK_On(K_FAN);
    //
    //        if (pFlg->FuelOK == 1) {
    //          //vStateNext = BRN_UNLOAD;
    //          mSetTimerTask(fWait_Time_2Next, 4 _s);
    //          vState = WAIT;
    //          //          pFlg->FuelOK = 0;
    //          //          mRK_Off(K_BUNKER);
    //        } else {
    //          mRK_On(K_BUNKER);
    //        }
    //
    //        break;
    //      }

    case BRN_UNLOAD: {
        pszState = (u08*)&szState_U;
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_Off(K_BUNKER);
        mRK_On(K_FAN);

        if (pFlg->Grate == 1) {
          /* Нужно подвинуть топливо в горелке */
          pFlg->Grate = 0;
          vState = BRN_GRATE;
        }

        v_N_Unload = vRegParam.N_Unload;

        if (f_FSM_Unload(0)) {
          if (vState == BRN_UNLOAD) {
            vState = BURNING;
            //{
            mSetTimerTask(fReUnload_On, (vSets.T_Pause) * FreqOS);
            TimerTaskID = GetTaskID(fReUnload_On);
            //}
          } else {
            mClrTimer(fReUnload_On);  /* Остановим таймер  */
          }
        }

        break;
      }

    case BURNING: {
        pszState = (u08*)&szState_B;
        fOffAllRele();                                                   /* Отключаем все реле */
        mLED_On(LED_BURNING);
        mRK_On(K_FAN);

        if (!krGetTimer(GetTaskID(fReUnload_On))) {
          f_FSM_Unload(UNLD_INIT);
          vState = BRN_UNLOAD;  /* Устанавливаем режим горения с загрузкой бункера */
          vStateNext = BRN_UNLOAD;
        }

        break;
      }

    case BRN_GRATE: {
        pszState = (u08*)&szState_G;
        fOffAllRele();                                                   /* Отключаем все реле */
        mLED_On(LED_BURNING);
        mLED_On(LED_GRATE);
        mLED_On(LED_UNLOAD);
        mRK_On(K_FAN);

        if (f_FSM_Grate(0)) {
          vState = BURNING;
        }

        break;
      }

    case AFTERBURN: {
        pszState = (u08*)&szState_D;
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        break;
      }

    case FAULT: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mClrTimer(fWait_Time_2Next);             /* */
        fBuzSound(1);
        break;
      }

    case FAULT_TS2: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        vStateNext = FAULT_TS2_2;
        mSetTimerTask(fWait_Time_2Next, T_ULD_FAULT_TS2 _s);             /* */
        vState = FAULT_TS2_1;
        fBuzSound(1);
        break;
      }

    case FAULT_TS2_1: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        mRK_On(K_R_SCREW);
        fBuzSound(1);
        break;
      }

    case FAULT_TS2_2: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        vStateNext = FAULT_TS2;
        mSetTimerTask(fWait_Time_2Next, T_WAIT_FAULT_TS2 _s);             /* */
        vState = FAULT_TS2_3;
        v_cnt_FultTS2_Unload--;

        if (v_cnt_FultTS2_Unload == 0) {
          vState = FAULT;
        }

        fBuzSound(1);
        break;
      }

    case FAULT_TS2_3: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);

        if (v_Param.TS2 < (273 + TEMP_HOT - 1)) { /* Контроль аварийной ситуации перегрев корпуса */
          vState = FAULT;
          pszError = (u08*)&szFaultTS2;
        }

        fBuzSound(1);
        break;
      }

    case FAULT_SCREW: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        fBuzSound(0b0011);
        break;
      }

    case FAULT_LOAD: {
        fOffAllRele();                                                   /* Отключаем все реле */
        mRK_On(K_FAN);
        fBuzSound(0b0011);
        break;
      }

    //    case COOLING: {
    //        //        pszState = (u08*)&szState_H;
    //        //        fOffAllRele();                                                   /* Отключаем все реле */
    //        //        mRK_On(K_FAN);
    //        fBuzSound(0b0101);
    //
    //        if (!f_CheckTempr()) {                                       /* Температура        */
    //          /* в норме            */
    //          vState = vStateNext;
    //          fBuzOff();
    //        }
    //
    //        break;
    //      }

    default:
      break;
  }

  switch (vState) {
    case FAULT_TS2:
    case FAULT_TS2_1:
    case FAULT_TS2_2:
    case FAULT_TS2_3: {
        break;
      }

    default: {
        if (v_Param.TS2 > (273 + TEMP_HOT)) { /* Контроль аварийной ситуации перегрев корпуса */
          v_cnt_FultTS2_Unload = N_ULD_FAULT_TS2;
          vState = FAULT_TS2;
          pszError = (u08*)&szFaultTS2;
        }

        break;
      }
  }

  f_FSM_Alarm(0);
  fBunker();
  f_Output();                                          /* Вывод управляющих сигналов на реле */
} /* fControl() */

u16 fGetTempLM335(u16 adc)
{
  u16 Temp;
  s32 tmp_adc;
  tmp_adc = adc;
  Temp = (tmp_adc * vSets_com.Uref / 10 / 65536) + vSets_com.T_Offset;
  return Temp;
}

u16 fGetTempPt100(u16 adc)
{
  u16 Temp;
  s32 tmp_adc;
  tmp_adc = adc;
  Temp = (tmp_adc * vSets_com.Uref / 10 / 65536) + vSets_com.T_Offset;
  return Temp;
}

u16 fGetADC_from_TempLM335(u16 Temp)
{
  u16 ADC_Temp;
  s32 tmp_Temp;
  //Temp = (ADC_Temp * vSets_com.Uref / 10 / 65536) + vSets_com.T_Offset;
  //ADC_Temp  = (Temp - vSets_com.T_Offset) * 65536 * 10 / vSets_com.Uref ;
  tmp_Temp = (Temp - vSets_com.T_Offset);
  ADC_Temp  = tmp_Temp * 65536 * 10 / vSets_com.Uref;
  return ADC_Temp;
}

void f_Output(void)
{
  v_OLed |= v_OLed_Manual;
  v_ORele |= v_ORele_Manual;
  //  v_LED3Buf[0] = fB27S(vState);
  //  v_LED3Buf[0] = v_OLed;
  fOut_vPort(2, v_ORele, IDPORT);
}
void f_Input(void)
{
}

void fCntScrew(void)
{
  v_CntUnld++;
}

u08 f_FSM_Unload(eFSM_Unload_t vFSM)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  static volatile  u32 vUnloadTimeOut;
  //  static volatile  u32 vUnloadTime;
  static u08 N_Unload_Old;
  static volatile  eFSM_Unload_t FSM_Unload;

  if (vFSM) {
    FSM_Unload = vFSM;
    return 0;
  }

  switch (FSM_Unload) {
    case UNLD_FILL_BNKR: {
        pszState = (u08*)&szState_L;
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);
        mRK_On(K_BUNKER);                   /* Включить двигатель подачи топлива из бункера. */

        if (pFlg->FuelOK == 1) {                                        /* Топливо появилось */
          vUnloadTimeOut = vOS_Tick + 4 _s;                   /* добавим время для "добавки" */
          FSM_Unload  = UNLD_WAIT;
        }  else {                               /* Топлива нет */
          if (vOS_Tick >= vUnloadTimeOut) {      /* Предельный интервал ожидания превышен */
            vState = FAULT_LOAD;  /* Топливо есть (с добавкой) продолжаем выгрузку в топку */
            return 1;
          }
        }

        break;
      }

    case UNLD_WAIT: {
        pszState = (u08*)&szState_L;
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);
        mRK_On(K_BUNKER);                   /* Включить двигатель подачи топлива из бункера. */

        if (vOS_Tick >= vUnloadTimeOut) {
          FSM_Unload  = UNLD_ACT;   /* Топливо есть (с добавкой) продолжаем выгрузку в топку */
        }

        break;
      }

    case UNLD_INIT: {
        //        vCntUnload++;                      /* Инкремент счетчика количества выгрузок топлива.*/
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);
        v_CntUnld = 0;
        vUnloadTimeOut = vOS_Tick + 4 _s;
        N_Unload_Old = v_CntUnld;
        FSM_Unload  = UNLD_ACT;
        mRK_Off(K_L_SCREW);
        mRK_On(K_R_SCREW);
        break;
      }

    case UNLD_ACT: {
        if (pFlg->FuelOK == 1) {
          //FSM_Unload  = UNLD_ACT;
        } else {
          vUnloadTimeOut = vOS_Tick + 10 _s;       /* Предельное время заполнения из бункера */
          FSM_Unload  = UNLD_FILL_BNKR;
          break;
        }

        mRK_Off(K_L_SCREW);
        mRK_On(K_R_SCREW);
        mRK_Off(K_BUNKER);                 /* Отключить двигатель подачи топлива из бункера. */

        if (vOS_Tick >= vUnloadTimeOut) {
          FSM_Unload  = UNLD_CLR;
        }

        if (N_Unload_Old != v_CntUnld) {
          vUnloadTimeOut = vOS_Tick + 4 _s;
        }

        N_Unload_Old = v_CntUnld;

        if (v_CntUnld >= v_N_Unload) {
          FSM_Unload  = UNLD_INIT;                             /* Выход после подачи топлива */
          return 1; /* Выход из модуля */
        }

        break;
      }

    case UNLD_CLR: {
        if (f_FSM_CleanScrew(0)) {
          FSM_Unload  = UNLD_ACT;
          vUnloadTimeOut = vOS_Tick + 4 _s;
        }

        break;
      }

    default: {
      }
      break;
  }

  return 0;
}
u08 f_FSM_CleanScrew(eFSM_CleanScrew_t vFSM)
{
  static volatile u08 N_Unload_Old = 0;
  static volatile u08 cntClean = 0;
  static volatile  eFSM_CleanScrew_t FSM_CleanScrew = CLR_INIT;
  static volatile  u32 vCCW_Time;
  static volatile  u32 vCW_TimeOut;
  static volatile  u32 v_Pause_Timer;

  if (vFSM) {
    FSM_CleanScrew = vFSM;
    return 0;
  }

  switch (FSM_CleanScrew) {
    case CLR_INIT: {
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);
        cntClean = 0;
        N_Unload_Old = v_CntUnld;
        vCCW_Time = vOS_Tick + 2 _s;
        FSM_CleanScrew  = CLR_CCW;
        mRK_Off(K_R_SCREW);
        mRK_On(K_L_SCREW);
        break;
      }

    case CLR_CCW: {
        mRK_Off(K_R_SCREW);
        mRK_On(K_L_SCREW);

        if (vOS_Tick >= vCCW_Time) {
          cntClean++;
          N_Unload_Old = v_CntUnld;
          v_Pause_Timer = vOS_Tick + 1 _s;
          FSM_CleanScrew  = CLR_CCW_PAUSE;
          mRK_Off(K_R_SCREW);
          mRK_Off(K_L_SCREW);
        }

        if (cntClean > 3) {
          FSM_CleanScrew = CLR_FAULT;
        }

        break;
      }

    case CLR_CCW_PAUSE: {
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);

        if (vOS_Tick >= v_Pause_Timer) {
          vCW_TimeOut = vOS_Tick + 4 _s;
          FSM_CleanScrew  = CLR_CW;
          mRK_Off(K_L_SCREW);
          mRK_On(K_R_SCREW);
        }

        break;
      }

    case CLR_CW: {
        mRK_Off(K_L_SCREW);
        mRK_On(K_R_SCREW);

        if (vOS_Tick >= vCW_TimeOut) {
          v_Pause_Timer = vOS_Tick + 1 _s;
          FSM_CleanScrew  = CLR_CW_PAUSE;
          mRK_Off(K_R_SCREW);
          mRK_Off(K_L_SCREW);
        }

        if (N_Unload_Old != v_CntUnld) {
          FSM_CleanScrew  = CLR_INIT;
          return 1;
        }

        N_Unload_Old = v_CntUnld;
        break;
      }

    case CLR_CW_PAUSE: {
        mRK_Off(K_R_SCREW);
        mRK_Off(K_L_SCREW);

        if (vOS_Tick >= v_Pause_Timer) {
          vCCW_Time = vOS_Tick + 2 _s;
          FSM_CleanScrew  = CLR_CCW;
          mRK_Off(K_R_SCREW);
          mRK_On(K_L_SCREW);
        }

        break;
      }

    case CLR_FAULT: {
        vState = FAULT_SCREW;
        pszError = (u08*)&szFaultCleaning;
        mSetTimerTask(fRunStop, 120 _s);
        TimerTaskID = GetTaskID(fRunStop);
        FSM_CleanScrew  = CLR_INIT;
        break;
      }

    default: {
      }
      break;
  }

  return 0;
}

u08 f_FSM_Alarm(u08 vFSM)
{
  static volatile eFSM_Alarm_t FSM_Alarm = ALARM_INIT;

  if (vFSM) {
    FSM_Alarm = vFSM;
    return 0;
  }

  switch (FSM_Alarm) {
    case ALARM_INIT: {
        if (f_CheckTempr()) {               /* Контроль границ температурного режима объекта */
          /* Температура за пределами установленных границ */
          FSM_Alarm = ALARM_ON;
        }

        break;
      }

    case ALARM_ON: {
        fBuzSound(0b0101);

        if (!f_CheckTempr()) {                                       /* Температура        */
          /* в норме            */
          FSM_Alarm = ALARM_INIT;
          fBuzOff();
        }

        break;
      }

    default: {
        break;
      }
  }

  return 1;
}

u08 f_FSM_Grate(eFSM_Grate_t vFSM)
{
  static volatile  eFSM_Grate_t FSM_Grate = GRT_INIT;

  if (vFSM) {
    FSM_Grate = vFSM;
    return 0;
  }

  switch (FSM_Grate) {
    case GRT_INIT: {
        mRK_Off(K_GRATE);
        FSM_Grate = GRT_ON;
        v_Time = vOS_Tick + 5 _s;
        break;
      }

    case GRT_ON: {
        mRK_On(K_GRATE);

        if (vOS_Tick >= v_Time) {
          FSM_Grate  = GRT_INIT;
          //          vCntGrate32++;
          return 1;
        }

        break;
      }

    default: {
        break;
      }
  }

  return 0;
}
u08 f_CheckTempr(void)   /* Контроль границ температурного режима объекта */
{
  if (v_Param.TS1 <= (273 + vSets.Temp1)) {   /* Температура котла и   */
    /* в норме */
    return 0;
  }

  return 1;
}
//#define LEVEL_EMPTY ((MAX_U16*1UL)/3)
//#define LEVEL_FULL ((MAX_U16*2UL)/3)
void fBunker(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  v_Param.AI_Pellet = v_ADC[2];

  if (1) {                        /* Работаем с датчиком подачи топлива */
    switch (vState) {
      case AFTERBURN:
      case FAULT_SCREW:
      case FAULT_LOAD:
      case FAULT:
      case STOP: {
          mRK_Off(K_BUNKER);
          mClrTimer(fBunker_Load_TimeOut);

          if (v_Param.AI_Pellet < LEVEL_EMPTY) { /* Контроль  */
            pFlg->FuelOK = 0;
          } else if (v_Param.AI_Pellet > LEVEL_FULL) { /* Контроль  */
            pFlg->FuelOK = 1;
          }

          break;
        }

      case TEST: {
          break;
        }

      default: {
          if (v_Param.AI_Pellet < LEVEL_EMPTY) { /* Контроль  */
            pFlg->FuelOK = 0;
            mSetTimerTask(fBunker_Load_TimeOut, T_BUNKER);
          } else if (v_Param.AI_Pellet > LEVEL_FULL) { /* Контроль  */
            pFlg->FuelOK = 1;
            mClrTimer(fBunker_Load_TimeOut);
          }

          break;
        }
    }  /* switch (vState) */
  } else {
    return;
  }
}
void fOffAllRele(void)
{
  if (1) {                        /* Работаем с датчиком подачи топлива */
    v_ORele &= (K_BUNKER);
  } else {
    v_ORele  = 0;
  }
}

void fSQInit(void)
{
#ifdef SQ1
  mPinIn(SQ1);
#endif // SQ1
  SQ1_On_TaskID = GetTaskID(fCntScrew);
  SQ1_Off_TaskID = GetTaskID(fIdle);
  fSQGet();
}
void fSQGet(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  u08 tmpSQ;
  //mSendTask(fSQGet);
  mSetTimerTask(fSQGet, 10 _ms);
  tmpSQ = vSQ_State;
  tmpSQ <<= 1;
  tmpSQ &= ~0x11;
#ifdef SQ1

  if (mPinIsAct(SQ1)) {
    tmpSQ |= 0x01;
    pFlg->Screw = 1;
  } else {
    pFlg->Screw = 0;
  }

#endif // SQ1
  vSQ_State = tmpSQ;

  switch (tmpSQ & 0b11) {
    case 0b01: {                         /* Замыкание конечного контакта SQ1 выталкивателя */
        /* */
        krSendTask(SQ1_On_TaskID);
        break;
      }

    case 0b10: {                        /* Размыкание конечного контакта SQ1 выталкивателя */
        /* */
        krSendTask(SQ1_Off_TaskID);
        break;
      }

    default: {
        /* */
        break;
      }
  }
}


