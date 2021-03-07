//;File LedDin.h
#ifndef INCLUDE_LEDDIN_H
#define INCLUDE_LEDDIN_H

#include  "main.h"

extern u08 vDinOff;

extern u08 vDinam[];
#define vDIG0 vDinam[0]
#define vDIG1 vDinam[1]
#define vDIG2 vDinam[2]
#define vDinCnt vDinam[3]
#define vDinMsk vDinam[4]

//#define vDinCnt vDinam[(mItems(vDinam)-2)]
//#define vDinMsk vDinam[(mItems(vDinam)-1)]


extern void (*pfDin_Out)(u16);
#define mSet_fDin_Out(func) pfDin_Out = (void(*)(u16))(&func)

/* This is a pointer to user defined output function. It must be initialized
   before using this modle.
*/

u08 fB27S(u08 Data);
void fDin_Init();
// inline void fOutPort(const u08 Data) ;
void fDin_Fresh(void);


//.nolist
//.dseg
//;###############################################################################
//vDinCnt:      .byte 1 ;Current position
//;< Display 1
//vDin1_1:      .byte 1 ;Dig1 Data
//vDin1_2:      .byte 1 ;Dig2 Data
//              .byte 1 ;Reserve
//vDin1_3:      .byte 1 ;Dig3 Data
//;> Display 1
//;< Display 2
//vDin2_1:      .byte 1 ;Dig1 Data
//vDin2_2:      .byte 1 ;Dig2 Data
//              .byte 1 ;Reserve
//vDin2_3:      .byte 1 ;Dig3 Data
//;> Display 2
//
//;###############################################################################
//.cseg
//.list
//
//;###############################################################################
//;Порт индикатора
#define LED_A PORTD, 5
#define LED_B PORTD, 7vDinam
#define LED_C PORTD, 2
#define LED_D PORTB, 6
#define LED_E PORTB, 7
#define LED_F PORTD, 6
#define LED_G PORTD, 3
#define LED_H PORTD, 4


//;---------------------------------------------------
#define a (1<<0)/*;  a    */
#define b (1<<1)/*;f   b  */
#define c (1<<2)/*;  g    */
#define d (1<<3)/*;e   c  */
#define e (1<<4)/*;  d  h */
#define f (1<<5)/*;       */
#define g (1<<6)/*;       */
#define h (1<<7)/*;       */


#define   S_0  (a|b|c|d|e|f)
#define   S_1  (b|c)
#define   S_2  (a|b|g|e|d)
#define   S_3  (a|b|c|d|g)
#define   S_4  (b|c|f|g)
#define   S_5  (a|f|g|c|d)
#define   S_6  (a|f|e|d|c|g)
#define   S_7  (a|b|c)
#define   S_8  (a|b|c|d|e|f|g)
#define   S_9  (a|b|c|d|f|g)

#define   S_A  (a|b|c|e|f|g)
#define   S_B  (c|d|e|f|g)
#define   S_C  (a|d|e|f)
#define   S_D  (b|c|d|e|g)
#define   S_E  (a|d|e|f|g)
#define   S_F  (a|e|f|g)

/*;  a    */
/*;f   b  */
/*;  g    */
/*;e   c  */
/*;  d  h */
/*;       */
#define   S_L  (      d|e|f  )
#define   S_S  (a|  c|d|  f|g)

#define   S_t  (      d|e|f|g)
#define   S_o  (    c|d|e|  g)
#define   S_n  (    c|  e|  g)
#define   S_H  (  b|c|  e|f|g)
#define   S_P  (a|b|    e|f|g)
#define   S_u  (    c|d|e    )
#define   S_U  (  b|c|d|e|f  )
#define   S_r  (        e|  g)
#define   S_G  (a|  c|d|e|f  )
#define   S_i  (    c        )

#define   S_Hi   (a            )
#define   S_Mid  (            g)
#define   S_Low  (      d      )
#define   S_Dot  (h            )
#define   S_BLNK  (0)


//;--------------------------------------------------------------------------------
#define LED_Pos PORTD
//;---------------------------------------------------
#define DIG0  PORTD,0
#define DIG1  PORTD,1
#define DIG2  PORTD,2

#define PORT_LED LED_H,LED_G,LED_F,LED_E,LED_D,LED_C,LED_B,LED_A

#define PORT_DIG DIG2,DIG1,DIG0
#endif // INCLUDE_LEDDIN_H
