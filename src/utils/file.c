#include "file.h"

#include <stdio.h>
#include <stdlib.h>

darray8 file_read_binary(const char* filepath)
{
	FILE* file = fopen(filepath, "rb");
	if(!file)
	{
		printf("failed to open file with path: %s", filepath);
		return (darray8){ NULL, 0, 0 };
	}

	fseek(file, 0, SEEK_END);
	const i32 size = ftell(file);
	fseek(file, 0, SEEK_SET);

	u8* buffer = malloc(size * sizeof(u8));
	fread(buffer, sizeof(u8), size, file);

	return (darray8) {buffer, size, size};
}

char* file_read_string(char* filepath)
{

}
