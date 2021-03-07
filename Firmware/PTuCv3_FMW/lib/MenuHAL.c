#include "MenuHAL.h"
const u08 __flash IncDecVal[] = {1, 10, 100};

Menu_t v_Menu;
u08 flgTimerEdit;
u08 v_LED3Buf[8];


//const __flash char szMenu1[] = "Ctrl MT_NUM";
//u16 Ctrl_MT_NUM_1 = 1234;
//
//const __flash Ctrl_t Ctrl_01 = {
//  .pszItemMenu  = &szMenu1,  //Указатель на ASCIIZ строку, текст выводимого пункта меню
//  .x_szItemMenu = 0,
//  .y_szItemMenu = 1,
//  .MenuType     = MT_UNUM,// - тип меню MT_NUM; MT_LST; MT_SUB
//  .pValParam    = &Ctrl_MT_NUM_1,//Указатель на параметр пункта меню (ячейка RAM 16bit)
//  .x_ValParam   = 11,
//  .y_ValParam   = 1,
//  //.uExPrm1.s_Min; // Для типа MT_NUM
//  .ExPrm1.u_Min = 4, // Для типа MT_NUM
//  //.ExPrm1.pszListItem;//Указатель на указатели строк для списка MT_LST
//  //.ExPrm2.s_Max =, // Для типа MT_NUM Максимальное значение параметра
//  .ExPrm2.u_Max = 99, // Для типа MT_NUM Максимальное значение параметра
//  //.ExPrm2.hSubMenu = , // MT_SUB -> SubMenuID. Идентификатор подменю.
//  //.ExPrm2.nLst,//    ; MT_LST -> Число строк списка для выбора.
//  .Unit = UC_DEG//Указатель на функцию которая обрабатывает данный пункт меню
//};

//  MT_STR
#define mMemu_STR(Name,ItemText,/*x_IT,y_IT,*/Var,VarMin,VarMax)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_STR,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.szStr = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.u_Min  = VarMin,   /*Минимальное значение параметра */\
       .ExPrm2.u_Max  = VarMax,   /*Максимальное значение параметра */\
       .TaskID        = GetTaskID(fEditName),   /* ID задачи обработки меню */\
       /*.Unit          = unit*/      /*Единица измерения параметра */\
      };

//  MT_UNUM8
#define mMemu_UNUM8(Name,ItemText,/*x_IT,y_IT,*/Var,VarMin,VarMax)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_UNUM,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u08Val = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.u_Min  = VarMin,   /*Минимальное значение параметра */\
       .ExPrm2.u_Max  = VarMax,   /*Максимальное значение параметра */\
       .TaskID        = GetTaskID(fMenuDefEditProc),   /* ID задачи обработки меню */\
       /*.Unit          = unit*/      /*Единица измерения параметра */\
      };

//  MT_UNUM
#define mMemu_UNUM(Name,ItemText,/*x_IT,y_IT,*/Var,VarMin,VarMax)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_UNUM,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u16Val = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.u_Min  = VarMin,   /*Минимальное значение параметра */\
       .ExPrm2.u_Max  = VarMax,   /*Максимальное значение параметра */\
       .TaskID        = GetTaskID(fMenuDefEditProc),   /* ID задачи обработки меню */\
       /*.Unit          = unit*/      /*Единица измерения параметра */\
      };

//  MT_SNUM
#define mMemu_SNUM(Name,ItemText,/*x_IT,y_IT,*/Var,VarMin,VarMax)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_SNUM,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.s16Val = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.s_Min  = VarMin,   /*Минимальное значение параметра */\
       .ExPrm2.s_Max  = VarMax,   /*Максимальное значение параметра */\
       .TaskID        = GetTaskID(fMenuDefEditProc),   /* ID задачи обработки меню */\
       /*.Unit          = unit*/      /*Единица измерения параметра */\
      };
//  MT_SUB
#define mMemu_SUB(Name,ItemText,/*x_IT,y_IT,*/SubMenu)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_SUB,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u16Val = 0,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       .x_ValParam    = 0,      /*Координата x вывода значения параметра пункта меню */\
       .y_ValParam    = 0,      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.s_Min  = 0,   /*Минимальное значение параметра */\
       .ExPrm2.hSubMenu  = (u16)(SubMenu),   /*Указатель на меню */\
       .TaskID        = GetTaskID(fMenuSubDefProc),   /* ID задачи обработки меню */\
      };
//  MT_BUTTON
#define mMemu_BTN(Name,ItemText,/*x_IT,y_IT,*/BDn_TaskID,BUp_TaskID)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_BUTTON,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON */\
       .pParam.u16Val = 0,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /* .x_ValParam    = 0,*/      /*Координата x вывода значения параметра пункта меню */\
       /* .y_ValParam    = 0,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.BtnDnTaskID  = BDn_TaskID,   /*ID задачи обработки нажатия кнопки*/\
       .ExPrm2.BtnUpTaskID  = BUp_TaskID,   /*ID задачи обработки нажатия кнопки*/\
       .TaskID        = GetTaskID(fMenuButtonProc),   /* ID задачи обработки меню */\
      };
//  MT_LSTF
#define mMemu_LSTF(Name,ItemText,/*x_IT,y_IT,*/Var,ListItem)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_LST,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u16Val     = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.ppszListItem = ListItem, /*Указатель на указатели строк для списка MT_LST */\
       .ExPrm2.nLst   = mItems(ListItem),    /*Число строк списка для выбора. */\
       .TaskID        = GetTaskID(fMenuDefEditProc),   /* ID задачи обработки меню */\
      };
//  MT_LST_RAM
#define mMemu_LST_RAM(Name,ItemText,/*x_IT,y_IT,*/Var,ListItem,n_Lst)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_LST_RAM,  /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u16Val     = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 16bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.ppszListItem_RAM = ListItem, /*Указатель на указатели строк для списка MT_LST */\
       .ExPrm2.nLst   = n_Lst,    /*Число строк списка для выбора. */\
       .TaskID        = GetTaskID(fMenuDefEditProc),   /* ID задачи обработки меню */\
      };


//  MT_TIMER
#define mMemu_TIMER(Name,ItemText,/*x_IT,y_IT,*/Var,vnTimer,VarMax)\
  const u08 __flash Name##sz[]=ItemText;\
  const Ctrl_t __flash Name \
    = {.pszItemMenu   = Name##sz, /*Указатель на ASCIIZ строку, текст выводимого пункта меню*/\
       /* .x_szItemMenu  = x_IT,*/     /*Координата x вывода текста пункта меню */\
       /* .y_szItemMenu  = y_IT,*/     /*Координата y вывода текста пункта меню */\
       .MenuType      = MT_UNUM, /*Тип меню MT_xNUM; MT_LST; MT_SUB; MT_BUTTON*/\
       .pParam.u08Val = &Var,     /*Указатель на параметр пункта меню (ячейка RAM 8bit) */\
       /*.x_ValParam    = x_V,*/      /*Координата x вывода значения параметра пункта меню */\
       /*.y_ValParam    = y_V,*/      /*Координата у вывода значения параметра пункта меню */\
       .ExPrm1.nTimer = vnTimer,  /*Номер таймера */\
       .ExPrm2.u_Max  = 13,       /*Количество параметров настройки интервального таймера */\
       .TaskID        = GetTaskID(fMenuProcTimer),   /* ID задачи обработки меню */\
       /*.Unit          = unit*/      /*Единица измерения параметра */\
      };

////u16 T_Pause;  /* 1 Номинальная мощность горелки */
#define MIName {S_BLNK,S_P,S_n}
mMemu_UNUM(CUNUM_Power, MIName, vSets.Power, 10, 99);
#undef MIName

//u16 T_Pause;  /* 1 Пауза между подачами топлива [sec] */
#define MIName {S_P,S_A,S_U}
mMemu_UNUM(CUNUM_T_Pause, MIName, vSets.T_Pause, 15, 60);
#undef MIName
//
//u16 N_Unload;   /* 2 Время подачи топлива шнеком горелки в топку [sec] */
#define MIName {S_U,S_L,S_D}
mMemu_UNUM(CUNUM_N_Unload, MIName, vSets.N_Unload, 1, 30);
#undef MIName

//u16 T_TEN;   /* 4 Время включения ТЭНа для розжига пеллеты. [sec] */
#define MIName {S_t,S_E,S_n}
mMemu_UNUM(CUNUM_T_TEN, MIName, vSets.T_TEN, 60, 650);
#undef MIName


//u16 Temp1;   /* 6 Температура котла установка [°C] */

#define MIName {S_BLNK,S_BLNK,S_t}
mMemu_UNUM(CUNUM_Temp1, MIName, vSets.Temp1, 4, 120);
#undef MIName

////u16 dTemp1;  /* 7 дельта Температуры котла, ошибка [°C]*/
//
//#define MIName {S_BLNK,S_D,S_t}
//mMemu_UNUM(CUNUM_dTemp1, MIName, vSets.dTemp1, 1, 20);
//#undef MIName



///** Ворошим решетку через данное кол-во выгрузок топлива. [ ] */
//#define MIName {S_n,S_BLNK,S_G}
//mMemu_UNUM(CUNUM_N_Grate, MIName, vSets.N_Grate, 1, 255);
//#undef MIName


///** Ворошим решетку заданное время. [sec] */
//#define MIName {S_t,S_BLNK,S_G}
//mMemu_UNUM(CUNUM_T_Grate, MIName, vSets.T_Grate, 1, 15);
//#undef MIName

/** 14 Кол-во оборотов шнека выгрузки перед розжигом [n] */
#define MIName {S_n,S_i,S_G}
mMemu_UNUM(CUNUM_N_Ignition, MIName, vSets.N_Ignition, 1, 30);
#undef MIName

/** Время розжига [sec] */
#define MIName {S_t,S_i,S_G}
mMemu_UNUM(CUNUM_T_Ignition, MIName, vSets.T_Ignition, 1, 300);
#undef MIName

/** 14 Кол-во оборотов шнека выгрузки перед розжигом [n] */
#define MIName {S_A,S_S,S_t}
mMemu_UNUM(CUNUM_AutoRun, MIName, vSets_com.AutoRun, 0, 1);
#undef MIName


#define MIName {S_t,S_S,S_t}
//mMemu_BTN(CB_Test, MIName, GetTaskID(fIdle), GetTaskID(f_Test));
#undef MIName

#define MIName {S_r,S_u,S_n}
mMemu_BTN(CB_RunStop, MIName, GetTaskID(fIdle), GetTaskID(fRunStop));
#undef MIName


//mMemu_BTN(CB_Supply, MIName, GetTaskID(fSupply_On), GetTaskID(fManual_Off));



//}


const Ctrl_t __flash *const __flash Menu_Main[] = {
  /* 00 */ (const Ctrl_t __flash *) 7,
  /* 01 */ &CB_RunStop,
  /* 02 */ &CUNUM_Temp1,
  /* 03 */ &CUNUM_Power,
  /* 04 */ &CUNUM_N_Unload,
  /* 05 */ &CUNUM_T_Pause,
  /* 06 */ &CUNUM_N_Ignition,
  /* 07 */ &CUNUM_T_Ignition,
  //  /* 07 */ &CUNUM_AutoRun,
  /* 08 */
  /* 09 */
  /* 10 */ //&CB_Test,
  /* 11 */
  /* 12 */
  /* 13 */

};



//;################################## FUNCTION ###################################
//;Name of function:
//// ; fMenuInit
////;
//*/
void fMenuInit(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  fSetsRead();

  if (pFlg->CfgOK != 1) { // Проверка флага с настройками всё впорядке/
    vState = FAULT;
  } else {
    //vState = STOP;
  }

  vRegParam.Temp = 273 + vSets.Temp1;
  vRegParam.ADC_Temp = fGetADC_from_TempLM335(vRegParam.Temp);
  //}
  flgTimerEdit = 0;
  v_Menu.hMenu = (Ctrl_t**)&Menu_Main;
  v_Menu.C_Indx = 1;
  v_Menu.vMode = IDLE;
  v_Menu.Msg = MSG_DRAW;
  fMenuGetHndCtrl();
#if defined(USE_MT_SUB)
  //{ Инициализация стека меню
  MenuSP = 0;
  MenuStk[MenuSP].hMenu = v_Menu.hMenu;
  MenuStk[MenuSP].C_Indx = v_Menu.C_Indx;
  //} Инициализация стека меню
#endif // defined
}



//;################################## FUNCTION ###################################
//;Name of function:
// ; fMenuSendMsg
//;Input:
// ; AL - сообщение обработчику меню. Например: ldi AL, MENU_SEL
//;Return:
// ;
//;Description:
// ; Посылает сообщение обработчику текущего пункта меню (v_Menu_TaskID)
//;
/// TODO (Admin#1#):

//PROC fMenuSendMsg
void fMenuSendMsg(eMENU_MSG_t Menu_Msg)
{
  v_Menu.Msg = Menu_Msg;
  krSendTask(v_Menu.TaskID);
}
//  ret
//ENDP fMenuSendMsg



/** Функция возвращает указатель на контрол текущего пункта меню,
  выполняет контроль границ меню.
  @param  - Входных параметров пока нет.
  @return const Ctrl_t __flash * указатель на контрол текущего пункта меню.

*/
const Ctrl_t __flash *fMenuGetHndCtrl(void)
{
  const Ctrl_t __flash *pCtrl;

  if (v_Menu.C_Indx > (u16)v_Menu.hMenu[0]) {
    v_Menu.C_Indx = 1;
  }

  if (v_Menu.C_Indx < 1) {
    v_Menu.C_Indx = (u16)v_Menu.hMenu[0];
  }

  pCtrl = v_Menu.hMenu[v_Menu.C_Indx];
  v_Menu.TaskID = pCtrl->TaskID;
  return pCtrl;
} /* fMenuGetHndCtrl */



//;################################## FUNCTION ###################################
//;Name of function:
// ; fMenuDefProc
//;Input:
// ; (v_Menu.Msg) = Сообщение, что делать. MENU_DRAW
//;Return:
// ; -
//;Description:
// ; Процедура обработки пункта меню по умолчанию.
// ; Добавить в список задач. Task(fMenuDefProc)
//;
//
//PROC fMenuDefProc

/** Функция выполняет контроль границ меню.
  Процедура обработки пункта меню по умолчанию.
  Добавить в список задач.
  \code
    aTask(fMenuDefProc),

    #Task(fMenuDefProc)

  \endcode
  #v_Menu #Msg Сообщение, что делать. MENU_DRAW
  @return - const Ctrl_t __flash * указатель на контрол текущего пункта меню.

*/


void fMenuDefProc(void)
{
  if (v_Menu.Msg != MSG_NOT) {
    switch (v_Menu.Msg) {
      case (MSG_DRAW):
        fMenuDraw();
        v_Menu.Msg = MSG_DRAW;
        break;

      case (MSG_NEXT):
        fMenuNext();
        v_Menu.Msg = MSG_DRAW;
        break;

      case (MSG_PREV):
        fMenuPrev();
        v_Menu.Msg = MSG_DRAW;
        break;

      case (MSG_SELECT):
        fMenuSelect();
        v_Menu.Msg = MSG_DRAW;
        break;

      case (MSG_PARAM_DEC):
      case (MSG_PARAM_INC): {
          mSendTask(fMenuParamIncDec);
          //v_Menu.Msg = MSG_DRAW;
          break;
        }

      default: {
          v_Menu.Msg = MSG_NOT;
          break;
        }
    }

    // mSendTask(fMenuDraw);
  }

  //fMenuDraw();
  return;
} /* fMenuDefProc */

void fMenuDraw(void)
{
  fMenuDrawCtrl();
}/* fMenuDraw */



void fMenuDraw_szItemMenu(const Ctrl_t __flash *pCtrl)
{
  const u08 __flash *psz;
  psz = pCtrl->pszItemMenu;
  krMemCopyF2R(psz, szParamName_Buf, 3);
  krMemCopyF2R(psz, szParamVal_Buf, 3);
}

//const char __flash StrLED_run[] = {S_r, S_u, S_n};
const char __flash StrLED_StP[] = {S_S, S_t, S_P};
const char __flash StrLED_Brn[] = {S_B, S_r, S_n};


void fMenuDrawCtrl(void)
{
  const Ctrl_t __flash *pCtrl;
  pCtrl = fMenuGetHndCtrl();
  /* NAME */
  fMenuDraw_szItemMenu(pCtrl);

  if (pCtrl == &CB_RunStop) {
    switch (vState) {
      case STOP: {
          //            krMemCopyF2R(StrLED_run, szParamName_Buf, 3);
          break;
        }

      case AFTERBURN: {
          krMemCopyF2R((u08*)StrLED_StP, szParamName_Buf, 3);
          break;
        }

      default: {
          krMemCopyF2R((u08*)StrLED_Brn, szParamName_Buf, 3);
          break;
        }
    }
  }

  switch (pCtrl->MenuType) {
    case MT_UNUM: {
        u16 val;
        val = *pCtrl->pParam.u16Val;

        if (val <= pCtrl->ExPrm1.u_Min) {
          val = pCtrl->ExPrm1.u_Min;
        }

        if (val >= pCtrl->ExPrm2.u_Max) {
          val = pCtrl->ExPrm2.u_Max;
        }

        *pCtrl->pParam.u16Val = val;
        xsprintf((char*)szParamVal_Buf, fmt_3u, val);
        fASCII2_LED(szParamVal_Buf, 3);
      }

    //   case MT_SUB:
    default: {
        break;
      }
  } /* switch (pCtrl->MenuType) */

  return;
}


void fMenuNext(void)
{
  v_Menu.C_Indx++;
}
//ENDP fMenuNext

void fMenuPrev(void)
{
  v_Menu.C_Indx--;
}
//ENDP fMenuPrev
void fMenuSelect(void)
{
  const Ctrl_t __flash *pCtrl;
  //pCtrl = v_Menu.hMenu[v_Menu.C_Indx];
  pCtrl = fMenuGetHndCtrl();

  switch (pCtrl->MenuType) {
    case MT_BUTTON:
      break;

    //    case MT_SUB:
    //      break;

    case MT_UNUM:

      //case MT_SNUM:

      //    case MT_LST:
      //    case MT_STR:
      //    case MT_LST_RAM:
      switch (v_Menu.vMode) {
        case NORMAL: {
            v_Menu.vMode = EDIT;
            break;
          }

        case EDIT: {
            v_Menu.vMode = NORMAL;
            fSetsWrite();
            break;
          }

        default: {
            break;
          }
      }

      break;

    default:
      break;
  }
}
//ENDP fMenuSelect
void fMenuButtonProc(void)
{
  const Ctrl_t __flash *pCtrl;
  pCtrl = fMenuGetHndCtrl();

  switch (v_Menu.Msg) {
    case MSG_SWDN:
      krSendTask(pCtrl->ExPrm1.BtnDnTaskID);
      v_Menu.Msg = MSG_DRAW;
      break;

    case MSG_SWUP:
      krSendTask(pCtrl->ExPrm2.BtnUpTaskID);
      v_Menu.Msg = MSG_DRAW;
      break;

    default:
      break;
  }

  fMenuDefProc();
} /* fMenuButtonProc */
void fMenuDefEditProc(void)
{
  switch (v_Menu.vMode) {
    case NORMAL: {
        switch (v_Menu.Msg) {
          case MSG_NEXT:
            //v_Menu.Msg = MSG_PARAM_INC;
            break;

          case MSG_PREV:
            //v_Menu.Msg = MSG_PARAM_DEC;
            break;

          //case MSG_SWDN:
          case MSG_SWUP:
            v_Menu.Msg = MSG_SELECT;
            break;

          default: {
              break;
            }
        }
      }
      break;

    case EDIT: {
        switch (v_Menu.Msg) {
          case MSG_NEXT: {
              v_Menu.Msg = MSG_PARAM_INC;
              break;
            }

          case MSG_PREV: {
              v_Menu.Msg = MSG_PARAM_DEC;
              break;
            }

          //case MSG_SWDN:
          case MSG_SWUP: {
              v_Menu.Msg = MSG_SELECT;
              break;
            }

          default: {
              break;
            }
        }
      }
      break;

    default:
      break;
  }

  fMenuDefProc();
} /* fMenuDefEditProc */

#if defined(USE_MT_SUB)

void fMenuSubDefProc(void)
{
  switch (v_Menu.Msg) {
    case MSG_NEXT:
      //v_Menu.Msg = MSG_PARAM_INC;
      fMenuDefProc();
      break;

    case MSG_PREV:
      //v_Menu.Msg = MSG_PARAM_DEC;
      fMenuDefProc();
      break;

    //case MSG_SWDN:
    case MSG_SWUP: {
        fMenuSubSelectProc();
      }
      break;

    default:
      v_Menu.Msg = MSG_DRAW;
      break;
  }

  fMenuDefProc();
}
void fMenuSubSelectProc(void)
{
  const Ctrl_t __flash *pCtrl;
  pCtrl = fMenuGetHndCtrl();
  //{ Вход в подменю
  MenuStk[MenuSP].hMenu = v_Menu.hMenu;
  MenuStk[MenuSP].C_Indx = v_Menu.C_Indx;
  v_Menu.hMenu   = pCtrl->ExPrm2.hSubMenu;
  v_Menu.C_Indx = 1;
  MenuSP++;

  if (MenuSP >= sizeof(MenuStk)) {
    MenuSP = sizeof(MenuStk) - 1;
    //} Вход в подменю
  } else {
    //{ Возврат из подменю
    if (MenuSP) {
      MenuSP--;
    }

    v_Menu.hMenu   = MenuStk[MenuSP].hMenu ;
    v_Menu.C_Indx  = MenuStk[MenuSP].C_Indx;
    //} Возврат из подменю
  }
}

#endif // defined

void fMenuParamIncDec(void)
{
  const Ctrl_t __flash *pCtrl;
  //pCtrl = v_Menu.hMenu[v_Menu.C_Indx];
  pCtrl = fMenuGetHndCtrl();
  static u08 CntUP = 0;
  static u08 CntDN = 0;
  u16 tmpInc;
  tmpInc = fGetIncDecVal(CntUP);
  u16 tmpDec;
  tmpDec = fGetIncDecVal(CntDN);

  switch (pCtrl->MenuType) {
    case MT_UNUM: {
        u16 val;
        val = *pCtrl->pParam.u16Val;

        switch (v_Menu.Msg) {
          case MSG_PARAM_INC: {
              CntUP++;
              CntDN = 0;

              if (val <= (pCtrl->ExPrm2.u_Max - tmpInc)) {
                val += tmpInc;
              }

              break;
            } /* MSG_PARAM_INC */

          case MSG_PARAM_DEC: {
              CntUP = 0;
              CntDN++;

              if (val >= (pCtrl->ExPrm1.u_Min + tmpDec)) {
                val -= tmpDec;
              }

              break;
            } /* MSG_PARAM_DEC */

          default:
            break;
        }

        *pCtrl->pParam.u16Val = val;
        break;
      } /* MT_UNUM */

    //    case MT_SNUM:
    //      if (0) {
    //        static s16 val_s;
    //        val_s = *pCtrl->pParam.s16Val;
    //
    //        switch (v_Menu.Msg) {
    //          case MSG_PARAM_INC: {
    //              if ((val_s + (s16)tmpInc) <= (s16)pCtrl->ExPrm2.s_Max) {
    //                val_s += (s16)tmpInc;
    //              }
    //
    //              break;
    //            } /* MSG_PARAM_INC */
    //
    //          case MSG_PARAM_DEC: {
    //              if ((val_s - (s16)tmpDec) >= (s16)pCtrl->ExPrm1.s_Min) {
    //                val_s -= (s16)tmpDec;
    //              }
    //
    //              break;
    //            } /* MSG_PARAM_DEC */
    //
    //          default:
    //            break;
    //        }
    //
    //        *pCtrl->pParam.s16Val = val_s;
    //        break;
    //      } /* MT_SNUM */

    default:
      break;
  }

  v_Menu.Msg = MSG_DRAW;
} /* fMenuParamIncDec */
u08 fGetIncDecVal(u08 CntIncDec)
{
  u08 indx;
  indx = CntIncDec / 10;

  if (indx > 2) {
    indx = 4;
  }

  //indx &= 0b0001;
  return IncDecVal[indx];
}
//;S_Alex
