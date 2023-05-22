#include "instance.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT || messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		printf("validation layer: %s\n", pCallbackData->pMessage);
	}

	return VK_FALSE;
}

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != NULL) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL) {
		func(instance, debugMessenger, pAllocator);
	}
}

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo) {
	createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo->pfnUserCallback = debugCallback;
	createInfo->pUserData = NULL;
	createInfo->flags = 0;
	createInfo->pNext = NULL;
}

void create_validation_layers(Instance* instance)
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(&createInfo);

	if (CreateDebugUtilsMessengerEXT(instance->instance, &createInfo, NULL, &instance->debugMessenger) != VK_SUCCESS)
	{
		printf("Debug utils messenger failed to create\n");
	}
}

void vulkan_instance_create(Instance* instance, Instance_options options)
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = options.application_options.applicationName;
	appInfo.applicationVersion = options.application_options.applicationVersion;
	appInfo.pEngineName = options.application_options.engineName;
	appInfo.engineVersion = options.application_options.engineVersion;
	appInfo.apiVersion = options.application_options.vulkanVersion;
	appInfo.pNext = NULL;

	VkInstanceCreateInfo instanceCreateInfo;
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	instanceCreateInfo.enabledExtensionCount = options.extension_options.extensionCount;
	instanceCreateInfo.ppEnabledExtensionNames = options.extension_options.extensionNames;
	instanceCreateInfo.enabledLayerCount = options.layer_options.layerCount;
	instanceCreateInfo.ppEnabledLayerNames = options.layer_options.layerNames;
	instanceCreateInfo.flags = options.flags;

	if (enable_validation)
	{
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		populateDebugMessengerCreateInfo(&debugCreateInfo);

		instanceCreateInfo.pNext = &debugCreateInfo;
	}
	else
	{
		instanceCreateInfo.pNext = NULL;
	}

	const VkResult result = vkCreateInstance(&instanceCreateInfo, NULL, &instance->instance);
	if (result != VK_SUCCESS)
	{
		printf("failed to initialize vulkan with code %d", result);
	}

	if (enable_validation)
	{
		create_validation_layers(instance);
	}
}

void vulkan_instance_destroy(Instance* instance)
{
	DestroyDebugUtilsMessengerEXT(instance->instance, instance->debugMessenger, NULL);
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
	for (u32 i = 0; i < extension_count; i++)
	{
		if (strcmp(extensions[i].extensionName, extensionName) == 0)
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