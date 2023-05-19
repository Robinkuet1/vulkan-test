#include <stdio.h>
#include "utils/darray.h"
#include "utils/file.h"

#include "gfx/instance.h"

int main(void)
{
	vulkan_instance_extensions_print();

	vulkan_instance_create((Instance_options){
		{
			"vkTest",
			"vkTest",
			VK_MAKE_VERSION(0,0,1),
			VK_MAKE_VERSION(0,0,1),
			VK_API_VERSION_1_3
		},
		{
			0,
			NULL
		},
		{
			0,
			NULL
		}
	});
	return 0;
}