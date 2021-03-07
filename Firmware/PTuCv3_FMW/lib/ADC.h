//File "ADC.h" for use Atmega8
#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED 1
#include <avr/io.h>

//#include <avr/pgmspace.h>

//#define ADC_LIST {0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7}
#define ADC_LIST {0,0},{1,1},{2,2}
/* ** *** Для фильтрации сигнала *** ** */
#define ADC_BUF_SIZE 8
#define ADCFR 0 //;ADC Free Running Select или
#define ADCIE 0 //;ADC Interrupt Enable



//;REFS1 REFS0 Voltage Reference Selection
//; 0 0   AREF, Internal Vref turned off
//; 0 1   AVCC with external capacitor at AREF pin
//; 1 0   Reserved
//; 1 1   Internal 2.56 V Voltage Reference with external capacitor at AREF pin
#define  Aref_AREF 0
#define  Aref_AVCC 1
#define  Aref_256  3
//;-------------------------------------------------------------------------
//;ADPS2 ADPS1 ADPS0 Division Factor
//; 0 0 0   2
//; 0 0 1   2
//; 0 1 0   4
//; 0 1 1   8
//; 1 0 0   16
//; 1 0 1   32
//; 1 1 0   64
//; 1 1 1   128
//;-------------------------------------------------------------------------
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6 //; only TQFP
#define ADC7 7 //; only TQFP

#define VBG 0b1110
#define GND 0b1111
//; ====================================================================

#define log2(q) 7
#define DivADC 128

#define FADC F_CPU/DivADC
#if FADC > 250000
#error "ADC clock frequency higher than 200 kHz"
#endif
#if   FADC < 50000
#error "ADC clock frequency below than 50 kHz"
#endif
//;###############################################################################









//;##########################################################
//;#################### DATA RAM ############################


extern u16 v_ADC[];  //Buffer for ADC data

typedef struct s_ADC_List {
  u08 nCanal;
  u08 Mux;
} ADC_List_t;

typedef struct s_buf {
#if ADC_BUF_SIZE
/* ** *** Для фильтрации сигнала *** ** */
  u08 wr_indx;
  u32 Summa;
  u16 buf[ADC_BUF_SIZE];
#else
  u16 inADC;
#endif // BUFF_SIZE
} buf_t;

extern buf_t Buff_ADC0;
extern buf_t Buff_ADC1;
extern buf_t Buff_ADC2;
extern buf_t Buff_ADC3;
extern buf_t Buff_ADC4;
extern buf_t Buff_ADC5;
extern buf_t Buff_ADC6;
extern buf_t Buff_ADC7;

/* ** *** Для фильтрации сигнала *** ** */

#if ADC_BUF_SIZE
uint16_t CalcMid(buf_t *p_buf, uint16_t data);
#endif // BUFF_SIZE

void fADCInit(void);
void fADC_Exe(void);



#endif // ADC_H_INCLUDED
// S_Alex

