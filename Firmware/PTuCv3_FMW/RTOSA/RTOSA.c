/**
 * \~russian
 * \file
 * \brief ���� "RTOSA.c" �������� ������ ������������ ������� RTOSA.
 *
 * �������� �������� ������� ���� ������������ �������. \ref grpRTOSA
 * \author ����� ��������� ������������
 * \~
 * \~english
 * \file
 * \brief TODO
 * \author Serov Alexandr
 * \~

 * \~ \author (S_Alex)
 *
 */

#include "RTOSA.h"


/**
 * \~russian
 * \addtogroup grpRTOSA ������������ ������� RTOSA.
 * \~english
 * \addtogroup grpRTOSA Operating system RTOSA.
 * \~
 * \code
  #include <RTOSA.h>
  #include <RTOSA.c>
 * \endcode
 * \~russian
 * \brief  �� ������� ���������� ������������ ������ �� ��.
 *
 * � ������ �������, ����� ����������� ���� ��� ���� "����� �����" � ���������� � ����
 * ���� ������ �������. ������� � ������ �� � ������ ��� ��� ��������� �� ����������.
 * ��� ��� �� ����� � ���� ��� ��� ����� ���� � ��������� � ��������� �������� ��� ���������
 * ��������� ����� ���: ��-23, ��-52, ��� "�����" �� �� ZX Spectrum, IBM PC ��� DOS.
 * �� �� ��� ������, ���� ���-�� ����������. � ����� ���������� ���� �� ��� ������ ����������
 * �� ������������ �������� �� ��. � ������ ��������� ���������, ���������, ��� ���������
 * ������� � ���� ��� i8051 �������� ��� ������������� ������������ ������. \n
 * ������� ��� ������� �� ���� � ����� ������� ���������� ��������� � ������� � �����, ��� ���
 * �������, ������� � �������� ��� �������� ������� ��������������. � ����������� �������
 * ������� ������ ��������� ��� �������� �� ������ ����������� (AVR) � ���������� (��).
 * �� ���� ��, ��� �� � ������ ������ ���������.
 * \~english
 * \brief  My RTOS.
 * \~
 *
 *
 *
 * \~russian \author ����� ��������� ������������
 * \~english \author Serov Alexandr
 * \~ \author (S_Alex)
 *
 *  \see
 *  \note
 */

u32 vOS_Tick;
u08 r_RND;
u08 r_TaskS;
u08 r_CntTask;
u08 r_CntTimers;

u08 T0_Reload;

/** \ingroup grpRTOSA */
void krClearTaskQueue(void)
{
  //krMemFill(TaskQueue,0xff,TASKQUEUESIZE);
  u08 indx;

  //  for(indx=0; indx!=TASKQUEUESIZE; indx++)
  for (indx = TASKQUEUESIZE - 1; indx != MAX_TASK; indx--) {
    TaskQueue[indx] = MAX_TASK;
  }
}

/** \ingroup grpRTOSA */
void krClearTimers(void)
{
  u08 indx;
  T_TIMERSPOOL *pTP = (T_TIMERSPOOL*)&TimersPool;
  indx = TIMERSPOOLSIZE;
  r_CntTimers = 0;

  while (indx) {
    pTP->TaskID = MAX_TASK;
    pTP->Time = 0;
    pTP->TStp = 1;
    pTP++;
    indx--;
  }
}

/** \ingroup grpRTOSA */
void krProcessTaskQueue(void)
{
  //if (0) krProcessTaskQueue();
  u08 index;
  u08 CurTaskID;
  //{ ����������� ������� ������ �� ���� ������
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    index = r_TaskS & (TASKQUEUESIZE - 1);
    CurTaskID = TaskQueue[index];

    if (CurTaskID != MAX_TASK) {
      TaskQueue[index] = MAX_TASK; /* �������� ������ ��� ����������*/
      /* ���������� 1 � �������� ��������� r_TaskS */
      u08 tmp = r_TaskS;
      tmp++;
      r_TaskS = (r_TaskS & 0b11110000) | ((tmp) % TASKQUEUESIZE);
      r_CntTask--;
      //     krDedug();
    }
  }

  //} ����������� ������� ������ �� ���� ������
  if (CurTaskID != MAX_TASK) {
    (TaskProcs[CurTaskID])();  /* ����� ������*/
  }
}



/** \ingroup grpRTOSA */
void krCallTaskID(u08 TaskID)
{
  (TaskProcs[TaskID])();  /* ����� ������*/
}

/** \ingroup grpRTOSA */
void krSendTask(u08 TaskID)
{
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    u08 index = r_TaskS >> 4 & (TASKQUEUESIZE - 1);
    u08 CurTaskID = TaskQueue[index];

    if (CurTaskID == MAX_TASK) {
      TaskQueue[index] = TaskID;
      r_CntTask++;
      /* ���������� 1 � �������� ���������*/
      r_TaskS = (r_TaskS + 0x10) & (((TASKQUEUESIZE - 1) << 4) | 0b1111);
      //      krDedug();
    }

    //  ;> critical section
  }
}


/** \ingroup grpRTOSA */
void krSetTimer(u08 TaskID, u16 Time)
{
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    //  ;< ����� � ������� �������� ������� � ������� �������� ID_Task
    u08 indx;
    T_TIMERSPOOL  *pTP = (T_TIMERSPOOL*)&TimersPool;
    indx = TIMERSPOOLSIZE;

    while (indx) {
      if (pTP->TaskID == TaskID) {
        pTP->Time = Time;
        pTP->TStp = 0;

        if (Time == 0) {
          pTP->TaskID = MAX_TASK;
          pTP->TStp = 1;                                                /* ��������� ������� */
          r_CntTimers--;
        }

        return;
      }

      pTP++;
      indx--;
    } /* while (indx) */

    //  ;> ����� � ������� �������� ������� � ������� �������� ID_Task
    //  ;< Search in queue Empty Timer
    pTP = (T_TIMERSPOOL*)&TimersPool;
    indx = TIMERSPOOLSIZE;

    while (indx) {
      if (pTP->TaskID == MAX_TASK) {
        pTP->TaskID = TaskID;
        pTP->Time = Time;
        pTP->TStp = 0;                                           /* ��������� ������ ������� */
        r_CntTimers++;
        break;
      }

      pTP++;
      indx--;
    } /* while (indx) */

    //  ;> Search in queue Empty Timer
    //krError();
    //krDedug();
  }
  //  ;> critical section
  return;
}


/** \ingroup grpRTOSA */
void krTimerRun(u08 TaskID, u08 Stp)
{
  //  ;< ����� � ������� �������� ������� � ������� �������� ID_Task
  u08 indx;
  T_TIMERSPOOL  *pTP = (T_TIMERSPOOL*)&TimersPool;
  indx = TIMERSPOOLSIZE;
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    while (indx) {
      if (pTP->TaskID == TaskID) {
        pTP->TStp = Stp;
        return;
      }

      pTP++;
      indx--;
    }

    //  ;> ����� � ������� �������� ������� � ������� �������� ID_Task
  }
  return;
}


/** \ingroup grpRTOSA */
u16 krGetTimer(u08 TaskID)
{
  //  ;< ����� � ������� �������� ������� � ������� �������� ID_Task
  u08 indx;
  T_TIMERSPOOL  *pTP = (T_TIMERSPOOL*)&TimersPool;
  indx = TIMERSPOOLSIZE;
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    while (indx) {
      if (pTP->TaskID == TaskID) {
        return pTP->Time;
      }

      pTP++;
      indx--;
    }

    //  ;> ����� � ������� �������� ������� � ������� �������� ID_Task
  }
  return 0;
}
/** \ingroup grpRTOSA */
void krClrTimer(u08 TaskID)
{
  //  ;< critical section
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { /*(ATOMIC_FORCEON)*/
    //  ;< ����� � ������� �������� ������� � ������� �������� ID_Task
    u08 indx;
    T_TIMERSPOOL* pTP = (T_TIMERSPOOL*)&TimersPool;
    indx = TIMERSPOOLSIZE;

    while (indx) {
      if (pTP->TaskID == TaskID) {
        pTP->TaskID = MAX_TASK;
        pTP->Time = 0;
        pTP->TStp = 1;
        return;
      }

      pTP++;
      indx--;
    }

    //  ;> ����� � ������� �������� ������� � ������� �������� ID_Task
  }
  //  ;> critical section
}
/** \ingroup grpRTOSA */
void krMemFill(u08 * aMem, u08 bVal, u08 bSize)
{
  while (bSize) {
    *aMem++ = bVal;
    bSize--;
  }
}
/** \ingroup grpRTOSA */
void krMemCopyR2R(u08 * aMemS, u08 * aMemD, u08 bSize)
{
  while (bSize) {
    *aMemD = *aMemS;
    aMemD++;
    aMemS++;
    bSize--;
  }
}
/** \ingroup grpRTOSA */
void krMemCopyF2R(const u08 __flash * aMemS, u08 * aMemD, u08 bSize)
{
  while (bSize--) {
    *aMemD++ = *aMemS++;
    //    *aMemD = *aMemS;
    //    aMemD++;
    //    aMemS++;
    //    bSize--;
  }
}
/** \ingroup grpRTOSA */
u08 krRand(void)
{
  r_RND = ((u16)r_RND * 13 + 17) % 256;
  return r_RND;
}
/** \ingroup grpRTOSA */
inline void mTimerService(void)
{
  u08 indx;
  T_TIMERSPOOL* pTP = (T_TIMERSPOOL*)&TimersPool;
  ADCSRA |= (1 << ADSC);      //ADC Start Conversion
  indx = TIMERSPOOLSIZE;

  while (indx) {
    if ((pTP->TaskID != MAX_TASK)) {
      if ((pTP->TStp == 0)) {
        pTP->Time--;

        if (pTP->Time == 0) {
          krSendTask(pTP->TaskID);
          pTP->TaskID = MAX_TASK;
          r_CntTimers--;
        }
      }
    }

    pTP++;
    indx--;
  }

  vOS_Tick ++;
}

/**
 * \~russian
 * \name ���������� ������� 0.
 * @{
 * \~english
 * TODO
 * \~
 */
#if defined(__AVR_ATmega8__)
ISR(TIMER0_OVF_vect)
{
  TCNT0 = 256 + T0_Reload;
  mTimerService();
}
#elif   defined(__AVR_ATmega32__)\
      ||defined(__AVR_ATmega64__)\
      ||defined(__AVR_ATmega16__)
ISR(TIMER0_COMP_vect)
{
  mTimerService();
}
#elif defined(__AVR_ATtiny261__)
ISR(TIMER0_OVF_vect)
{
  //  nop();
  TCNT0L = 256 + T0_Reload;
  mTimerService();
}
#endif
/** @} */
