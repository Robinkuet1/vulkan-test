#pragma once
#include <GLFW/glfw3.h>

#include "types.h"
#include "window.h"


typedef struct
{
	u8 keys[GLFW_KEY_LAST];
} Input;

void input_initialize(Window* window);