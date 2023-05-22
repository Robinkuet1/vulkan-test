#pragma once
#include "core/core.h"

//---------8bit--------------
typedef struct
{
	u8* data;
	u64 size;
	u64 capacity;
} darray8;

darray8* darray8_create(u64 capacity);
void darray8_init(darray8* array, u64 capacity);
void darray8_insert(darray8* array, u8 data);
void darray8_free(darray8* array);


//---------32bit--------------
typedef struct
{
	i32* data;
	u64 size;
	u64 capacity;
} darray32;

darray32* darray32_create(u64 capacity);
void darray32_init(darray32* array, u64 capacity);
void darray32_insert(darray32* array, i32 data);
void darray32_free(darray32* array);
