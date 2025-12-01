#pragma once

// Int, float and bool types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;
typedef float f32;
typedef double f64;
typedef int bool32;

#ifndef bool
typedef _Bool bool;
#endif


#define true 1
#define false 0

// Static assertions
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ensure types are of the same size
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte in size");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes in size");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes in size");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes in size");
STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte in size");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes in size");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes in size");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes in size");
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes in size");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes in size");
STATIC_ASSERT(sizeof(bool32) == 4, "Expected bool32 to be 4 bytes in size");
STATIC_ASSERT(sizeof(bool) == 1, "Expected bool to be 1 byte in size");


static i8 directions[4][3] = {
	{-1, 0, '^'},
	{0, 1, '>'},
	{1, 0, 'v'},
	{0, -1, '<'},
};


typedef struct {
	u8 x;
	u8 y;
} Point;
