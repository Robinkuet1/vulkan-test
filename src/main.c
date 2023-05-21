#include <stdio.h>
#include "utils/darray.h"
#include "utils/file.h"

#include "gfx/instance.h"
#include "gfx/device.h"

int main(void)
{
	char const* enabled_extensions = "VK_EXT_debug_utils";
	char const* enabled_layers = "VK_LAYER_KHRONOS_validation";

	Instance instance;
	vulkan_instance_create(&instance, (Instance_options){
		{
			"vkTest",
			"vkTest",
			VK_MAKE_VERSION(0,0,1),
			VK_MAKE_VERSION(0,0,1),
			VK_API_VERSION_1_2
		},
		{
			1,
			&enabled_extensions
		},
		{
			1,
			&enabled_layers
		},
		0,
		1
	});

	vulkan_physical_device_print(&instance);

	return 0;
}