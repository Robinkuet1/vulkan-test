#include <stdio.h>
#include "utils/darray.h"
#include "utils/file.h"

#include "gfx/instance.h"
#include "gfx/globals.h"
#include "gfx/device.h"

int main(void)
{
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
		0
	});

	vulkan_physical_device_print(&instance);

	PhysicalDevice physicalDevice;
	vulkan_physical_device_get_best(&instance, &physicalDevice);

	Device device;
	vulkan_logical_device_create(&physicalDevice, &device);

	return 0;
}