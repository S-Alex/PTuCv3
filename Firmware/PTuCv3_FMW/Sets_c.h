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
  .AutoRun      = 0         ,  /**< Автоматический запуск горелки при подаче питания */
  .TimeOut      = 15        ,  /**< Время меню. Время простоя меню, выход без сохранения параметров. */
  .BlowTime     = 33        ,  /**< Время продувки горелки во время дожига остатков топлива */
  .Uref         = 4096      ,  /**< Опорное напряжение мВ. 4096 */
  .T_Offset     = 0         ,  /**< Смещение температуры. */
//  .ScrewTimeOut = 5         ,  /**< Время через которое шнек считать заклиненным, [sec] */
//  .T_Alarm      = 99        ,  /**< Время выдачи сигнала аварии. */
//  .Level_Empty  = LEVEL_EMPTY, /**<  */
//  .Level_Full   = LEVEL_FULL,  /**<  */

  .CRC          = evSets_com_CRC,
};


EEMEM Sets_t evSets_Usr1 = {
  .T_Pause    = 15  ,     /* 1 Пауза между подачами топлива [sec] */
  .N_Unload   = 30  ,     /* 2 Кол-во оборотов шнека выгрузки топлива в топку горелки [n] */
  .T_TEN      = 15  ,     /* 3 Время включения ТЭНа для розжига пеллеты. [sec] */
  .Temp1      = 60  ,     /* 6 Температура котла установка [°C] */
  .dTemp1     = 1   ,     /* 7 дельта Температуры котла, ошибка [°C]*/
//  .N_Grate    = 5   ,     /* 10 Ворошим решетку через заданное количество подач топлива [n] */
//  .T_Grate    = 3   ,     /* 11 Ворошим решетку заданное время. [sec] */
  .N_Ignition = 5   ,     /* 13 Кол-во оборотов шнека выгрузки перед розжигом [n] */
  .T_Ignition = 300 ,     /* 9 Время розжига [sec] */
  .Power      = 100 ,        /*  */
  .CRC        = evSets_Usr1_CRC,

};
