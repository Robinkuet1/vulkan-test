#pragma once

#pragma warning(disable:6385) //reading invalid data
#pragma warning(disable:6011) //dereferencing NULL pointer
#pragma warning(disable:6101) //dereferencing NULL pointer

#include "types.h"
#include "enums.h"

/**
 * \brief data will only be read and not changed by the function
 */
#define in __in

/**
 * \brief data will be read and changed by the function
 */
#define inout __inout

/**
 * \brief data will be created and returned by the function
 */
#define out __out

#define true 1
#define false 0