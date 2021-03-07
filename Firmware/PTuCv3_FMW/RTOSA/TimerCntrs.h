//File TimerCntrs.inc
//Updated: "2011-03-07" "19:41"
//Updated: "2011-03-17" "23:39"
//Updated: "2014-11-15" "23:47"

#ifndef TIMERCNTRS_H
#define TIMERCNTRS_H 1
#ifndef MACROSA_H_INCLUDED
#include "..\MacroSA.h"
#endif

//{ <<<

//{ TC0
#if defined(__AVR_ATtiny261__)
#define TCCR0 TCCR0B
#endif

#if defined(__AVR_ATmega8__)\
||defined(__AVR_ATmega32__)\
    ||defined(__AVR_ATmega16__)\
||defined(__AVR_ATtiny261__)
//CS02 CS01 CS00         //Description
#define T0_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T0Div1     0b001 //clkI/O/1 (No prescaling)
#define T0Div8     0b010 //clkI/O/8 (From prescaler)
#define T0Div64    0b011 //clkI/O/64 (From prescaler)
#define T0Div256   0b100 //clkI/O/256 (From prescaler)
#define T0Div1024  0b101 //clkI/O/1024 (From prescaler)
#define T0ExtFall  0b110 //External clock source on T0 pin. Clock on falling edge.
#define T0ExtRis   0b111 //External clock source on T0 pin. Clock on rising edge.
#elif defined (__AVR_ATmega103__)|defined (__AVR_ATmega64__)
//CS02 CS01 CS00         //Description
#define T0_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T0Div1     0b001 //clkI/O/1 (No prescaling)
#define T0Div8     0b010 //clkI/O/8 (From prescaler)
#define T0Div32    0b011 //clkI/O/32 (From prescaler)
#define T0Div64    0b100 //clkI/O/64 (From prescaler)
#define T0Div128   0b101 //clkI/O/128 (From prescaler)
#define T0Div256   0b110 //clkI/O/256 (From prescaler)
#define T0Div1024  0b111 //clkI/O/1024 (From prescaler)
//-----------------------------------------------------+
//Compare Output Mode, Non-PWM Mode                    |
//COM01|COM00| Description                             |
//  0  |  0  | Normal port operation, OC2 disconnected.|
//  0  |  1  | Toggle OC2 on compare match             |
//  1  |  0  | Clear OC2 on compare match              |
//  1  |  1  | Set OC2 on compare match                |
//-----------------------------------------------------+
#define  COMTC0NORMAL  (0<<COM01)|(0<<COM00) //         |
#define  COMTC0Toggle  (0<<COM01)|(1<<COM00) //         |
#define  COMTC0Clear   (1<<COM01)|(0<<COM00) //         |
#define  COMTC0Set     (1<<COM01)|(1<<COM00) //         |
//-----------------------------------------------------+
#endif

//} TC0


//{ TC1
//{ 16-bit Timer/Counter (Timer/Counterl and Timer/Counter3)
#if defined(__AVR_ATmega8__) \
||defined(__AVR_ATmega64__)  \
||(__AVR_ARCH__==5)
//Тактируется от задающего генератора TCK или от внешнего входа T1
//через делитель коэффициент деления 1,8,64,256,1024.
//Регистр управления таймером/счетчиком0.
//TCCR1A-(The Timer/Counter1 Control Register)
//CS12 CS11 CS10 Description
#define T1_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T1Div1     0b001 //clkI/O/1 (No prescaling)
#define T1Div8     0b010 //clkI/O/8 (From prescaler)
#define T1Div64    0b011 //clkI/O/64 (From prescaler)
#define T1Div256   0b100 //clkI/O/256 (From prescaler)
#define T1Div1024  0b101 //clkI/O/1024 (From prescaler)
#define T1ExtFall  0b110 //External clock source on T1 pin. Clock on falling edge.
#define T1ExtRis   0b111 //External clock source on T1 pin. Clock on rising edge.


//----+-----+-----+-----+-----+---------------------------+------+---------+---------+
//Mode|WGMn3|WGMn2|WGMnl|WGMnO|Timer/Counter Mode of      |TOP   |Update of|TOVn Flag|
//    |     |CTCn |PWMnl|PWMn0|        Operation          |      |OCRnx at | Set on  |
//----+-----+-----+-----+-----+---------------------------+------+---------+---------+
//  0 |  0  |  0  |  0  |  0  |Normal                     |OxFFFF|Immediate|MAX      |
//  1 |  0  |  0  |  0  |  1  |PWM, Phase Correct, 8-bit  |OxOOFF|TOP      |BOTTOM   |
//  2 |  0  |  0  |  1  |  0  |PWM, Phase Correct, 9-bit  |0x01FF|TOP      |BOTTOM   |
//  3 |  0  |  0  |  1  |  1  |PWM, Phase Correct, 10-bit |0x03FF|TOP      |BOTTOM   |
//  4 |  0  |  1  |  0  |  0  |CTC                        |OCRnA |Immediate|MAX      |
//  5 |  0  |  1  |  0  |  1  |Fast PWM, 8-bit            |OxOOFF|TOP      |TOP      |
//  6 |  0  |  1  |  1  |  0  |Fast PWM, 9-bit            |0x01FF|TOP      |TOP      |
//  7 |  0  |  1  |  1  |  1  |Fast PWM, 10-bit           |0x03FF|TOP      |TOP      |
//  8 |  1  |  0  |  0  |  0  |PWM, Phase and Freq Correct|ICRn  |BOTTOM   |BOTTOM   |
//  9 |  1  |  0  |  0  |  1  |PWM, Phase and Freq Correct|OCRnA |BOTTOM   |BOTTOM   |
//  10|  1  |  0  |  1  |  0  |PWM, Phase Correct         |ICRn  |TOP      |BOTTOM   |
//  11|  1  |  0  |  1  |  1  |PWM, Phase Correct         |OCRnA |TOP      |BOTTOM   |
//  12|  1  |  1  |  0  |  0  |CTC                        |ICRn  |Immediate|MAX      |
//  13|  1  |  1  |  0  |  1  |(Reserved)                 |-     |  -      |-        |
//  14|  1  |  1  |  1  |  0  |Fast PWM                   |ICRn  |TOP      |TOP      |
//  15|  1  |  1  |  1  |  1  |Fast PWM                   |OCRnA |TOP      |TOP      |
//----+-----+-----+-----+-----+---------------------------+------+---------+---------+
#define  PWM1A_DISCON  ((0<<COM1A1)|(0<<COM1A0))
#define  PWM1A_TOGGLE  ((0<<COM1A1)|(1<<COM1A0))
#define  PWM1A_NOINV   ((1<<COM1A1)|(0<<COM1A0))
#define  PWM1A_INV     ((1<<COM1A1)|(1<<COM1A0))

#define  PWM1B_DISCON  ((0<<COM1B1)|(0<<COM1B0))
#define  PWM1B_TOGGLE  ((0<<COM1B1)|(1<<COM1B0))
#define  PWM1B_NOINV   ((1<<COM1B1)|(0<<COM1B0))
#define  PWM1B_INV     ((1<<COM1B1)|(1<<COM1B0))

#if defined(__AVR_ATmega64__)

#define T3_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T3Div1     0b001 //clkI/O/1 (No prescaling)
#define T3Div8     0b010 //clkI/O/8 (From prescaler)
#define T3Div64    0b011 //clkI/O/64 (From prescaler)
#define T3Div256   0b100 //clkI/O/256 (From prescaler)
#define T3Div1024  0b101 //clkI/O/1024 (From prescaler)
#define T3ExtFall  0b110 //External clock source on T1 pin. Clock on falling edge.
#define T3ExtRis   0b111 //External clock source on T1 pin. Clock on rising edge.

#define  PWM1C_DISCON  (0<<COM1C1)|(0<<COM1C0)
#define  PWM1C_TOGGLE  (0<<COM1C1)|(1<<COM1C0)
#define  PWM1C_NOINV   (1<<COM1C1)|(0<<COM1C0)
#define  PWM1C_INV     (1<<COM1C1)|(1<<COM1C0)

#endif //__AVR_ATmega64__

#else
#error "Контроллер не поддерживается"
#endif //__AVR_ATmega64__


//} 16-bit Timer/Counter (Timer/Counterl and Timer/Counter3)
//} TC1



//{ TC2
#if defined(__AVR_ATmega8__)\
||defined(__AVR_ATmega32__)\
    ||defined(__AVR_ATmega16__)

//#message "--------------------------------------------Timers for ATmega8:--------------------------------------------"
//CS22 CS21 CS20         //Description
#define T2_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T2Div1     0b001 //clkI/O/1 (No prescaling)
#define T2Div8     0b010 //clkI/O/8 (From prescaler)
#define T2Div32    0b011 //clkI/O/32 (From prescaler)
#define T2Div64    0b100 //clkI/O/64 (From prescaler)
#define T2Div128   0b101 //clkI/O/128 (From prescaler)
#define T2Div256   0b110 //clkI/O/256 (From prescaler)
#define T2Div1024  0b111 //clkI/O/1024 (From prescaler)
#elif defined (__AVR_ATmega103__)|defined (__AVR_ATmega64__)
//CS22 CS21 CS20         //Description
#define T2_OFF     0b000 //No clock source. (Timer/counter stopped)
#define T2Div1     0b001 //clkI/O/1 (No prescaling)
#define T2Div8     0b010 //clkI/O/8 (From prescaler)
#define T2Div64    0b011 //clkI/O/64 (From prescaler)
#define T2Div256   0b100 //clkI/O/256 (From prescaler)
#define T2Div1024  0b101 //clkI/O/1024 (From prescaler)
#define T2ExtFall  0b110 //External clock source on T0 pin. Clock on falling edge.
#define T2ExtRis   0b111 //External clock source on T0 pin. Clock on rising edge.
//-----------------------------------------------------+
//Compare Output Mode, Non-PWM Mode                    |
//COM21|COM20| Description                             |
//  0  |  0  | Normal port operation, OC2 disconnected.|
//  0  |  1  | Toggle OC2 on compare match             |
//  1  |  0  | Clear OC2 on compare match              |
//  1  |  1  | Set OC2 on compare match                |
//-----------------------------------------------------+
#define  COMTC2NORMAL  (0<<COM21)|(0<<COM20) //         |
#define  COMTC2Toggle  (0<<COM21)|(1<<COM20) //         |
#define  COMTC2Clear   (1<<COM21)|(0<<COM20) //         |
#define  COMTC2Set     (1<<COM21)|(1<<COM20) //         |
//-----------------------------------------------------+

#endif

//} TC2




//.macro mInitTC8bit  //TIMER,FREQUENCY //mInitTC8bit 0,100
/*     {
 *       #if defined(__AVR_ATmega8__)
 *         .set  F_Ovf = @1//100
 *       #elif defined(__AVR_ATmega64__)
 *         .set  F_Ovf = @1*2//100
 *       #endif
 *       .set  F_Ovf = @1*2//100
 *       .set  N_Cnt   = 8
 *       .set  FnMin   = 1
 *       .set  FnMax   = (1<<N_Cnt) - 1
 *
 *       .set  PreDivMin = Fclk / ( F_Ovf * FnMax)
 *       .set  PreDivMax = Fclk / ( F_Ovf * FnMin)
 *
 *     #if defined(__AVR_ATmega8__)||defined(__AVR_ATmega64__)
 *       .message  " +--------------+"
 *       .if @0==0
 *        .message " |PreDiv for TC0|"
 *       .elif @0==2
 *        .message " |PreDiv for TC2|"
 *       .endif
 *       .if PreDivMin < 1
 *         .message " |   Div1       |"
 *         .set PreDiv = 1
 *         .set DivMask = T@0Div1
 *       .elif (PreDivMin<8)&&defined(T@0Div8)
 *         .message " |   Div8       |"
 *         .set PreDiv = 8
 *         .set DivMask = T@0Div8
 *       .elif (PreDivMin<32)&&defined(T@0Div32)
 *         .message " |   Div32      |"
 *         .set PreDiv = 32
 *         .set DivMask = T@0Div32
 *       .elif (PreDivMin<64)&&defined(T@0Div64)
 *         .message " |   Div64      |"
 *         .set PreDiv = 64
 *         .set DivMask = T@0Div64
 *       .elif (PreDivMin<128)&&defined(T@0Div128)
 *         .message " |   Div128     |"
 *         .set PreDiv = 128
 *         .set DivMask = T@0Div128
 *       .elif (PreDivMin<256)&&defined(T@0Div256)
 *         .message " |   Div256     |"
 *         .set PreDiv = 256
 *         .set DivMask = T@0Div256
 *       .elif (PreDivMin<1024)&& defined(T@0Div8)
 *         .message " |   Div1024    |"
 *         .set PreDiv = 1024
 *         .set DivMask = T@0Div1024
 *       .else
 *         .error "Timer not config"
 *       .endif
 *       .message  "+--------------+"
 *
 *
 *       .set  Fn  = Fclk/(PreDiv * F_Ovf)
 *       #if defined(__AVR_ATmega8__)
 *         in    AL,     TIMSK
 *         ori   AL,     (1<<TOIE0)//Bit 0 - TOIE0: Timer/Counter0 Overflow Interrupt Enable
 *         out   TIMSK,  AL
 *
 *       //{ Interrupt
 *         .set  OldPC = pc
 *         .org  OVF0addr  //Overflow0 Interrupt Vector Address
 *           rjmp TIM0_OVF //Timer0 Overflow Handler
 *         .org  OldPC
 *
 *         TIM0_OVF: //Timer0 Overflow Handler
 *         in    TmpSREG,  SREG
 *         push  AL
 *         //Place your code here
 *         ldi   AL, (1<<N_Cnt)-Fn
 *         out   TCNT0,  AL
 *         //
 *         pop   AL
 *         out   SREG,   TmpSREG
 *         reti
 *       //} Interrupt
 *
 *       #elif defined(__AVR_ATmega64__)
 *         .if @0==0
 *           ldi   AL,     DivMask|(1<<WGM01)|(0<<WGM00)|COMTC0Toggle
 *           out   TCCR0,  AL
 *           ldi   AL,     Fn
 *           out   OCR0,   AL
 *         .elif @0==2
 *           ldi   AL,     DivMask|(1<<WGM21)|(0<<WGM20)|COMTC2Toggle
 *           out   TCCR2,  AL
 *           ldi   AL,     Fn
 *           out   OCR2,   AL
 *         .endif
 *       #endif
 *     #else
 *       #error "Sorry. Chip not support"
 *     #endif
 *
 *
 *
 *     }
 */


//F_Ovf = Fclk / (PreDiv * (2^n - Fn))
//PreDiv  = Fclk / ( F_Ovf * (2^n - Fn))
#define bit0 0
#define bit1 1
#define bit2 2
#define bit3 3
#define bit4 4
#define bit5 5
#define bit6 6
#define bit7 7

//{ Определение выводов PWM
#if defined(__AVR_ATmega8__)
#define  PWM_1A   PORTB,1,1
#define  PWM_1B   PORTB,2,1
#define  PWM_2    PORTB,3,1
#elif defined(__AVR_ATmega32__)\
    ||defined(__AVR_ATmega16__)
#define  PWM_1A   PORTD,5,1
#define  PWM_1B   PORTD,4,1
#elif defined(__AVR_ATmega64__)
#define  PWM_1A   PORTB,5,1
#define  PWM_1B   PORTB,6,1
#elif defined(__AVR_ATtiny261__)
#define  PWM_1A   PORTB,1,1
#define  PWM_1B   PORTB,3,1
#else
#error "Контроллер не поддерживается"

#endif
//} Определение выводов PWM

//###############################################################################
//опредение переменных для работы с таймерами/счетчиками.
//###############################################################################
//Table 42. Waveform Generation Mode Bit Description
//---------------------------------------------------------------------|
//Mode | WGM21 | WGM20 | Timer/Counter      | TOP |  Update  | TOV2    |
//     | (CTC2)| (PWM2)| Mode of Operation  |     | of OCR2  | Flag Set|
//---------------------------------------------------------------------|
// 0   |   0   |   0   | Normal             |0xFF |Immediate | MAX     |
// 1   |   0   |   1   | PWM, Phase Correct |0xFF |   TOP    | BOTTOM  |
// 2   |   1   |   0   | CTC                |OCR2 |Immediate | MAX     |
// 3   |   1   |   1   | Fast PWM           |0xFF |   TOP    | MAX     |
//---------------------------------------------------------------------|
//Note: 1. The CTC2 and PWM2 bit definition names are now obsolete.
//Use the WGM21:0 definitions.
//However, the functionality and location of these bits are compatible with
//previous versions of the timer.
//###############################################################################

//###############################################################################
//Bit        |  7 |   6  |   5  |   4  |   3  |   2 |   1 |  0  |
//TCCR2      |FOC2| WGM20| COM21| COM20| WGM21| CS22| CS21| CS20| //OLD
//TCCR2      |FOC2| PWM2 | COM21| COM20| CTC2 | CS22| CS21| CS20|
//Read/Write |  W | R/W  | R/W  | R/W  | R/W  | R/W | R/W | R/W |
//Init Value |  0 |   0  |   0  |   0  |   0  |   0 |   0 |  0  |
//###############################################################################

//      #define T2Div1     0b001 //clkI/O/1 (No prescaling)




//###############################################################################
//For  ATmega8 & ATmega103 & ATmega64

//опредение переменных для работы с таймерами/счетчиками.

//Таймер/счетчик0  8 разрядный.
//Тактируется от задающего генератора TCK, или TOSC1 RTC,
//через делитель коэффициент деления 1,8,32,64,128,256,1024.
//Регистр управления таймером/счетчиком0.
//TCCR0-(The Timer/Counter0 Control Register)
#if defined(__AVR_ATmega8__)
//code specific for these devices
//#message "--------------------------------------------Timers for ATmega8:--------------------------------------------"
#define PWM_2  PORTB,3,1
#define CTC2 WGM21
#define PWM2 WGM20

#define  PWM_PhC   (0<<CTC2)|(1<<PWM2)//PWM, Phase Correct
#define  PWM_Fast  (1<<CTC2)|(1<<PWM2)//Fast PWM
#define  PWM_NoInv (1<<COM21)|(0<<COM20)
#define  PWM_Inv   (1<<COM21)|(1<<COM20)

;
inline void mPWM2Init(void)
{
  TCCR2 = T2Div1 | PWM_Fast | PWM_NoInv;
  mPinOut(PWM_2);
  mPinSet(PWM_2);
};

inline void mPWM2Stop(void)
{
  TCCR2 = T2_OFF;
  mPinIn(PWM_2);
  mPinSet(PWM_2);
};



#endif

//mInit_TC0  T0Div8, 1 установить предделитель на 8 и разрешить прерывания от таймера
#define  mInit_TC0(Div,fInt) \
  {\
    TCCR0 = Div;\
    TCNT0 =0;\
    if (fInt) TIMSK |=fInt;\
  };
//###############################################################################
//###############################################################################

//###############################################################################

#if defined(__AVR_ATmega8__)
/*     .macro  mInit_TC2
 *       ldi   R16,  @0
 *       out   TCCR2,  R16
 *
 *       in    R16,  TIMSK
 *       andi  R16,  ~(1<<TOIE2)
 *       out   TIMSK,  R16
 *
 *     .endmacro
 */

#elif defined (__AVR_ATmega103__)
//Таймер/счетчик2  8 разрядный.
//Тактируется от задающего генератора TCK через делитель.
//коэффициент деления 1,8,64,256,1024.Или от входа PD7(T2).
//Регистр управления таймером/счетчиком2.
//TCCR2-(The Timer/Counter2 Control Register)

//=======================================================
//Bit6-PWM0,PWM2: Pulse Width Modulator Enable.
// Разрешение ШИМ.
#define PWM_ON   0b01000000
#define PWM_OFF  0b00000000
//-------------------------------------------------------
//Bits5,4-COM01,COM00/COM21,COM20: Compare Output Mode.
//Режим работы вывода PB4(OC0/PWM0)
//       = 0b76543210
#define OC_OFF   0b00000000//отключение вывода PB4(OC0/PWM0)
// -//-    PB7(OC2/PWM2).
#define OC_Toggle  0b00010000//перключение вывода PB4(OC0/PWM0)
// -//-    PB7(OC2/PWM2).
#define OC_Clear 0b00100000//Очистка вывода PB4(OC0/PWM0)
// -//-    PB7(OC2/PWM2).
#define OC_Set   0b00110000//Установка вывода PB4(OC0/PWM0)
// -//-    PB7(OC2/PWM2).
//-------------------------------------------------------
//Bit3-CTC0/CTC2: Clear Timer/Counter on Compare match
//Очистить Таймер/счетчик0,2 при совпадении значения
//таймера/счетчика [регистр TCNT0,2-(Timer/Counter0,2)]
//с содержимым регистра OCR0,2-(Timer/Counter0,2 Output Compare Register)
//       = 0b76543210
#define Comp_ON  0b00001000
#define Comp_OFF 0b00000000
//-------------------------------------------------------

//=======================================================
#define ASync 0x08
#define Sync  0x00

/*     .macro Init_TC0//
 *       ldi   R16,@1
 *       out   ASSR0,R16
 *       ldi   R16,@0
 *       out   TCCR0,R16
 *       LAsync1:
 *       in    R16,ASSR0
 *       andi  R16,$07
 *       brne  LAsync1
 *     .endm
 */

#define mInit_TC2(v1) TCCR2 = v1
#endif
//###############################################################################
//###############################################################################











//###############################################################################


#define mInit_TC1(v1) TCCR1B = v1


static
inline
void mT1SetMode(const u08 Mode, const  u16 PreDiv, const u08 PWM1Type)
{
#if defined(__AVR_ATmega8__)
  /*  TCCR1A
   *    7   |    6   |    5   |    4   |   3   |   2   |   1   |   0   |
   * COM1A1 | COM1A0 | COM1B1 | COM1B0 | FOC1A | FOC1B | WGM11 | WGM10 |
   */
  /* TCCR1B
   *   7   |   6   | 5 |   4   |   3   |  2   |  1   |   0  |
   * ICNC1 | ICES1 | – | WGM13 | WGM12 | CS12 | CS11 | CS10 |
   */
  //----+-----+-----+-----+-----+---------------------------+------+---------+---------+
  //Mode|WGM13|WGM12|WGM11|WGM10|Timer/Counter Mode of      |TOP   |Update of|TOVn Flag|
  //    |     |CTC1 |PWM1l|PWM10|        Operation          |      |OCRnx at | Set on  |
  //----+-----+-----+-----+-----+---------------------------+------+---------+---------+
  //  4 |  0  |  1  |  0  |  0  |CTC                        |OCRnA |Immediate|MAX      |
  u08 AL, AH;
  AL = TCCR1A;
  AL &= ~((1 << WGM11) | (1 << WGM10));
  AL |= (Mode & 0b0011) | PWM1Type;
  AH = TCCR1B;
  AH &= ~((1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS11) | (1 << CS10));
  AH |= ((Mode & 0b1100) << 1) | PreDiv;
  TCCR1A = AL;
  TCCR1B = AH;
  //#if defined(__AVR_ATmega8__)
#elif   defined(__AVR_ATmega64__)\
      ||defined(__AVR_ATmega32__)\
      ||defined(__AVR_ATmega16__)
  u08 AL, AH;
  AL = TCCR1A;
  AL &= ~((1 << WGM11) | (1 << WGM10));
  AL |= (Mode & 0b0011) | PWM1Type;
  AH = TCCR1B;

  if (PreDiv > 7) {
    // Ignore PREDIV
    AH &= ~((1 << WGM13) | (1 << WGM12));
    AH |= (((Mode & 0b1100) >> 1) << WGM12);
  }  else {
    AH &= ~((1 << WGM13) | (1 << WGM12) | (1 << CS12) | (1 << CS11) | (1 << CS10));
    AH |= ((Mode & 0b1100) << 1) | PreDiv;
  }

  TCCR1A = AL;
  TCCR1B = AH;
  //#elif defined(__AVR_ATmega64__)
#else
#error "Контроллер не поддерживается"
#endif
}


inline u16 mGetT0_Div(const u64 F_Tim, const u64 n_Cnt, const u08 flgTCCR)
{
  //#define  n_Cnt 8
  u08 Val_TCCR = 0;
  u16 PreDiv = 0;
  u16 PreDivMin = (F_CPU / F_Tim) >> n_Cnt;
#if defined(__AVR_ATmega8__)\
  ||defined(__AVR_ATmega32__)\
  ||defined(__AVR_ATmega64__)\
  ||defined(__AVR_ATmega16__)\
  ||defined(__AVR_ATtiny261__)

  //#if(__AVR_ARCH__==5)
  if (PreDivMin < 1) {
    PreDiv = 1;
    Val_TCCR = T0Div1;
  } else if (PreDivMin < 8) {
    PreDiv = 8;
    Val_TCCR = T0Div8;
  } else if (PreDivMin < 64) {
    PreDiv = 64;
    Val_TCCR = T0Div64;
  } else if (PreDivMin < 256) {
    PreDiv = 256;
    Val_TCCR = T0Div256;
  } else if (PreDivMin < 1024) {
    PreDiv = 1024;
    Val_TCCR = T0Div1024;
  }

#else
#error "Контроллер не поддерживается"
#endif // defined

  if (flgTCCR) {
    return Val_TCCR & 0b111;
  } else {
    return PreDiv;
  }
}
inline u16 mGetT1_Div(const u64 F_Tim, const u64 n_Cnt, const u08 flgTCCR)
{
  //#define  n_Cnt 8
  u08 Val_TCCR = 0;
  u16 PreDiv = 0;
  u16 PreDivMin = 7;
  PreDivMin = (F_CPU / F_Tim) >> n_Cnt;
#if defined(__AVR_ATmega8__)\
  ||defined(__AVR_ATmega32__)\
  ||defined(__AVR_ATmega64__)\
  ||defined(__AVR_ATmega16__)\
  ||defined(__AVR_ATtiny261__)

  //#if(__AVR_ARCH__==5)
  if (PreDivMin < 1) {
    PreDiv = 1;
    Val_TCCR = T1Div1;
  } else if (PreDivMin < 8) {
    PreDiv = 8;
    Val_TCCR = T1Div8;
  } else if (PreDivMin < 64) {
    PreDiv = 64;
    Val_TCCR = T1Div64;
  } else if (PreDivMin < 256) {
    PreDiv = 256;
    Val_TCCR = T1Div256;
  } else if (PreDivMin < 1024) {
    PreDiv = 1024;
    Val_TCCR = T1Div1024;
  }

#else
#error "Контроллер не поддерживается"
#endif // defined

  if (flgTCCR) {
    return Val_TCCR & 0b111;
  } else {
    return PreDiv;
  }
}

inline u16 mGetT2_Div(const u64 F_Tim, const u64 n_Cnt, const u08 flgTCCR)
{
  //#define  n_Cnt 8
  u08 Val_TCCR = 0;
  u16 PreDiv = 0;
  u16 PreDivMin = F_CPU / (F_Tim * (1 << n_Cnt));
#if defined(__AVR_ATmega8__)\
  ||defined(__AVR_ATmega32__)\
  ||defined(__AVR_ATmega64__)\
  ||defined(__AVR_ATmega16__)\
  ||defined(__AVR_ATtiny261__)

  //#if(__AVR_ARCH__==5)
  if (PreDivMin < 1) {
    PreDiv = 1;
    Val_TCCR = T2Div1;
  } else if (PreDivMin < 8) {
    PreDiv = 8;
    Val_TCCR = T2Div8;
  } else if (PreDivMin < 32) {
    PreDiv = 32;
    Val_TCCR = T2Div32;
  } else if (PreDivMin < 64) {
    PreDiv = 64;
    Val_TCCR = T2Div64;
  } else if (PreDivMin < 64) {
    PreDiv = 64;
    Val_TCCR = T2Div64;
  } else if (PreDivMin < 128) {
    PreDiv = 128;
    Val_TCCR = T2Div128;
  } else if (PreDivMin < 256) {
    PreDiv = 256;
    Val_TCCR = T2Div256;
  } else if (PreDivMin < 1024) {
    PreDiv = 1024;
    Val_TCCR = T2Div1024;
  }

#else
#error "Контроллер не поддерживается"
#endif // defined

  if (flgTCCR) {
    return Val_TCCR & 0b111;
  } else {
    return PreDiv;
  }
}

/*   .macro mT3SetMode //MODE,PREDIV,PWM1TYPE
 *
 *     mIn   AL,     TCCR3A
 *     cbr   AL,     0xff//(1<<WGM11)|(1<<WGM10)
 *     ori   AL,     (@0&0b0011)|@2
 *
 *     mIn   AH,     TCCR3B
 *     .if @1>7
 *       // Ignore PREDIV
 *       cbr   AH,     (1<<WGM33)|(1<<WGM32)
 *       ori AH,     ((@0&0b1100)<<1)
 *     .else
 *       cbr   AH,     (1<<WGM33)|(1<<WGM32)|(1<<CS32)|(1<<CS31)|(1<<CS30)
 *       ori   AH,     ((@0&0b1100)<<1)|@1|(1<<ICNC3)|(1<<ICES3)
 *     .endif
 *
 *     mOut  TCCR3A, AL
 *     mOut  TCCR3B, AH
 *
 *   .endmacro
 */
//} >>>
#endif // TIMERCNTRS_H
//S_Alex
