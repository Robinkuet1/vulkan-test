#pragma once
#include "darray.h"

#include <stdlib.h>


//------------8bit--------------
darray8* darray8_create(u64 capacity)
{
	darray8* array = malloc(sizeof(darray8));

	array->data = malloc(sizeof(u8) * capacity);
	array->size = 0;
	array->capacity = capacity;

	return array;
}

void darray8_init(darray8* array, u64 capacity)
{
	array->data = malloc(sizeof(u8) * capacity);
	array->size = 0;
	array->capacity = capacity;
}

void darray8_insert(darray8* array, u8 data)
{
	if (array->capacity == array->size)
	{
		array->capacity += 16;
		array->data = realloc(array->data, array->size * sizeof(u8));
	}
	array->data[array->size++] = data;
}

void darray8_free(darray8* array)
{
	free(array->data);
	array->data = NULL;
	array->capacity = 0;
	array->size = 0;
}



//------------32bit--------------
darray32* darray32_create(u64 capacity)
{
	darray32* array = malloc(sizeof(darray32));

	array->data = malloc(sizeof(i32) * capacity);
	array->size = 0;
	array->capacity = capacity;

	return array;
}

void darray32_init(darray32* array, u64 capacity)
{
	array->data = malloc(sizeof(i32) * capacity);
	array->size = 0;
	array->capacity = capacity;
}

void darray32_insert(darray32* array, i32 data)
{
	if(array->capacity == array->size)
	{
		array->capacity += 16;
		array->data = realloc(array->data, array->size * sizeof(i32));
	}
	array->data[array->size++] = data;
}

void darray32_free(darray32* array)
{
	free(array->data);
	array->data = NULL;
	array->capacity = 0;
	array->size = 0;
}