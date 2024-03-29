#include "bcd.h"

unsigned _bcd2bin(unsigned char val)
{
  return (val & 0x0f) + (val >> 4) * 10;
}

unsigned char _bin2bcd(unsigned char val)
{
  return ((val / 10) << 4) + val % 10;
}
