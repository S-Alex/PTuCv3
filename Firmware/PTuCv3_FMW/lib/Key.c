//----------------------------------------------------------------------------

//Keyboard support module

//----------------------------------------------------------------------------

#include "Main.h"
//#include "Keyboard.h"

#define ms2sys(Time_ms) Time_ms

//----------------------------- Constants: -----------------------------------
#define KEY_NO          0x00
#define REP_S           0x00
#define REP_F           0x80

#define DBOUNCE_TIME           50   //  debounce time, ms
#define AUTOREPEAT_DELAY      800   //  initial autorepeat delay,   mS
#define AUTOREPEAT_SLOW_RATE  180   //  slow autorepeat rate,   mS
#define AUTOREPEAT_SLOW_COUNT  16   //  slow autorepeat step count
#define AUTOREPEAT_FAST_RATE   60   //  fast autorepeat rate,   mS

//------------------------------ Variables: ----------------------------------

static char KeyCode;

//------------------------- Function prototypes: -----------------------------

char Scan(void);

char(*pf_Scan)(void);

//---------------------------- Keyboard init: --------------------------------

void Keyboard_Init(void)
{
  KeyCode = KEY_NO;
  pf_Scan = &fKBD_Scan;
}

//---------------------------- Scan keyboard: --------------------------------

char Scan(void)
{
  return pf_Scan();
}

//-------------------------- Keyboard processing: ----------------------------

void Keyboard_Exe(void)
{
  static char LastCode = KEY_NO;
  static char TempCode = KEY_NO;
  static char DbncTimer = 0;
  static int  RepTimer = 0;
  static char RepCnt = 0;

  if (DbncTimer) {
    DbncTimer--;
  }

  if (RepTimer) {
    RepTimer--;
  }

  char scan_key = Scan();

  if (scan_key != LastCode) {     //new press
    if (scan_key != TempCode) {   //bounce
      TempCode = scan_key;
      DbncTimer = ms2sys(DBOUNCE_TIME);
    } else {
      if (!DbncTimer) {
        if (scan_key != KEY_NO) { //key pressed
          RepTimer = ms2sys(AUTOREPEAT_DELAY);
          KeyCode = scan_key;
        }

        LastCode = scan_key;
        RepCnt = 0;
      }
    }
  } else { //key holded
    if (RepTimer == 1) { //repeat timer is over
      if (RepCnt < AUTOREPEAT_SLOW_COUNT) {
        KeyCode = scan_key | REP_S; //slow autorepeat
        RepTimer = ms2sys(AUTOREPEAT_SLOW_RATE);
        RepCnt++;
      } else {
        KeyCode = scan_key | REP_F; //fast autorepeat
        RepTimer = ms2sys(AUTOREPEAT_FAST_RATE);
      }
    }
  }
}

//----------------------------- Get key code: --------------------------------

char Keyboard_GetCode(void)
{
  char code = KeyCode;
  KeyCode = KEY_NO;
  return (code);
}

//----------------------------------------------------------------------------
