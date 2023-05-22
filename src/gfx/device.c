#include "device.h"

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "globals.h"

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
	(device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || \
	device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) &&
	vulkan_physical_device_find_queue_family(&device, NULL) == OK;
}

f64 vulkan_physical_device_score(PhysicalDevice device)
{
	//todo more parameters for score evaluation
	f64 score = 1;

	if (device.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score *= 2;

	score *= VK_VERSION_MINOR(device.properties.apiVersion) * VK_VERSION_MAJOR(device.properties.apiVersion);
	score *= vulkan_physical_device_is_suitable(device);

	return score;
}

result vulkan_physical_device_find_queue_family(const PhysicalDevice* device, u32* index)
{
	u32 count;
	vkGetPhysicalDeviceQueueFamilyProperties(device->physicalDevice, &count, NULL);

	VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * count);
	vkGetPhysicalDeviceQueueFamilyProperties(device->physicalDevice, &count, queueFamilies);

	for (u32 i = 0; i < count; i++)
	{
		if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			if(index)
				*index = i;
			return OK;
		}
	}
	return NOT_FOUND;
}

result vulkan_physical_device_get_best(Instance* instance, PhysicalDevice* device)
{
	u32 count;
	PhysicalDevice* devices;

	vulkan_physical_device_get_all(instance, &devices, &count);
	if (count == 0)
		return NOT_FOUND;

	f64 max = 0;
	for(u32 i = 0; i < count; i++)
	{
		const f64 score = vulkan_physical_device_score(devices[i]);
		if(max < score)
			max = score;
	}

	for (u32 i = 0; i < count; i++)
	{
		const f64 score = vulkan_physical_device_score(devices[i]);
		if (fabs(max - score) < .01 && score != 0)
			*device = devices[i];
		return OK;
	}

	return UNKNOWN;
}

result vulkan_logical_device_create(const PhysicalDevice* physicalDevice, Device* device)
{
	u32 index;
	if (vulkan_physical_device_find_queue_family(physicalDevice, &index) != OK)
	{
		printf("failed to find queue family\n");
		return NOT_FOUND;
	}

	VkDeviceQueueCreateInfo queueCreateInfo;
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = index;
	queueCreateInfo.queueCount = 1;
	const float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;
	queueCreateInfo.flags = 0;
	queueCreateInfo.pNext = NULL;

	const VkPhysicalDeviceFeatures deviceFeatures = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,
		0,0,0,
		0,0,0,
		0,0,
		0,0,
		0,0,
		0,0,
		0,0,
		0,0,0,0,0,
		0,0,0,0,
		0,0,0,
		0,0,0,
		0,0,0
	};

	VkDeviceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;

	if (enable_validation) {
		createInfo.enabledLayerCount = 1;
		createInfo.ppEnabledLayerNames = &enabled_layers;
	}
	else {
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = NULL;
	}

	device = malloc(sizeof(Device));
	VkDevice tmp;
	if(vkCreateDevice(physicalDevice->physicalDevice, &createInfo, NULL, &tmp) != VK_SUCCESS)
	{
		printf("failed to create device\n");
		return UNKNOWN;
	}
	return OK;
}

void vulkan_logical_device_destroy(Device* device)
{
	vkDestroyDevice(device->device, NULL);
}
