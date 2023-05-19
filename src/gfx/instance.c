#include "instance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Instance vulkan_instance_create(Instance_options options)
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = options.application_options.applicationName;
	appInfo.applicationVersion = options.application_options.applicationVersion;
	appInfo.pEngineName = options.application_options.engineName;
	appInfo.engineVersion = options.application_options.engineVersion;
	appInfo.apiVersion = options.application_options.vulkanVersion;
	appInfo.pNext = NULL;

	VkInstanceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = options.extension_options.extensionCount;
	createInfo.ppEnabledExtensionNames = options.extension_options.extensionNames;
	createInfo.enabledLayerCount = options.layer_options.layerCount;
	createInfo.ppEnabledLayerNames = options.layer_options.layerNames;
	createInfo.flags = options.flags;
	createInfo.pNext = NULL;

	VkInstance instance;
	const VkResult result = vkCreateInstance(&createInfo, NULL, &instance);
	if (result != VK_SUCCESS)
	{
		printf("failed to initialize vulkan with code %d", result);
		exit(1);
	}
}

void vulkan_instance_destroy(Instance* instance)
{
	vkDestroyInstance(instance->instance, NULL);
}

void vulkan_instance_extensions_print(void)
{
	//get all extensions and store in array
	u32 extension_count = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
	VkExtensionProperties* extensions = malloc(sizeof(VkExtensionProperties) * extension_count);
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, extensions);

	//print all extensions
	printf("available extensions:\n");
	for (u32 i = 0; i < extension_count; i++)
	{
		printf("\t %s\n", extensions[i].extensionName);
	}
	printf("\n");
}

void vulkan_instance_layers_print(void)
{
	//get all layers and store in array
	u32 layer_count = 0;
	vkEnumerateInstanceLayerProperties(&layer_count, NULL);
	VkLayerProperties* layers = malloc(sizeof(VkLayerProperties) * layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, layers);

	//print all layers
	printf("available layers:\n");
	for (u32 i = 0; i < layer_count; i++)
	{
		printf("\t %s\n", layers[i].layerName);
	}
	printf("\n");
}

u8 vulkan_instance_extensions_supported(const char* extensionName)
{
	//get all extensions and store in array
	u32 extension_count = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);
	VkExtensionProperties* extensions = malloc(sizeof(VkExtensionProperties) * extension_count);
	vkEnumerateInstanceExtensionProperties(NULL, &extension_count, extensions);

	//enumerator over all extensions
	for(u32 i = 0; i < extension_count; i++)
	{
		if(strcmp(extensions[i].extensionName, extensionName) == 0)
		{
			//found
			return 1;
		}
	}
	//not found
	return 0;
}

u8 vulkan_instance_layer_supported(const char* layerName)
{
	//get all layers and store in array
	u32 layer_count = 0;
	vkEnumerateInstanceLayerProperties(&layer_count, NULL);
	VkLayerProperties* layers = malloc(sizeof(VkLayerProperties) * layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, layers);

	//enumerator over all layers
	for (u32 i = 0; i < layer_count; i++)
	{
		if (strcmp(layers[i].layerName, layerName) == 0)
		{
			//found
			return 1;
		}
	}
	//not found
	return 0;
}


