//#include "main.h"
#include  "Sets.h"

#define _evSets_com 1
#define _evSets_Usr1 1


#ifndef evSets_com_CRC
#define evSets_com_CRC 0
#endif // evSets_com_CRC

#ifndef evSets_Usr1_CRC
#define evSets_Usr1_CRC 0
#endif // evSets_Usr1_CRC

EEMEM Sets_com_t evSets_com = {
  .AutoRun      = 0         ,  /**< �������������� ������ ������� ��� ������ ������� */
  .TimeOut      = 15        ,  /**< ����� ����. ����� ������� ����, ����� ��� ���������� ����������. */
  .BlowTime     = 33        ,  /**< ����� �������� ������� �� ����� ������ �������� ������� */
  .Uref         = 4096      ,  /**< ������� ���������� ��. 4096 */
  .T_Offset     = 0         ,  /**< �������� �����������. */
//  .ScrewTimeOut = 5         ,  /**< ����� ����� ������� ���� ������� �����������, [sec] */
//  .T_Alarm      = 99        ,  /**< ����� ������ ������� ������. */
//  .Level_Empty  = LEVEL_EMPTY, /**<  */
//  .Level_Full   = LEVEL_FULL,  /**<  */

  .CRC          = evSets_com_CRC,
};


EEMEM Sets_t evSets_Usr1 = {
  .T_Pause    = 15  ,     /* 1 ����� ����� �������� ������� [sec] */
  .N_Unload   = 30  ,     /* 2 ���-�� �������� ����� �������� ������� � ����� ������� [n] */
  .T_TEN      = 15  ,     /* 3 ����� ��������� ���� ��� ������� �������. [sec] */
  .Temp1      = 60  ,     /* 6 ����������� ����� ��������� [�C] */
  .dTemp1     = 1   ,     /* 7 ������ ����������� �����, ������ [�C]*/
//  .N_Grate    = 5   ,     /* 10 ������� ������� ����� �������� ���������� ����� ������� [n] */
//  .T_Grate    = 3   ,     /* 11 ������� ������� �������� �����. [sec] */
  .N_Ignition = 5   ,     /* 13 ���-�� �������� ����� �������� ����� �������� [n] */
  .T_Ignition = 300 ,     /* 9 ����� ������� [sec] */
  .Power      = 100 ,        /*  */
  .CRC        = evSets_Usr1_CRC,

};
