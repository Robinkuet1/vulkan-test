#include "window.h"

#include <stdio.h>

static void glfwErrorCallback(i32 code, const char* msg)
{
	printf("%s", msg);
}

void core_window_create(window_options options, Window* window)
{
	if(!glfwInit())
	{
		printf("failed to initialize glfw\n");
		return;
	}

	glfwSetErrorCallback(glfwErrorCallback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window->window = glfwCreateWindow(options.initialWidth, options.initialHeight, options.name, NULL, NULL);
}

void core_window_destroy(Window* window)
{
	if(window->instance.surface)
	{
		vkDestroySurfaceKHR(window->instance.instance, window->instance.surface, NULL);
	}

	glfwDestroyWindow(window->window);
	glfwTerminate();
}

void core_window_get_surface(Window* window)
{
	if(glfwCreateWindowSurface(window->instance.instance, window->window, NULL, &window->instance.surface) != VK_SUCCESS)
	{
		printf("failed to create window surface!\n");
	}	
}
