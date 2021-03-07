#include "Tasks.h"

const TPTR __flash TaskProcs[] = {
  //;< Список адресов задач
  /* 01 */ aTask(fIdle),
  /* 02 */ aTask(fRunStop),
  /* 03 */ aTask(fFlash),
  /* 04 */ aTask(fMenu),
  /* 05 */ //aTask(fFaultIgnition),
  /* 06 */ aTask(fBuzOn),
  /* 07 */ aTask(fBuzOff),
  /* 08 */ aTask(fBunker_Load_TimeOut),
  /* 09 */ //aTask(fTEN_AirOn),
  //{ Menu */
  /* 10 */ aTask(fMenuDefEditProc),
  /* 11 */ aTask(fMenuDefProc),
  /* 13 */ aTask(fMenuDraw),
  /* 13 */ aTask(fMenuNext),
  /* 14 */ aTask(fMenuPrev),
  /* 15 */ aTask(fMenuSelect),
  /* 16 */ aTask(fMenuParamIncDec),
  /* 17 */ aTask(fMenuButtonProc),
  /* 18 */ //aTask(fMenuSubDefProc),
  //} Menu */
  #ifdef TEST_MENU
  /* 19 */ aTask(f_Test),
  #endif // TEST_MENU
  /* 20 */ //aTask(fSupply_On),
  /* 21 */ //aTask(fSupply_Off),
  /* 22 */ //aTask(fScrew_R_On),
  /* 23 */ //aTask(fScrew_L_On),
  /* 24 */ aTask(fMenuInit),
  /* 25 */
  /* 26 */ aTask(fReUnload_On),
  /* 27 */ //aTask(fTEN_On),
  /* 28 */ //aTask(fFuelOn),
  /* 29 */ aTask(fTEN_OnTimeLeft),
  /* 30 */ //aTask(fManual_Off),
  /* 31 */ aTask(fGrate_On),
  /* 32 */ //aTask(fAlarm_On),
  /* 33 */ //aTask(fClean_On),
  /* 34 */ aTask(fWait_Time_2Next),
  /* 35 */ //aTask(fFan_On),
  /* 36 */ //aTask(fPump_On),
  /* 37 */ aTask(fCntScrew),
  /* 38 */ aTask(fSQGet),
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
};







