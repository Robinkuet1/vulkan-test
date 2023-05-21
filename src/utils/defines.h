#pragma once
#include <stdint.h>

#pragma warning(disable:6385) //reading invalid data
#pragma warning(disable:6011) //dereferencing NULL pointer


typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

/**
 * \brief data will only be read and not changed by the function
 */
#define in __in

/**
 * \brief data will be read and changed by the function
 */
#define inout __inout

/**
 * \brief data will be created and returned by the function
 */
#define out __out