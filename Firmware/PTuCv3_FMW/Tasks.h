#ifndef TASK_H
#define TASK_H 1
//include "RTOSA/RTOSA.h"
#include "main.h"

typedef struct {
  //;< Список адресов задач
  /* 01 */ Task(fIdle);
  /* 02 */ Task(fRunStop);
  /* 03 */ Task(fFlash);
  /* 04 */ Task(fMenu);
  /* 05 */ //Task(fFaultIgnition);
  /* 06 */ Task(fBuzOn);
  /* 07 */ Task(fBuzOff);
  /* 08 */ Task(fBunker_Load_TimeOut);
  /* 09 */ //Task(fTEN_AirOn);
  //{ Menu */
  /* 10 */ Task(fMenuDefEditProc);
  /* 11 */ Task(fMenuDefProc);
  /* 13 */ Task(fMenuDraw);
  /* 13 */ Task(fMenuNext);
  /* 14 */ Task(fMenuPrev);
  /* 15 */ Task(fMenuSelect);
  /* 16 */ Task(fMenuParamIncDec);
  /* 17 */ Task(fMenuButtonProc);
  /* 18 */ //Task(fMenuSubDefProc);
  //} Menu */
  #ifdef TEST_MENU
  /* 19 */ Task(f_Test);
  #endif // TEST_MENU
  /* 20 */ //Task(fSupply_On);
  /* 21 */ //Task(fSupply_Off);
  /* 22 */ //Task(fScrew_R_On);
  /* 23 */ //Task(fScrew_L_On);
  /* 24 */ Task(fMenuInit);
  /* 25 */
  /* 26 */ Task(fReUnload_On);
  /* 27 */ //Task(fTEN_On);
  /* 28 */ //Task(fFuelOn);
  /* 29 */ Task(fTEN_OnTimeLeft);
  /* 30 */ //Task(fManual_Off);
  /* 31 */ Task(fGrate_On);
  /* 32 */ //Task(fAlarm_On);
  /* 33 */ //Task(fClean_On);
  /* 34 */ Task(fWait_Time_2Next);
  /* 35 */ //Task(fFan_On);
  /* 36 */ //Task(fPump_On);
  /* 37 */ Task(fCntScrew);
  /* 38 */ Task(fSQGet);
  /* 39 */
  /* 40 */
  /* 41 */
  /* 42 */
  /* 43 */
  /* 44 */
  /* 45 */
  /* 46 */
  /* 47 */
  /* 48 */
  /* 49 */
  /* 50 */
  /* 51 */

  //;> Список адресов задач
} TaskProcsPtr_t;


#endif //TASK_H


