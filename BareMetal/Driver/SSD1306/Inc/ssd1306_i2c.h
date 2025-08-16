/**
 * @file ssd1306_i2c.h
 * @author Shrey Shah
 * @brief I2C Initialization Functions for SSD1306 OLED Display
 * @version 1.0
 * @date 15-08-2025
 */

#ifndef __SSD1306_I2C_H__
#define __SSD1306_I2C_H__

// Includes
#include "ssd1306_config.h"

/**
 * @brief Loads `I2C1` configuration for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C1` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
__STATIC_INLINE__ void SSD1306_Load_I2C1(ssd1306_config_t* ssd1306){
	// Set the SSD1306 I2C Address
	ssd1306->address = SSD1306_I2C_ADDRESS;
	// Load default I2C1 Configuration
	I2C1_Load_Default(&ssd1306->i2c_config);
}

/**
 * @brief Loads `I2C2` configuration for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function assumes the following:
 * @note - `I2C2` is used for communication
 * @note - `0x3C` is the I2C address of the display
 */
__STATIC_INLINE__ void SSD1306_Load_I2C2(ssd1306_config_t* ssd1306){
	// Set the SSD1306 I2C Address
	ssd1306->address = SSD1306_I2C_ADDRESS;
	// Load default I2C1 Configuration
	I2C2_Load_Default(&ssd1306->i2c_config);
}

/**
 * @brief Loads input configuration for the SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @param i2c_config Pointer to I2C Configuration Structure
 * @note - Pointer to the I2C configuration structure can be freed after this call
 * @note - This function only copies the contents of the I2C Configuration Structure
 */
__STATIC_INLINE__ void SSD1306_Load_I2C(ssd1306_config_t* ssd1306, i2c_config_t* i2c_config){
	// Update the I2C Configuration
	memcpy(&ssd1306->i2c_config, i2c_config, sizeof(i2c_config_t));
}

/**
 * @brief Configures the I2C Peripheral for SSD1306 OLED Display based on the configuration
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_I2C_Config(ssd1306_config_t* ssd1306){
	// Configure the I2C Peripheral as per the configuration
	I2C_Config(&ssd1306->i2c_config);
}

/**
 * @brief Enables the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_I2C_Enable(ssd1306_config_t* ssd1306){
	// Enable the I2C Peripheral
	I2C_Enable(ssd1306->i2c_config.I2Cx);
}

/**
 * @brief Disables the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 */
__STATIC_INLINE__ void SSD1306_I2C_Disable(ssd1306_config_t* ssd1306){
	// Disable the I2C Peripheral
	I2C_Disable(ssd1306->i2c_config.I2Cx);
}

/**
 * @brief Initializes the I2C Peripheral for SSD1306 OLED Display
 * @param ssd1306 Pointer to the SSD1306 configuration structure
 * @note This function performs the following:
 * @note - Configures the I2C Peripheral
 * @note - Enables the I2C Peripheral
 */
__STATIC_INLINE__ void SSD1306_I2C_Init(ssd1306_config_t* ssd1306){
	// Configure the I2C Peripheral
	SSD1306_I2C_Config(ssd1306);
	// Enable the I2C Peripheral
	SSD1306_I2C_Enable(ssd1306);
}


// ------------------------------------------------------------- CONFIGURATION FUNCTION END ------------------------------------------------------------- //


#endif /* __SSD1306_I2C_H__ */