#pragma once

#include "../utils/defines.h"
#include <vulkan/vulkan.h>

typedef struct
{
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	struct Device* device;
} Instance;

typedef struct
{
	const char* applicationName;
	const char* engineName;
	u32 applicationVersion;
	u32 engineVersion;
	u32 vulkanVersion;
} Application_options;

typedef struct
{
	u32 extensionCount;
	const char* const* extensionNames;
} Extension_options;

typedef struct
{
	u32 layerCount;
	const char* const* layerNames;
} Layer_options;

typedef struct
{
	Application_options application_options;
	Extension_options extension_options;
	Layer_options layer_options;
	VkInstanceCreateFlags flags;
	u8 enableValidationLayers;
} Instance_options;

/**
 * \brief creates a new vulkan instance, selects a physical device and creates a logical device
 * \param instance pointer to the new instance
 * \param options options for the new instance and device
 */
void vulkan_instance_create(Instance* instance, Instance_options options);

/**
 * \brief destroys a vulkan instance
 * \param instance pointer to the instance to destroy
 */
void vulkan_instance_destroy(Instance* instance);

/**
 * \brief prints out all supported extensions for this instance
 */
void vulkan_instance_extensions_print(void);

/**
 * \brief prints out all supported layers for this instance
 */
void vulkan_instance_layers_print(void);

/**
 * \brief checks if a extension is supported on this instance
 * \param extensionName name of the extension
 * \return 1 if extension supported
 */
u8 vulkan_instance_extensions_supported(const char* extensionName);

/**
 * \brief checks if a layer is supported on this instance
 * \param layerName name of the layer
 * \return 1 if layer supported
 */
u8 vulkan_instance_layer_supported(const char* layerName);
