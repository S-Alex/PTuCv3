#include <stdio.h>
#include <stdlib.h>


#define EEMEM

#define MIN_DELAY  -9999  //минимальное значение задержки PLL, us
#define MAX_DELAY   9999  //максимальное значение задержки PLL, us
#define NOM_DELAY 00 //номинальное значение задержки PLL DFS, us



#define REG_KP_NOM    60  //номинальное значение PllKp
#define REG_KI_NOM    8  //номинальное значение PllKi

#include "types.h"

#include "../PTuCv2_FMW/Sets.h"
#include "../PTuCv2_FMW/Sets_c.h"

#define strs(s) str(s)
#define str(s) "#define "#s
#define fmt "_CRC 0x%04X\n"
FILE *pFile;

uint16_t
crc16_update(uint16_t crc, uint8_t a)
{
  int i;
  crc ^= a;

  for (i = 0; i < 8; ++i) {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }

  return crc;
}

u16 fCRC16(u08 * pBuff, u16 nByte)
{
  u08 tmp;
  u16 tmpCRC16;
  tmpCRC16 = 0xffff;

  while (nByte--) {
    tmpCRC16 = crc16_update(tmpCRC16, *pBuff);
    tmp = *pBuff;
    printf("//0x%02X  _CRC 0x%04X\n", tmp, tmpCRC16);
    fprintf(pFile, "//0x%02X  _CRC 0x%04X\n", tmp, tmpCRC16);
    pBuff++  ;
  }

  return tmpCRC16;
}


int main()
{
  pFile = fopen("CRC16_for_set.h", "w+b");
#ifdef _evSets_com
#define evSets evSets_com
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_com
#ifdef _evSets_Min
#define evSets evSets_Min
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Min
#ifdef _evSets_Mid
#define evSets evSets_Mid
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Mid
#ifdef _evSets_Max
#define evSets evSets_Max
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Max
#ifdef _evSets_Usr1
#define evSets evSets_Usr1
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Usr1
#ifdef _evSets_Usr2
#define evSets evSets_Usr2
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Usr2
#ifdef _evSets_Usr3
#define evSets evSets_Usr3
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Usr3
#ifdef _evSets_Usr4
#define evSets evSets_Usr4
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Usr4
#ifdef _evSets_Usr5
#define evSets evSets_Usr5
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Usr5
#ifdef _evSets_Timers
#define evSets evSets_Timers
  evSets.CRC = fCRC16((u08*)&evSets, sizeof(evSets) - sizeof(evSets.CRC));
  printf(strs(evSets)fmt, evSets.CRC);
  fprintf(pFile, strs(evSets)fmt, evSets.CRC);
#endif // evSets_Timers
  //
  fclose(pFile);
  return 0;
}
