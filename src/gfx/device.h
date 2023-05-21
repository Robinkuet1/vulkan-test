#pragma once

#include <vulkan/vulkan.h>

#include "../utils/defines.h"
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