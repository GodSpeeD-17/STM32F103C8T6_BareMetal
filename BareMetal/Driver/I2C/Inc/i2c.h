/**
 * @file i2c.h
 * @author Shrey Shah
 * @brief I2C Driver Header File
 * @version v1.0
 * @date 16-11-2025
 */

#ifndef I2C_H_
#define I2C_H_

// Includes
#include "i2c_ll.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup I2C_03_Driver
 * @{
 */

/**
 * @brief    I2C Peripheral Instance Identifiers
 * @defgroup I2C_03_Driver_01_PeripheralInstances I2C Peripheral Instances
 * @ingroup  I2C_03_Driver
 * @details
 * - Type-safe identifiers for I2C peripheral instances
 * - Used to reference specific I2C peripherals in configuration and operation functions
 * - Supports I2C1 and I2C2 on STM32F103C8T6
 *
 * @see I2C_Init() for usage examples
 * @see I2C_Config() for configuration using these identifiers
 * @see Reference Manual RM0008 - Section 24 I2C Interface
 * @{
 */

/** @brief I2C peripheral instance identifier type @typedef i2c_t */
typedef uint8_t									i2c_t;
/** @brief I2C1 peripheral instance @def I2C_1 */
#define I2C_1									((i2c_t) (0x00))
/** @brief I2C2 peripheral instance @def I2C_2 */
#define I2C_2									((i2c_t) (0x01))

/** @} */ // I2C_03_Driver_01_PeripheralInstances

/*---------------------------------------------- I2C Protocol Configuration ----------------------------------------------*/ 
/**
 * @brief    I2C Protocol Speed Mode Configuration
 * @defgroup I2C_03_Driver_02_ProtocolSpeedMode I2C Protocol Speed Mode
 * @ingroup  I2C_03_Driver
 * @details
 * - Defines I2C communication speed modes (Standard Mode and Fast Mode)
 * - Standard Mode: Up to 100 kHz operation
 * - Fast Mode: Up to 400 kHz operation
 * - Selection depends on application requirements and pull-up resistor characteristics
 *
 * @see I2C Timing Specifications in Reference Manual RM0008 - Section 24.4
 * @see @ref I2C_03_Driver_03_ProtocolSpeedFMDuty for Fast Mode duty cycle options
 * @{
 */

/**
 * \section I2C_Driver_ProtocolSpeedMode_Definitions I2C Driver Protocol Speed Mode Definitions
 * \brief I2C Protocol Speed Mode Configuration
 */ 

/** @brief I2C protocol speed mode type definition @typedef i2c_protocol_speed_mode_t */
typedef uint8_t									i2c_protocol_speed_mode_t;
/** @brief Standard Mode (up to 100 kHz) @def I2C_PROTOCOL_SPEED_MODE_SM */
#define I2C_PROTOCOL_SPEED_MODE_SM				((i2c_protocol_speed_mode_t) (0x00))
/** @brief Fast Mode (up to 400 kHz) @def I2C_PROTOCOL_SPEED_MODE_FM */
#define I2C_PROTOCOL_SPEED_MODE_FM				((i2c_protocol_speed_mode_t) (0x01))

/** @} */ // I2C_03_Driver_02_ProtocolSpeedMode

/*---------------------------------------------- I2C Fast Mode Duty Cycle ----------------------------------------------*/ 
/**
 * @brief    I2C Fast Mode Duty Cycle Configuration
 * @defgroup I2C_03_Driver_03_ProtocolSpeedFMDuty I2C Fast Mode Duty Cycle
 * @ingroup  I2C_03_Driver
 * @details
 * - Defines duty cycle options for I2C Fast Mode operation
 * - Controls the Thigh/Tlow ratio for SCL signal in Fast Mode
 * - Available only when Fast Mode is selected
 *
 * **Duty Cycle Options:**
 * - 2:1 duty cycle: Thigh = 2 × Tlow (33% duty)
 * - 16:9 duty cycle: Thigh = 16/9 × Tlow (64% duty)
 *
 * @see Reference Manual RM0008 - Section 24.4.5 I2C clock generation
 * @see @ref I2C_03_Driver_02_ProtocolSpeedMode for speed mode selection
 * @{
 */

/**
 * \section I2C_Driver_ProtocolSpeedFMDuty_Definitions I2C Driver Fast Mode Duty Cycle Definitions
 * \brief I2C Fast Mode Duty Cycle Configuration
 */
/** @brief I2C Fast Mode duty cycle type definition @typedef i2c_protocol_speed_fm_duty_t */
typedef uint8_t									i2c_protocol_speed_fm_duty_t;
/** @brief 2:1 duty cycle (Thigh = 2 × Tlow) @def I2C_PROTOCOL_SPEED_FM_DUTY_2_1 */
#define I2C_PROTOCOL_SPEED_FM_DUTY_2_1			((i2c_protocol_speed_fm_duty_t) (0x00))
/** @brief 16:9 duty cycle (Thigh = 16/9 × Tlow) @def I2C_PROTOCOL_SPEED_FM_DUTY_16_9 */
#define I2C_PROTOCOL_SPEED_FM_DUTY_16_9			((i2c_protocol_speed_fm_duty_t) (0x01))

/** @} */ // I2C_03_Driver_03_ProtocolSpeedFMDuty

/*---------------------------------------------- I2C Acknowledgment Configuration ----------------------------------------------*/ 
/**
 * @brief    I2C Acknowledgment Configuration
 * @defgroup I2C_03_Driver_04_ProtocolAck I2C Acknowledgment Control
 * @ingroup  I2C_03_Driver
 * @details
 * - Controls I2C acknowledgment generation for slave devices
 * - When enabled, slave generates ACK after each byte reception
 * - When disabled, slave does not generate ACK (used in some advanced scenarios)
 * - Typically kept enabled for normal operation
 *
 * @see Reference Manual RM0008 - Section 24.6.1 Control register 1 (I2C_CR1)
 * @{
 */

/**
 * \section I2C_Driver_ProtocolAck_Definitions I2C Driver Acknowledgment Definitions
 * \brief I2C Acknowledgment Configuration
 */

/** @brief I2C acknowledgment control type definition @typedef i2c_protocol_ack_t */
typedef uint8_t									i2c_protocol_ack_t;
/** @brief Acknowledgment disabled @def I2C_PROTOCOL_ACK_DISABLE */
#define I2C_PROTOCOL_ACK_DISABLE				((i2c_protocol_ack_t) (0x00))
/** @brief Acknowledgment enabled @def I2C_PROTOCOL_ACK_ENABLE */
#define I2C_PROTOCOL_ACK_ENABLE					((i2c_protocol_ack_t) (0x01))

/** @} */ // I2C_03_Driver_04_ProtocolAck

/*---------------------------------------------- I2C Clock Stretching Configuration ----------------------------------------------*/ 
/**
 * @brief    I2C Clock Stretching Configuration
 * @defgroup I2C_03_Driver_05_ProtocolStretch I2C Clock Stretching Control
 * @ingroup  I2C_03_Driver
 * @details
 * - Controls I2C clock stretching capability for slave devices
 * - When enabled, slave can hold SCL low to delay communication
 * - When disabled, slave cannot stretch clock (useful for some masters)
 * - Typically enabled to allow slaves time to process data
 *
 * @see Reference Manual RM0008 - Section 24.4.6 Clock stretching
 * @{
 */

/**
 * \section I2C_Driver_ProtocolStretch_Definitions I2C Driver Clock Stretching Definitions
 * \brief I2C Clock Stretching Configuration
 */

/** @brief I2C clock stretching control type definition @typedef i2c_protocol_stretch_t */
typedef uint8_t									i2c_protocol_stretch_t;
/** @brief Clock stretching disabled @def I2C_PROTOCOL_STRETCH_DISABLE */
#define I2C_PROTOCOL_STRETCH_DISABLE			((i2c_protocol_stretch_t) (0x00))
/** @brief Clock stretching enabled @def I2C_PROTOCOL_STRETCH_ENABLE */
#define I2C_PROTOCOL_STRETCH_ENABLE				((i2c_protocol_stretch_t) (0x01))

/** @} */ // I2C_03_Driver_05_ProtocolStretch

/*---------------------------------------------- I2C Protocol Structure ----------------------------------------------*/ 
/**
 * @brief    I2C Protocol Configuration Structure
 * @defgroup I2C_03_Driver_06_ProtocolStructure I2C Protocol Structure
 * @ingroup  I2C_03_Driver
 * @details
 * - Combined protocol configuration structure for I2C communication
 * - Uses bit fields for efficient storage and access
 * - Contains all essential protocol parameters in a single structure
 *
 * @see @ref I2C_Init() for initialization usage
 * @see @ref I2C_Config() for configuration procedure
 * @{
 */

/**
 * \section I2C_Driver_ProtocolStructure_Definition I2C Driver Protocol Structure Definition
 * \brief I2C Protocol Configuration Structure
 */

/** 
 * @brief I2C protocol configuration structure
 * @typedef i2c_protocol_t
 * @details
 * <details>
 * <summary><b>Click to expand I2C Protocol Configuration Details</b></summary>
 * 
 * Complete protocol configuration for I2C communication. This structure combines
 * all timing and control parameters needed for I2C peripheral initialization.
 * 
 * **Usage Example:**
 * @code
 * i2c_protocol_t protocol_config = {
 *     .speed = I2C_PROTOCOL_SPEED_MODE_FM,      // 400kHz Fast Mode
 *     .duty = I2C_PROTOCOL_SPEED_FM_DUTY_2_1,   // 2:1 duty cycle
 *     .ack = I2C_PROTOCOL_ACK_ENABLE,           // Enable acknowledgment
 *     .stretch = I2C_PROTOCOL_STRETCH_ENABLE    // Allow clock stretching
 * };
 * @endcode
 * 
 * **Configuration Guidelines:**
 * - For most applications, use Fast Mode with acknowledgment enabled
 * - Clock stretching should be enabled unless master requires deterministic timing
 * - Duty cycle selection depends on pull-up resistor characteristics
 * 
 * @see @ref I2C_03_Driver_02_ProtocolSpeedMode for speed mode details
 * @see @ref I2C_03_Driver_03_ProtocolSpeedFMDuty for duty cycle details
 * </details>
 */
typedef struct
{
	/** 
	 * @brief I2C communication speed mode
	 * @details
	 * - Use @ref I2C_PROTOCOL_SPEED_MODE_SM for Standard Mode (100 kHz)
	 * - Use @ref I2C_PROTOCOL_SPEED_MODE_FM for Fast Mode (400 kHz)
	 * 
	 * **Standard Mode (100 kHz):**
	 * - Maximum frequency: 100 kHz
	 * - Suitable for long bus lines and simple sensors
	 * - Lower EMI and power consumption
	 * 
	 * **Fast Mode (400 kHz):**
	 * - Maximum frequency: 400 kHz  
	 * - Recommended for most applications
	 * - Higher throughput for data-intensive devices
	 * 
	 * @note Fast Mode requires stronger pull-up resistors (typically 1-2 kΩ)
	 */	
	i2c_protocol_speed_mode_t speed: 1;

	/** 
	 * @brief Fast Mode duty cycle configuration
	 * @details
	 * - Use @ref I2C_PROTOCOL_SPEED_FM_DUTY_2_1 for 2:1 duty cycle (Thigh/Tlow = 2)
	 * - Use @ref I2C_PROTOCOL_SPEED_FM_DUTY_16_9 for 16:9 duty cycle (Thigh/Tlow ≈ 1.78)
	 * 
	 * **2:1 Duty Cycle:**
	 * - Thigh = 2 × CCR × TPCLK
	 * - Tlow = 1 × CCR × TPCLK  
	 * - Total period: 3 × CCR × TPCLK
	 * - CCR = PCLK1 / (3 × FSCL)
	 * 
	 * **16:9 Duty Cycle:**
	 * - Thigh = 9 × CCR × TPCLK
	 * - Tlow = 16 × CCR × TPCLK
	 * - Total period: 25 × CCR × TPCLK
	 * - CCR = PCLK1 / (25 × FSCL)
	 * 
	 * @note This field is only meaningful when speed mode is set to Fast Mode
	 * @see Reference Manual RM0008 - Section 24.4.5 Clock generation
	 */
	i2c_protocol_speed_fm_duty_t duty: 1;

	/** 
	 * @brief I2C acknowledgment control
	 * @details
	 * - Use @ref I2C_PROTOCOL_ACK_ENABLE to enable acknowledgment (recommended)
	 * - Use @ref I2C_PROTOCOL_ACK_DISABLE to disable acknowledgment
	 * 
	 * **When Enabled:**
	 * - Slave generates ACK pulse after each byte reception
	 * - Required for normal multi-byte communication
	 * - Master expects ACK after transmitting address and data bytes
	 * 
	 * **When Disabled:**
	 * - Slave does not generate ACK pulses
	 * - Used for advanced scenarios like clock synchronization
	 * - Not recommended for normal operation
	 * 
	 * @note Most applications should keep acknowledgment enabled
	 */
	i2c_protocol_ack_t ack: 1;

	/** 
	 * @brief I2C clock stretching control
	 * @details
	 * - Use @ref I2C_PROTOCOL_STRETCH_ENABLE to allow clock stretching (recommended)
	 * - Use @ref I2C_PROTOCOL_STRETCH_DISABLE to prevent clock stretching
	 * 
	 * **When Enabled:**
	 * - Slave can hold SCL low to pause communication
	 * - Allows slave time to process received data
	 * - Essential for slave devices with variable processing times
	 * 
	 * **When Disabled:**
	 * - Slave cannot stretch the clock
	 * - Useful when master requires deterministic timing
	 * - Requires slave to process data within fixed time windows
	 * 
	 * @note Disabling clock stretching may cause data loss if slave cannot keep up
	 * @see Reference Manual RM0008 - Section 24.4.6 Clock stretching
	 */	
	i2c_protocol_stretch_t stretch: 1;
} i2c_protocol_t;

/** @} */ // I2C_03_Driver_06_ProtocolStructure

/*---------------------------------------------- SMBus Protocol Structure ----------------------------------------------*/ 
/**
 * @brief    SMBus Protocol Configuration Structure
 * @defgroup I2C_03_Driver_07_SMBusProtocol SMBus Protocol Structure
 * @ingroup  I2C_03_Driver
 * @details
 * - SMBus (System Management Bus) protocol configuration
 * - Based on I2C with additional protocol layers and timeouts
 * - Reserved for future SMBus implementation
 *
 * @see SMBus Specification version 3.0
 * @{
 */

/**
 * \section I2C_Driver_SMBusProtocol_Definition I2C Driver SMBus Protocol Structure Definition
 * \brief SMBus Protocol Configuration Structure
 */

/** 
 * @brief SMBus protocol configuration structure
 * @typedef smbus_protocol_t
 * @note Currently reserved for future implementation
 */
typedef struct
{
	/* Reserved for SMBus protocol implementation */
} smbus_protocol_t;

/** @} */ // I2C_03_Driver_07_SMBusProtocol


/** @} */ // I2C_03_Driver

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* I2C_H_  */ 

#ifdef __OLD_I2C__ 
// Header Guards
#ifndef __I2C_H__
#define __I2C_H__

// Includes
#include "i2c_config.h"

//  MACROS
#define I2C_readAddress(I2Cx, slaveAddress)			(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_READ)))
#define I2C_writeAddress(I2Cx, slaveAddress)		(I2C_writeByte((I2Cx), (((slaveAddress) << 1) | I2Cx_WRITE)))

/**
 * @brief I2C Direction Initialisation
 * @param[in] I2C_CONFIGx I2C Configuration Structure
 */
#define I2C_Init(I2C_CONFIGx) 			\
{										\
	/* I2C Configuration */ 			\
	I2C_Config((I2C_CONFIGx));			\
	/* I2C Enable */ 					\
	I2C_Enable((I2C_CONFIGx)->I2Cx); 	\
}

/**
 * @brief I2C Bus Ready
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns - `0x00`: I2C Bus is not ready
 * @returns - `0x01`: I2C Bus is ready
 */
__STATIC_FORCEINLINE uint8_t I2C_busReady(I2C_TypeDef* I2Cx){
	// Bus Busy
	if((I2Cx->SR2.REG & I2C_SR2_BUSY))
		return 0x00;
	// Bus Free
	else
		return 0x01;
}

/**
 * @brief I2C Send START Sequence
 * @param[in] I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_FORCEINLINE void I2C_sendStart(I2C_TypeDef* I2Cx){
	// Send START condition
	I2Cx->CR1.REG |= I2C_CR1_START;
}

/**
 * @brief I2C Byte Send
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param data Data to be TX
 */
__STATIC_FORCEINLINE void I2C_writeByte(I2C_TypeDef* I2Cx, uint8_t data){
	// Send data
	I2Cx->DR.REG = data;
}

/**
 * @brief I2C Byte Read
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @returns Data received from I2C Bus
 */
__STATIC_FORCEINLINE uint8_t I2C_readByte(I2C_TypeDef* I2Cx){
	// Read data
	uint8_t byte = I2Cx->DR.REG;
	// Wrap
	byte &= 0xFF;
	// Return data
	return byte;
}

/**
 * @brief I2C Send STOP Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 */
__STATIC_FORCEINLINE void I2C_sendStop(I2C_TypeDef* I2Cx){
	// Send STOP condition
	I2Cx->CR1.REG |= I2C_CR1_STOP;
}

/**
 * @brief I2C Master Write Start Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Target I2C Slave Address
 * @note Does not generate STOP condition, use `I2C_sendStop()` after writing data
 */
void I2C_Master_Write_Start(I2C_TypeDef* I2Cx, uint8_t slaveAddress);

/**
 * @brief I2C Master Write Start Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Target I2C Slave Address
 * @param registerAddress Target Register Address
 * @note Does not generate STOP condition, use `I2C_sendStop()` after writing data
 */
void I2C_Master_Write_Start_Reg(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief I2C Master Read Start Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Target I2C Slave Address
 * @param registerAddress Target Register Address
 * @note Does not generate STOP condition, use `I2C_sendStop()` after reading data
 */
void I2C_Master_Read_Start(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief I2C Master Stop Sequence
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 */
void I2C_Master_Stop(I2C_TypeDef* I2Cx);

/**
 * @brief I2C Master Write Buffer Data
 * @param I2Cx I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param buffer Pointer to buffer to be transmitted
 * @param buff_len Length of data in buffer to be transmitted
 */
void I2C_Master_Write_Data(I2C_TypeDef* I2Cx, uint8_t* buffer, uint16_t buff_len);

/**
 * @brief I2C Master Write Byte
 * @param I2Cx I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param data Data to be sent on I2C
 */
__STATIC_FORCEINLINE void I2C_Master_Write_Byte(I2C_TypeDef* I2Cx, uint8_t data){
	// I2C Master Single Byte Sent
	I2C_Master_Write_Data(I2Cx, &data, 1);
}

/**
 * @brief Writes a Single Byte to Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slave_address MAX30102 Slave Address
 * @param register Register Address
 * @param byte Data to be written
 */
void I2C_Write_Reg_Byte(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t byte);

/**
 * @brief Writes Multiple Consecutive Bytes to Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Starting Register Address
 * @param data Pointer to the data buffer
 * @param len Number of bytes to write
 */
void I2C_Write_Reg_Block(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

/**
 * @brief Reads a Single Byte from a Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Register Address to read from
 * @returns The read byte
 */
uint8_t I2C_Read_Reg_Byte(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress);

/**
 * @brief Reads Multiple Consecutive Bytes from a Register Address of a given Slave Address
 * @param I2Cx I2C Instance: `I2C1`, `I2C2`
 * @param slaveAddress Slave Address
 * @param registerAddress Starting Register Address
 * @param data Pointer to the buffer to store the read data
 * @param len Number of bytes to read
 */
void I2C_Read_Reg_Block(I2C_TypeDef* I2Cx, uint8_t slaveAddress, uint8_t registerAddress, uint8_t* data, uint8_t len);

#endif /* __I2C_H__ */

#endif /* __OLD_I2C__ */