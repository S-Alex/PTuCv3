#include "main.h"
#include  <h:\avr\include\avr\eeprom.h>

#include  "Sets_c.h"


Sets_t vSets;           /**< Текущие настройки выбранного режима работы */
Sets_com_t vSets_com;   /**< Общие настройки контроллера */


u16 f_Write_CRC_Block(u08 *pBuf, u08 *pEBuf, u16 nByte)
{
  u16 tmpCRC;
  u16 *pCRC;
  u16 nDataByte;
  nDataByte = nByte - sizeof(tmpCRC);
  pCRC = (u16*)(pBuf + nDataByte);
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    tmpCRC = fCRC16(pBuf, nByte - sizeof(tmpCRC));
    *pCRC = tmpCRC;
    eeprom_update_block(pBuf, pEBuf, nByte);
  }
  return tmpCRC;
}


void fSetsRead(void)
{
  volatile Flg_t *pFlg = (Flg_t*)(&gFlagsL); /* Инициализация указателя на структуру флагов */
  pFlg->CfgOK = 1; // Установка флага с настройками всё впорядке/
  u16 *pvSets;
  uint16_t *pevSets;
  u16 vSets_com_CRC;
  u16 vSets_CRC;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    eeprom_read_block(&vSets_com, &evSets_com, sizeof(vSets_com));
    vSets_com_CRC = fCRC16((u08*)&vSets_com, sizeof(vSets_com));

    if (vSets_com_CRC != 0) {
      /* Ошибка CRC настроек */
      pFlg->CfgOK = 0;                       /* Сброс флага с настройками не всё впорядке, */
      pszError = (u08*)&szFaultCRCc;
      return;
    }

    pvSets  = (u16*)&vSets;
    pevSets = (uint16_t*)&evSets_Usr1;
    eeprom_read_block(pvSets, pevSets, sizeof(Sets_t));
    vSets_CRC = fCRC16((u08*)&vSets, sizeof(vSets));
  }

  if (vSets_CRC != 0) {
    /* Ошибка CRC настроек сервисного меню */
    pFlg->CfgOK = 0;                       /* Сброс флага с настройками не всё впорядке, */
    pszError = (u08*)&szFaultCRCs;
  }

  return;
}  /* void fReadSets(void) */


void fSetsWrite(void)
{
  u16 *pvSets;
  uint16_t *pevSets;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pvSets  = (u16*)&vSets;
    vSets_com.CRC = fCRC16((u08*)&vSets_com, sizeof(vSets_com) - sizeof(vSets_com.CRC));
    vSets.CRC = fCRC16((u08*)&vSets, sizeof(vSets) - sizeof(vSets.CRC));
    eeprom_update_block(&vSets_com, &evSets_com, sizeof(vSets_com));
    pevSets  = (uint16_t*)&evSets_Usr1;
    eeprom_update_block(pvSets, pevSets, sizeof(Sets_t));
  }
  return;
}   /* void fWriteSets(void) */

