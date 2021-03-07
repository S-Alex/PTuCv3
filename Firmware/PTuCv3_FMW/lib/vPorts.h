//File: vPorts.h
#ifndef VPORTS_H
#define VPORTS_H

#include <avr/io.h>
#include "MacroSA.h"

#include  "RTOSA/types.h"



/**
 * \~russian
 * \addtogroup vPorts Библиотека виртуальных портов.
 * \~english
 * \addtogroup vPorts Virtual ports LIB.
 * \~
 * \code
  #include <vPorts.h>
  #include <vPorts.c>
 * \endcode
 * \~russian
 * \brief  Основные функции для виртуальных портов.
 * \~english
 * \brief  Basic routines for virtual ports.
 * \~
 *
 *
 *
 * \~russian \author Серов Александр Владимирович
 * \~english \author Serov Alexandr
 * \~ \author (S_Alex)
 *
 *  \see
 *  \note
 */

/** \ingroup vPorts */
typedef enum ID_Port {
  IDPORT = 0, /**< - для доступа к регистру защёлке порта */
  IDDDR, /**< - для доступа к регистру направления данных порта */
  IDPIN, /**< - для доступа к регистру состояния входных линий порта */
} ID_Port_t;


void fOut_vPort(u08 nPort, u08 Data, ID_Port_t Id_);
void fOut_pvPort(const u08 __flash *pvPort, u08 Data, ID_Port_t Id_);


#endif // VPORTS_H


