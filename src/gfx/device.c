#include "device.h"

#include <stdio.h>
#include <stdlib.h>

void vulkan_physical_device_print(Instance* instance)
{
	u32 count;
	PhysicalDevice* devices = 0;
	vulkan_physical_device_get_all(instance, &devices, &count);

	printf("Vulkan compatible devices:\n");
	for (u32 i = 0; i < count; i++)
	{
		printf("\t%d. %s VK:%d.%d.%d Score:%.2f Suitable:%d\n", i + 1,devices[i].properties.deviceName,
		VK_VERSION_MAJOR(devices[i].properties.apiVersion),
		VK_VERSION_MINOR(devices[i].properties.apiVersion),
		VK_VERSION_PATCH(devices[i].properties.apiVersion),
		vulkan_physical_device_score(devices[i]),
		vulkan_physical_device_is_suitable(devices[i]));
	}

	free(devices);
}

void vulkan_physical_device_get_all(Instance* instance, PhysicalDevice** devices, u32* device_count)
{
	*device_count = 0;
	vkEnumeratePhysicalDevices(instance->instance, device_count, NULL);

	VkPhysicalDevice* physicalDevices = malloc(sizeof(VkPhysicalDevice) * *device_count);
	vkEnumeratePhysicalDevices(instance->instance, device_count, physicalDevices);

	*devices = malloc(sizeof(PhysicalDevice) * (*device_count));
	for(u32 i = 0; i < *device_count; i++)
	{
		devices[i]->physicalDevice = physicalDevices[i];
		vkGetPhysicalDeviceProperties(devices[i]->physicalDevice, &devices[i]->properties);
		vkGetPhysicalDeviceFeatures(devices[i]->physicalDevice, &devices[i]->features);
	}

	free(physicalDevices);
}

u8 vulkan_physical_device_is_suitable(PhysicalDevice device)
{
	//todo implement checks for required features
	return
	device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || \
	device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
}

f64 vulkan_physical_device_score(PhysicalDevice device)
{
	//todo more parameters for score evaluation
	f64 score = 1;

	if (device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score *= 2;

	return score;
}
