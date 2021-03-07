

#include "Debug.h"


void krDedug(void)
{
  if (r_CntTask >= (TASKQUEUESIZE)) {
    //xputs(PSTR("\nERROR: Task ovf\n"));

    while (1) {
      asm("nop");
    }
  }

  if (r_CntTimers >= (TIMERSPOOLSIZE)) {
    //xputs(PSTR("\nERROR: Task ovf\n"));


    while (1) {
      asm("nop");
    }
  }

}



void krError(void)
{
  // xputs(PSTR("\nERROR\n"));
}
