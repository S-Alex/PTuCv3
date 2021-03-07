//;File KBD_3x1.h
//;Updated: "2015-07-16"

#ifndef INCLUDE_KBD_3X1_H
#define INCLUDE_KBD_3X1_H

#define KEY_TIME_SHORT      (3 )
#define KEY_TIME_LONG       (30)
#define KEY_TIME_AREPEAT1   (40)
#define KEY_TIME_AREPEAT2   (72)
#define KEY_TIME_REPEAT     (80)



#ifndef KEY_01
#define KEY_01      PORTD,5,0
#endif // KEY_01

#ifndef KEY_02
#define KEY_02      PORTC,3,0
#endif // KEY_02

#ifndef KEY_03
#define KEY_03      PORTC,2,0
#endif // KEY_03

#if (1)
typedef struct {
  u08 Last;
  u08 Tick;
  u08 AutoRep;
  u08 act;
  u08 wt;

} t_KBD;
#else
typedef struct {
  u16 Last;
  u16 Tick;
  u16 AutoRep;
  u08 act;

} t_KBD;
#endif

typedef enum {
  KBD_NO,   /**< Состояние энкодера прежнее       */
  KBD_UP,   /**< Вращение энкодера на увеличение  */
  KBD_DN,   /**< Вращение энкодера на уменьшение  */
  KBD_SWUP, /**< Кнопка энкодера была отпущена    */
  KBD_SWDN, /**< Кнопка энкодера была нажата      */
} eKBD_MSG;

void fKBD_Init(void);
u08 fKBD_Scan(void);
u08 fKBD_GetKey(void);
void  fKBD_Exe(void);

extern t_KBD v_KBD;



#endif // INCLUDE_KBD_3X1_H









