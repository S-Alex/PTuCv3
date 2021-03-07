#include <avr/io.h>





/* Fuses AtMega32 */


/* Low Fuse Byte */
#define FUSE_CKSEL0      (unsigned char)~_BV(0)
#define FUSE_CKSEL1      (unsigned char)~_BV(1)
#define FUSE_CKSEL2      (unsigned char)~_BV(2)
#define FUSE_CKSEL3      (unsigned char)~_BV(3)
#define FUSE_SUT0        (unsigned char)~_BV(4)
#define FUSE_SUT1        (unsigned char)~_BV(5)
#define FUSE_BODEN       (unsigned char)~_BV(6)
#define FUSE_BODLEVEL    (unsigned char)~_BV(7)
//#define LFUSE_DEFAULT (FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0)

/* High Fuse Byte */
#define FUSE_BOOTRST     (unsigned char)~_BV(0)
#define FUSE_BOOTSZ0     (unsigned char)~_BV(1)
#define FUSE_BOOTSZ1     (unsigned char)~_BV(2)
#define FUSE_EESAVE      (unsigned char)~_BV(3)
#define FUSE_CKOPT       (unsigned char)~_BV(4)
#define FUSE_SPIEN       (unsigned char)~_BV(5)
#define FUSE_JTAGEN      (unsigned char)~_BV(6)
#define FUSE_OCDEN       (unsigned char)~_BV(7)
//#define HFUSE_DEFAULT (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN & FUSE_JTAGEN)


/* LF:0xA4 HF:0xD1 */
FUSES = {
  .low = 0xff
  & FUSE_CKSEL0
  & FUSE_CKSEL1
  //& FUSE_CKSEL2
  & FUSE_CKSEL3
  & FUSE_SUT0
  // & FUSE_SUT1
  & FUSE_BODEN
  //& FUSE_BODLEVEL
  ,

  .high = 0xff
  //& FUSE_BOOTRST
  & FUSE_BOOTSZ0
  & FUSE_BOOTSZ1
  & FUSE_EESAVE
  //& FUSE_CKOPT
  & FUSE_SPIEN // ����� ��������� � ���� �����. ������ ����
  //& FUSE_JTAGEN
  //& FUSE_OCDEN

};

/* Lock Bits */
#define __LOCK_BITS_EXIST
#define __BOOT_LOCK_BITS_0_EXIST
#define __BOOT_LOCK_BITS_1_EXIST
