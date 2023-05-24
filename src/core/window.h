#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "core.h"
#include "types.h"
#include "gfx/instance.h"

typedef struct
{
	GLFWwindow* window;
	i32 width;
	i32 height;
	Instance instance;
} Window;

typedef struct
{
	char* name;
	i32 initialWidth;
	i32 initialHeight;
} window_options;

void core_window_create(in window_options options, out Window* window);

void core_window_destroy(in Window* window);

void core_window_get_surface(inout Instance* instance);