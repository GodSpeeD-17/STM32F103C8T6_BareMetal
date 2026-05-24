/**
 * @file stm32f1xx_utils.c
 * @author Shrey Shah
 * @brief 
 * @version v1.0
 * @date 01-03-2026
 */

// ------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------
#include "stm32f1xx_utils.h"

// ------------------------------------------------------------------------------------------
// Register Operations Utilities
// ------------------------------------------------------------------------------------------

driver_status_t RegOps_Read(_IO *reg, uint32_t* const out_value)
{
	if ((reg == NULL) || (out_value == NULL))
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*out_value = *reg;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RegOps_Write(_IO *reg, uint32_t value)
{
	if (reg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*reg = value;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RegOps_Set(_IO *reg, uint32_t mask)
{
	if (reg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*reg |= mask;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RegOps_Clear(_IO *reg, uint32_t mask)
{
	if (reg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*reg &= ~mask;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RegOps_Toggle(_IO *reg, uint32_t mask)
{
	if (reg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*reg ^= mask;

	return DRIVER_STATUS_SUCCESS;
}

driver_status_t RegOps_WriteMasked(_IO *reg, uint32_t mask, uint32_t value)
{
	if (reg == NULL)
	{
		return DRIVER_STATUS_ERROR_NULL_PTR;
	}

	*reg = (*reg & ~mask) | (value & mask);

	return DRIVER_STATUS_SUCCESS;
}
