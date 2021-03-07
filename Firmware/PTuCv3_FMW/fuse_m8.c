#include <avr/io.h>
/* Low Fuse Byte */
/* #define FUSE_CKSEL0      (unsigned char)~_BV(0)
 * #define FUSE_CKSEL1      (unsigned char)~_BV(1)
 * #define FUSE_CKSEL2      (unsigned char)~_BV(2)
 * #define FUSE_CKSEL3      (unsigned char)~_BV(3)
 * #define FUSE_SUT0        (unsigned char)~_BV(4)
 * #define FUSE_SUT1        (unsigned char)~_BV(5)
 * #define FUSE_BODEN       (unsigned char)~_BV(6)
 * #define FUSE_BODLEVEL    (unsigned char)~_BV(7)
 * #define LFUSE_DEFAULT (FUSE_SUT0 & FUSE_CKSEL3 & FUSE_CKSEL2 & FUSE_CKSEL1)
 *
 * / * High Fuse Byte */
/* #define FUSE_BOOTRST     (unsigned char)~_BV(0)
 * #define FUSE_BOOTSZ0     (unsigned char)~_BV(1)
 * #define FUSE_BOOTSZ1     (unsigned char)~_BV(2)
 * #define FUSE_EESAVE      (unsigned char)~_BV(3)
 * #define FUSE_CKOPT       (unsigned char)~_BV(4)
 * #define FUSE_SPIEN       (unsigned char)~_BV(5)
 * #define FUSE_WDTON       (unsigned char)~_BV(6)
 * #define FUSE_RSTDISBL    (unsigned char)~_BV(7)
 * #define HFUSE_DEFAULT (FUSE_SPIEN & FUSE_BOOTSZ1 & FUSE_BOOTSZ0)
 */

//HF = 0xD7; LF = 0x24 /* Для работы от внутреннего генератора 8 МГц */
//HF = 0xD7; LF = 0xF0 /* Для работы от внешнего кварца 8 МГц */

FUSES = { /* For Atmega8 */
  .low = 0xff
  & FUSE_CKSEL0
  & FUSE_CKSEL1
  //& FUSE_CKSEL2
  & FUSE_CKSEL3
  & FUSE_SUT0
  //& FUSE_SUT1
  & FUSE_BODEN
  & FUSE_BODLEVEL,
  .high = 0xff
  //& FUSE_BOOTRST
  //& FUSE_BOOTSZ0
  //& FUSE_BOOTSZ1
  & FUSE_EESAVE
  //& FUSE_CKOPT
  & FUSE_SPIEN      // Очень осторожно с этим битом. Должен быть
  //& FUSE_WDTON
  //& FUSE_RSTDISBL // Очень осторожно с этим битом. За комментировать этот бит.
};

/* Lock Bit Modes
 * LB_MODE_1 //No memory lock features enabled.
 * LB_MODE_2 //Further programming of the Flash and EEPROM is disabled
 * LB_MODE_3 //Further programming and verification of the Flash and EEPROM is disabled
 *
 * BLB0_MODE_1 //No restrictions for SPM or LPM accessing the Application section.
 * BLB0_MODE_2 //SPM is not allowed to write to the Application section
 * BLB0_MODE_3 //SPM is not allowed to write to the Application section, and LPM
 *             //executing from the Boot Loader section is not allowed to read
 *             //from the Application section. If Interrupt Vectors are placed in
 *             //the Boot Loader section, interrupts are disabled while executing
 *             //from the Application section.
 * BLB0_MODE_4 //LPM executing from the Boot Loader section is not allowed to
 *             //read from the Application section. If Interrupt Vectors are placed
 *             //in the Boot Loader section, interrupts are disabled while
 *             //executing from the Application section.
 *
 * BLB1_MODE_1 //No restrictions for SPM or LPM accessing the Boot Loader section.
 * BLB1_MODE_2 //SPM is not allowed to write to the Boot Loader section.
 * BLB1_MODE_3 //SPM is not allowed to write to the Boot Loader section, and LPM
 *             //executing from the Application section is not allowed to read
 *             //from the Boot Loader section. If Interrupt Vectors are placed in
 *             //the Application section, interrupts are disabled while executing
 *             //from the Boot Loader section.
 * BLB1_MODE_4 //LPM executing from the Application section is not allowed to
 *             //read from the Boot Loader section. If Interrupt Vectors are
 *             //placed in the Application section, interrupts are disabled while
 *             //executing from the Boot Loader section.
 */

//LOCKBITS = (LB_MODE_1 & BLB0_MODE_1 & BLB1_MODE_1);
LOCKBITS = (LB_MODE_3 & BLB0_MODE_4 & BLB1_MODE_4);

#include  <avr/signature.h>
