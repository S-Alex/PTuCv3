//File MacroSA.h
#ifndef MACROSA_H_INCLUDED
#define MACROSA_H_INCLUDED

//#define __AVR_ATmega8__





#define NEW_PIN_MACROS

#include <avr\builtins.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define mItems(Mass) (sizeof(Mass)/sizeof(Mass[0]))

#ifndef offsetof
#define offsetof(TYPE, MEMBER) (__builtin_offsetof (TYPE, MEMBER))
#endif // offsetof


//(&((sMainMenu *)0)->MM_02)
#define mGetMenuID(MEMBER) (__builtin_offsetof (sMM, MEMBER))

#define DDR(Port) (*(volatile u08 *)(_SFR_ADDR(Port)-1))
#define PIN(Port) (*(volatile u08 *)(_SFR_ADDR(Port)-2))


/*
//#define mPinOut(PiN) \
//  asm volatile("sbi %0-1,%1"::"I" (_SFR_IO_ADDR(P_##PiN)),"I" (B_##PiN))
//#define mPinIn(PiN) \
//  asm volatile("cbi %0-1,%1"::"I" (_SFR_IO_ADDR(P_##PiN)),"I" (B_##PiN))
//#define mPinSet(PiN) \
//  asm volatile("sbi %0,%1"::"I" (_SFR_IO_ADDR(P_##PiN)),"I" (B_##PiN))
//#define mPinClr(PiN) \
//  asm volatile("cbi %0,%1"::"I" (_SFR_IO_ADDR(P_##PiN)),"I" (B_##PiN))
//#define mPinCpl(PiN) \
//  asm volatile("sbi %0-2,%1"::"I" (_SFR_IO_ADDR(P_##PiN)),"I" (B_##PiN))
*/

#define PinMarge(MRG_Port,PiN) MRG_Port |= (1<<PiN)
#define PinMarge_(mrg,Port,Pin) PinMarge(MRG##Pin)

#define mPinMarge(...) PinMarge_(mrg,Port,##__VA_ARGS__)

#ifndef NEW_PIN_MACROS

#define PinOut(Port,PiN) (*(volatile u08 *)(_SFR_ADDR(Port)-1))|= (1<<PiN)
#define PinIn(Port,PiN)  (*(volatile u08 *)(_SFR_ADDR(Port)-1))&=~(1<<PiN)
#define PinSet(Port,PiN) (*(volatile u08 *)(_SFR_ADDR(Port)))|=   (1<<PiN)
#define PinClr(Port,PiN) (*(volatile u08 *)(_SFR_ADDR(Port)))&=~  (1<<PiN)
#define PinCpl(Port,PiN) (*(volatile u08 *)(_SFR_ADDR(Port)))^=   (1<<PiN)

#define PinIs(Port,PiN) ((*(volatile u08 *)(_SFR_ADDR(Port)-2))&(1<<PiN))
#define PinBit(Port,PiN) PiN


#define mPinOut(Pin) PinOut(Pin)
#define mPinIn(Pin)  PinIn(Pin)
#define mPinSet(Pin) PinSet(Pin)
#define mPinClr(Pin) PinClr(Pin)
#define mPinCpl(Pin) PinCpl(Pin)
#define mPinIs(Pin)  PinIs(Pin)
#define mPinBit(Pin) PinBit(Pin)

#else

#define PinOut(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)-1)) |=  (1<<PiN)
#define PinIn(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)-1)) &= ~(1<<PiN)
#define PinSet(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)))   |=  (1<<PiN)
#define PinClr(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)))   &= ~(1<<PiN)
#define PinCpl(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)))   ^=  (1<<PiN)

#define PinOn(Port,PiN,ALvl)\
  do{\
    u08 tmp;\
    tmp = (*(volatile u08 *)(_SFR_ADDR(Port)));\
    if(ALvl) tmp |=  (1<<PiN);\
    else     tmp &= ~(1<<PiN);\
    (*(volatile u08 *)(_SFR_ADDR(Port))) = tmp;\
  }while(0);

#define PinOff(Port,PiN,ALvl)\
  do{\
    u08 tmp;\
    tmp = (*(volatile u08 *)(_SFR_ADDR(Port)));\
    if(ALvl) tmp &= ~(1<<PiN);\
    else     tmp |=  (1<<PiN);\
    (*(volatile u08 *)(_SFR_ADDR(Port))) = tmp;\
  }while(0);

#define PinIs(Port,PiN,ALvl) ((*(volatile u08 *)(_SFR_ADDR(Port)-2))&(u08)(1<<PiN))

#define PinIsAct_(Port,PiN,ALvl) ((*(volatile u08 *)(_SFR_ADDR(Port)-2)^(0xff+ALvl))&(1<<PiN))


#define PinIsAct(Port,PiN,ALvl) PinIsAct##ALvl(Port,PiN)

#define PinIsAct0(Port,PiN) (!((*(volatile u08 *)(_SFR_ADDR(Port)-2))&(1<<PiN)))
#define PinIsAct1(Port,PiN)   ((*(volatile u08 *)(_SFR_ADDR(Port)-2))&(1<<PiN))


#define PinBit(Port,PiN,ALvl) PiN

#define PinDDR(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)-1))
#define PinPIN(Port,PiN,ALvl) (*(volatile u08 *)(_SFR_ADDR(Port)-2))


#define mPinOut(Pin) PinOut(Pin)
#define mPinIn(Pin)  PinIn(Pin)
#define mPinSet(Pin) PinSet(Pin)
#define mPinClr(Pin) PinClr(Pin)
#define mPinCpl(Pin) PinCpl(Pin)
#define mPinIs(Pin)  PinIs(Pin)
#define mPinBit(Pin) PinBit(Pin)

#define mPinOn(Pin) PinOn(Pin)
#define mPinOff(Pin) PinOff(Pin)
#define mPinIsAct(Pin)  PinIsAct(Pin)
#define mPinIsNoAct(Pin)  (!PinIsAct(Pin))

#define mPinDDR(Pin) PinDDR(Pin)
#define mPinPIN(Pin) PinPIN(Pin)


#endif






////To always round down to the nearest cycle:
////Code:
//#define _delay_us(__us) __builtin_avr_delay_cycles(F_CPU/1000000.0 * __us)
//
//
//// To round up or down to closest cycle:
////Code:
//#define _delay_us(__us) __builtin_avr_delay_cycles(F_CPU/1000000.0 * __us +0.5)


// To always round up:
//Code:

#define mDelay_us(__us) \
  if((unsigned long) (F_CPU/1000000.0 * __us) != F_CPU/1000000.0 * __us)\
    __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000.0 * __us)+1);\
  else \
    __builtin_avr_delay_cycles((unsigned long) ( F_CPU/1000000.0 * __us))


//unsigned char __builtin_avr_swap(unsigned char);
#define swap(a) __builtin_avr_swap(a)

// u08 swap(u08 data);

//inline u08 swap_(u08 data)
//{
// asm volatile("swap %0"
//     :"=&r"(data)
//     :"0"(data)
//     );
//     return data;
//}

/* Для уменьшения кода и ускорения его работы флаговые переменные
    можно разместить в SFR регистрах с адресами 0x00..0x1F
    Например:
    Если УАПП не используется, то для таких целей можно использовать
    регистр скорости связи (UBRR), а, если не задействовано ЭСППЗУ, то для
    хранения глобальных переменных можно использовать регистр данных (EEDR) и
    регистр адреса ЭСППЗУ (EEAR).
    В данном примере задействованы регистры управления TWI (I2C)
/
//#define gFlagsL OCR1B
//#define gFlagsH OCR1D

#ifndef gFlagsL
u08 gFlagsL;
#endif

#ifndef gFlagsH
u08 gFlagsH;
#endif


/ Макро для сброса флага/
#define mFlgCLRL(nFlg) gFlagsL &= ~(1<<(nFlg%8))
#define mFlgCLRH(nFlg) gFlagsH &= ~(1<<(nFlg%8))

#define mFlgClr(nFlg)\
  do{\
      if (nFlg<8) mFlgCLRL(nFlg);\
      else mFlgCLRH(nFlg);\
    }while(0);

/ Макро для установки флага/
#define mFlgSETL(nFlg) gFlagsL |= (1<<(nFlg%8))
#define mFlgSETH(nFlg) gFlagsH |= (1<<(nFlg%8))

#define mFlgSet(nFlg)\
  do{\
      if (nFlg<8) mFlgSETL(nFlg);\
      else mFlgSETH(nFlg);\
    }while(0);

/ Макро для инверсии (дополнения) флага/
#define mFlgCPLL(nFlg) gFlagsL ^= (1<<(nFlg%8))
#define mFlgCPLH(nFlg) gFlagsH ^= (1<<(nFlg%8))

#define mFlgCpl(nFlg)\
  do{\
      if (nFlg<8) mFlgCPLL(nFlg);\
      else mFlgCPLH(nFlg);\
    }while(0);

/ Макро для проверки флага/
#define mIsFlgL(nFlg) (gFlagsL & (1<<(nFlg%8)))
#define mIsFlgH(nFlg) (gFlagsH & (1<<(nFlg%8)))

/ Переход на метку при установленном флаге/
#define mJmpIfSet(nFlg,Label)\
  do{\
      if (nFlg<8) {if mIsFlgL(nFlg) goto Label;}\
      else {if mIsFlgL(nFlg) goto Label;}\
    }while(0);

/ Переход на метку при сброшеном флаге/
#define mJmpIfClr(nFlg,Label)\
  do{\
      if (nFlg<8) {if (!mIsFlgL(nFlg)) goto Label;}\
      else {if (!mIsFlgL(nFlg)) goto Label;}\
    }while(0);

/ Макро вызова функции при установленном флаге/
#define mCallIfSet(nFlg,aFn)\
  do{\
      if (nFlg<8) {if mIsFlgL(nFlg) aFn();}\
      else {if mIsFlgL(nFlg) aFn();}\
    }while(0);

/ Макро вызова функции при установленном флаге, и его сброс/
#define mCallIfSetC(nFlg,aFn)\
  do{\
      if (nFlg<8) {if mIsFlgL(nFlg) {aFn(); mFlgCLRL(nFlg);}}\
      else {if mIsFlgL(nFlg) {aFn();mFlgCLRH(nFlg);}}\
    }while(0);

#endif

*/

/* Макро для работы с портами */
#define OutPort8(p7,b7,p6,b6,p5,b5,p4,b4,p3,b3,p2,b2,p1,b1,p0,b0,Data)\
  {\
    if(Data&(1<<0)){PinSet(p0,b0);}else{PinClr(p0,b0);};\
    if(Data&(1<<1)){PinSet(p1,b1);}else{PinClr(p1,b1);};\
    if(Data&(1<<2)){PinSet(p2,b2);}else{PinClr(p2,b2);};\
    if(Data&(1<<3)){PinSet(p3,b3);}else{PinClr(p3,b3);};\
    if(Data&(1<<4)){PinSet(p4,b4);}else{PinClr(p4,b4);};\
    if(Data&(1<<5)){PinSet(p5,b5);}else{PinClr(p5,b5);};\
    if(Data&(1<<6)){PinSet(p6,b6);}else{PinClr(p6,b6);};\
    if(Data&(1<<7)){PinSet(p7,b7);}else{PinClr(p7,b7);};\
  }\
  asm volatile("":::"memory")
#define mOutPort8(PORT,Data) OutPort8(PORT,Data)


#define OutPort4(p3,b3,p2,b2,p1,b1,p0,b0,Data)\
  {\
    if(Data&(1<<0)){PinSet(p0,b0);}else{PinClr(p0,b0);};\
    if(Data&(1<<1)){PinSet(p1,b1);}else{PinClr(p1,b1);};\
    if(Data&(1<<2)){PinSet(p2,b2);}else{PinClr(p2,b2);};\
    if(Data&(1<<3)){PinSet(p3,b3);}else{PinClr(p3,b3);};\
  }\
  asm volatile("":::"memory")
#define mOutPort4(PORT,Data) OutPort4(PORT,Data)


#define OutPort3(p2,b2,p1,b1,p0,b0,Data)\
  {\
    if(Data&(1<<0)){PinSet(p0,b0);}else{PinClr(p0,b0);};\
    if(Data&(1<<1)){PinSet(p1,b1);}else{PinClr(p1,b1);};\
    if(Data&(1<<2)){PinSet(p2,b2);}else{PinClr(p2,b2);};\
  }\
  asm volatile("":::"memory")
#define mOutPort3(PORT,Data) OutPort3(PORT,Data)


inline int mROL(int a, int n)
{
  int t1, t2;
  n = n % (sizeof(a) * 8);   // нормализуем n
  t1 = a << n;      // двигаем а вправо на n бит, теряя старшие биты
  t2 = a >> (sizeof(a) * 8 - n); // перегоняем старшие биты в младшие
  return t1 | t2;   // объединяем старшие и младшие биты
}

inline int mROR(int a, int n)
{
  int t1, t2;
  n = n % (sizeof(a) * 8);  // нормализуем n
  t1 = a >> n;      // двигаем а влево на n бит, теряя младшие биты
  t2 = a << (sizeof(a) * 8 - n); // перегоняем младшие биты в старшие
  return t1 | t2;   // объединяем старшие и младшие биты
}



#endif // MACROSA_H_INCLUDED

//S_Alex
