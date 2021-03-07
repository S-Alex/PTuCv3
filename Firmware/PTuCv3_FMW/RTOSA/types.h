//;File: "types.h"

#ifndef TYPES_H
#define TYPES_H 1


// datatype definitions macros
typedef unsigned char  u08;
typedef   signed char  s08;
typedef unsigned short u16;
typedef   signed short s16;
typedef unsigned long  u32;
typedef   signed long  s32;
typedef unsigned long long u64;
typedef   signed long long s64;

#ifndef __INTTYPES_H_
// use inttypes.h instead
// C99 standard integer type definitions
typedef unsigned char uint8_t;
typedef   signed char int8_t;
typedef unsigned short  uint16_t;
typedef   signed short  int16_t;
typedef unsigned long uint32_t;
typedef   signed long int32_t;
typedef unsigned long long uint64_t;
typedef   signed long long int64_t;

#endif //ifndef __INTTYPES_H_

// maximum value that can be held
// by unsigned data types (8,16,32bits)
#define MAX_U08 255
#define MAX_U16 65535
#define MAX_U32 4294967295

// maximum values that can be held
// by signed data types (8,16,32bits)
#define MIN_S08 -128
#define MAX_S08 127
#define MIN_S16 -32768
#define MAX_S16 32767
#define MIN_S32 -2147483648
#define MAX_S32 2147483647

#endif //TYPES_H
