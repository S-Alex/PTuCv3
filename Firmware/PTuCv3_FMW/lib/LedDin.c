////;File Led3din.c

#include "LedDin.h"
#include "vPorts.h"

void (*pfDin_Out)(u16);

u08 vDinOff;
u08 vLED_CA_CC;
u08 vDinam[3 + 2] = {
  S_1, S_2, S_3,
  1, ~0b00000001
};

void fDin_Out(u16 data)
{
  if (vLED_CA_CC) {
    data = ~data;
  }

  fOut_vPort(1, ((data >> 8) & 0xff), IDPORT);
  fOut_vPort(0, ((data >> 0) & 0xff), IDPORT);
}


void fDin_Init()
{
  //{* Настройка физического канала передачи данных для динамической индикации */
  mSet_fDin_Out(fDin_Out);     /* Загрузка указателя на функцию вывода в порт */
  //}* Настройка физического канала передачи данных для динамической индикации */
  // < Все разряды настроим на вывод
  fOut_vPort(0, 0xff, IDDDR);
  fOut_vPort(1, 0xff, IDDDR);
  // > Все разряды настроим на вывод
  // < Тушим все разряды
  pfDin_Out(0xff00);
  // > Тушим все разряды
  vDinCnt = 0b00000001;
  vDinMsk = 0b00000001;
} /* fDin_Init() */



//;###############################################################################
void fDin_Fresh()
{
  u16 tmp_1;
  { /* < Calc next position */
    vDinMsk = (vDinMsk << 1);
    vDinCnt++;
    // < Тушим все разряды
    pfDin_Out(0xff00);
    // > Тушим все разряды

    if (vDinCnt >= (mItems(vDinam) - 2)) {
      vDinCnt = 0;
      vDinMsk = 0b00000001;
      fKBD_Exe();
    }
  } /* > Calc next position */

  if (vDinOff & 1) return;

  u08 tmp_3 = vDinam[vDinCnt];
  u08 tmp_2 = ~vDinMsk;
  tmp_1 = tmp_2 << 8 | tmp_3;
  //tmp_1 |= tmp_3;
  pfDin_Out(tmp_1);
  //  pfDin_Out((~vDinMsk << 8) | vDinam[vDinCnt]);
}


//;Преобразование двоичного в 7сег. индикатор
__flash
const  u08 Tab_7Seg[] = {
  S_0, S_1, S_2, S_3, S_4, S_5, S_6, S_7,
  S_8, S_9, S_A, S_B, S_C, S_D, S_E, S_F
};


u08 fB27S(u08 Data)
{
  return  Tab_7Seg[Data];
}
//;S_Alex
