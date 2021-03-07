#include  "../main.h"
#include  "ADC.h"

__flash
const ADC_List_t  v_ADC_List[] = {ADC_LIST};
//#define ADC_MAX_CANAL (mItems(v_ADC_List))
#define ADC_MAX_CANAL 3

u16 v_ADC[ADC_MAX_CANAL] = {  //Buffer for ADC data
  0, 0, 0
};

buf_t Buff_ADC0;
buf_t Buff_ADC1;
buf_t Buff_ADC2;
buf_t Buff_ADC3;
buf_t Buff_ADC4;
buf_t Buff_ADC5;
buf_t Buff_ADC6;
buf_t Buff_ADC7;

#if ADC_BUF_SIZE
buf_t *const __flash v_ADC_Bufs[ADC_MAX_CANAL] = {
  &Buff_ADC0,
#if (ADC_MAX_CANAL >= 1)
  &Buff_ADC1,
#endif
#if (ADC_MAX_CANAL >= 2)
  &Buff_ADC2,
#endif
#if (ADC_MAX_CANAL > 3)
  &Buff_ADC3,
#endif
#if (ADC_MAX_CANAL >= 4)
  &Buff_ADC4,
#endif
#if (ADC_MAX_CANAL >= 5)
  &Buff_ADC5,
#endif
#if (ADC_MAX_CANAL >= 6)
  &Buff_ADC6,
#endif
#if (ADC_MAX_CANAL >= 7)
  &Buff_ADC7,
#endif
};
#endif // BUFF_SIZE

///** ############################################################################
// Interrupting routine the ADC change meagering canal
// ADC Conversion Complete
//*/
//ISR(ADC_vect, ISR_NAKED)
//{
//  fADC_Exe();
//  reti();
//}

void fADCInit(void)
{
  DDRC   &= ~0b00000111;   // Порт A на ввод
  PORTC  &= ~0b00000111;  // Подтягивающие резисторы отключить
  ADMUX   = 0
            | (Aref_AREF << REFS0)  /* Опорное напряжение AVcc */
            | (1 << ADLAR)          /* Выравнивание по левому краю */
            | (ADC0);               /* Стартуем с ADC0 */
#ifdef ADATE
  SFIOR  &= ~(1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);  /* Free Running mode */
  SFIOR  |= (1 << ADTS2 | 0 << ADTS1 | 0 << ADTS0);   /* Timer/Counter0 Overflow */
  //  SFIOR |=  (0 << ADTS2 | 1 << ADTS1 | 1 << ADTS0);  /* Timer/Counter0 Compare Match */
  ADCSRA  = (1 << ADEN) | ADCFR << ADATE | ADCIE << ADIE | (log2(DivADC) << ADPS0);
#else
  ADCSRA = (1 << ADEN) | ADCFR << ADFR | ADCIE << ADIE | (log2(DivADC) << ADPS0);
#endif // ADATE
  TIFR   |= (1 << TOV0);
  ADCSRA |= (1 << ADIF); //Clean flag
  ADCSRA |= (1 << ADSC); //ADC Start Conversion
  return;
}

void fADC_Exe(void)
{
  static u08 CurCanal = 0;
  u08 tmpCanal = 0;
  u08 tmpFreeRun = 0;

  if (ADCSRA & (1 << ADIF)) {
    ADCSRA  |= (1 << ADIF);    // Acknowledge the interrupt flag
    TIFR    |= (1 << TOV0);
    /*  */
#if ADCFR
#ifdef ADATE
    //tmpFreeRun = (!(SFIOR & (1 << ADTS2 | 1 << ADTS1 | 1 << ADTS0)));  /* Free Running mode */
    tmpFreeRun = 0;
#else
    tmpFreeRun = 1;
#endif // ADATE
#else
    tmpFreeRun = 0;
#endif // ADCFR
    //tmpFreeRun = 0;
    tmpCanal = (CurCanal - tmpFreeRun);

    if (tmpCanal >= ADC_MAX_CANAL) {
      tmpCanal = 0;
    }

#if ADC_BUF_SIZE
    u16 mid;
    mid = CalcMid(v_ADC_Bufs[tmpCanal], ADC);
    v_ADC[v_ADC_List[tmpCanal].nCanal] = mid;
#else
    v_ADC[v_ADC_List[tmpCanal].nCanal] = ADC;
#endif // BUFF_SIZE
    CurCanal++;

    if (CurCanal >= ADC_MAX_CANAL) {
      CurCanal = 0;
    }

    ADMUX = (ADMUX & ~0b11111) | v_ADC_List[CurCanal].Mux;
        ADCSRA |= (1 << ADSC);      //ADC Start Conversion
  }
}

#if ADC_BUF_SIZE

uint16_t CalcMid(buf_t * p_buf, uint16_t data)
{
  p_buf->Summa -= p_buf->buf[p_buf->wr_indx];
  p_buf->Summa += data;
  p_buf->buf[p_buf->wr_indx] = data;
  p_buf->wr_indx++;

  if (p_buf->wr_indx >= ADC_BUF_SIZE) {
    p_buf->wr_indx = 0;
  }

  return p_buf->Summa / ADC_BUF_SIZE;
}

#endif // BUFF_SIZE
