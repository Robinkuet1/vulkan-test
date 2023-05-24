#pragma once

#include <vulkan/vulkan.h>

#include "core/core.h"
#include "instance.h"

/**
 * \brief contains all the required components to interface with a physical vulkan device
 */
typedef struct
{
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
} PhysicalDevice;

/**
 * \brief contains all the required components to interface with a logical vulkan device
 */
typedef struct
{
	VkDevice device;
	VkQueue graphicsQueue;
} Device;

typedef struct
{
	u32 graphicsFamily;
	u8 graphicsFamilyFound;

	u32 presentFamily;
	u8 presentFamilyFound;
} QueueFamilyIndices;

/**
 * \brief returns an array of all Vulkan capable devices on this instance
 * \param instance vulkan instance
 */
void vulkan_physical_device_print(in Instance* instance);

/**
 * \brief returns an array of all Vulkan capable devices on this instance
 * \param instance vulkan instance
 * \param devices pointer to array of physical devices
 * \param device_count count of vulkan capable devices on this array
 */
void vulkan_physical_device_get_all(in Instance* instance, out PhysicalDevice** devices, out u32* device_count);

/**
 * \brief returns if a physical device is suitable or not
 * \param device device to evaluate
 * \return true if the device is suitable
 * \attention this function is intended to be edited by the user of this library to include individual tests for features the user might need.
 */
u8 vulkan_physical_device_is_suitable(in PhysicalDevice device);

/**
 * \brief scores a physical device based on different parameters 
 * \param device device to score
 * \return a score based on many different parameters
 */
f64 vulkan_physical_device_score(in PhysicalDevice device);

/**
 * \brief returns the queue family index
 * \param device handle for a vulkan physical device
 * \param index returns the index for the vulkan family queue
 */
result vulkan_physical_device_find_queue_family(in const PhysicalDevice* device, out u32* index);

/**
 * \brief enumerates over all devices and returns the best fitting one
 * \param instance vulkan instance
 */
result vulkan_physical_device_get_best(in Instance* instance, out PhysicalDevice* device);

/**
 * \brief creates a vulkan logical device from a physical device
 * \param physicalDevice handle for a vulkan physical device
 */
result vulkan_logical_device_create(in const PhysicalDevice* physicalDevice, out Device* device);

/**
 * \brief destroys a vulkan logical device
 * \param device device to destroy
 */
void vulkan_logical_device_destroy(in Device* device);

u8 vulkan_queue_family_index_completed(in const QueueFamilyIndices* indices);