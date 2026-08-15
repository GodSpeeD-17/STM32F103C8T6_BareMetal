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
#include "rcc.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup I2C_03_Driver I2C Driver APIs
 * @ingroup I2C
 * @brief I2C Driver APIs
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

/**
 * @brief Convert driver I2C instance to low-level peripheral pointer
 * @param[in] i2cx Driver I2C instance ( @ref `I2C_1`, @ref `I2C_2`)
 * @returns Corresponding I2C_TypeDef peripheral pointer
 */
__STATIC_FORCEINLINE I2C_TypeDef* I2C_D2L_GetInstance(const i2c_t i2cx)
{
	static I2C_TypeDef* const _driverI2CMapping[] = 
	{
		[I2C_1] = I2C1, 
		[I2C_2] = I2C2
	};
	return _driverI2CMapping[i2cx];
}

/** @} */ // I2C_03_Driver_01_PeripheralInstances

/*---------------------------------------------- I2C Protocol Configuration ----------------------------------------------*/ 

/**
 * @defgroup I2C_03_Driver_02_Protocol I2C Protocol Configuration Structure
 * @ingroup I2C_03_Driver
 * @brief I2C Protocol Configuration
 * @{
 */

/**
 * @brief    I2C Protocol Speed Mode Configuration
 * @defgroup I2C_03_Driver_02_Protocol_01_SpeedMode I2C Protocol Speed Mode
 * @ingroup  I2C_03_Driver_02_Protocol
 * @details
 * - Defines I2C communication speed modes (Standard Mode and Fast Mode)
 * - Standard Mode: Up to 100 kHz operation
 * - Fast Mode: Up to 400 kHz operation
 * - Selection depends on application requirements and pull-up resistor characteristics
 *
 * @see I2C Timing Specifications in Reference Manual RM0008 - Section 24.4
 * @see @ref I2C_03_Driver_02_Protocol_02_SpeedFMDuty for Fast Mode duty cycle options
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

/** @} */ // I2C_03_Driver_02_Protocol_01_SpeedMode

/*---------------------------------------------- I2C Fast Mode Duty Cycle ----------------------------------------------*/ 
/**
 * @brief    I2C Fast Mode Duty Cycle Configuration
 * @defgroup I2C_03_Driver_02_Protocol_02_SpeedFMDuty I2C Fast Mode Duty Cycle
 * @ingroup  I2C_03_Driver_02_Protocol
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
 * @see @ref I2C_03_Driver_02_Protocol_01_SpeedMode for speed mode selection
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

/** @} */ // I2C_03_Driver_02_Protocol_02_SpeedFMDuty

/*---------------------------------------------- I2C Acknowledgment Configuration ----------------------------------------------*/ 
/**
 * @brief    I2C Acknowledgment Configuration
 * @defgroup I2C_03_Driver_02_Protocol_03_Ack I2C Acknowledgment Control
 * @ingroup  I2C_03_Driver_02_Protocol
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

/** @} */ // I2C_03_Driver_02_Protocol_03_Ack

/*---------------------------------------------- I2C Clock Stretching Configuration ----------------------------------------------*/ 
/**
 * @brief    I2C Clock Stretching Configuration
 * @defgroup I2C_03_Driver_02_Protocol_04_Stretch I2C Clock Stretching Control
 * @ingroup  I2C_03_Driver_02_Protocol
 * @details
 * - Controls I2C clock stretching capability for slave devices
 * - When enabled, slave can hold SCL low to delay communication
 * - When disabled, slave cannot stretch clock (useful for some masters)
 * - Typically enabled to allow slaves time to process data
 *
 * @see Reference Manual RM0008 - Section 24.4.6 Clock stretching
 * @{
 * \section I2C_Driver_ProtocolStretch_Definitions I2C Driver Clock Stretching Definitions
 * \brief I2C Clock Stretching Configuration
 */

/** @brief I2C clock stretching control type definition @typedef i2c_protocol_stretch_t */
typedef uint8_t									i2c_protocol_stretch_t;
/** @brief Clock stretching disabled @def I2C_PROTOCOL_STRETCH_DISABLE */
#define I2C_PROTOCOL_STRETCH_DISABLE			((i2c_protocol_stretch_t) (0x00))
/** @brief Clock stretching enabled @def I2C_PROTOCOL_STRETCH_ENABLE */
#define I2C_PROTOCOL_STRETCH_ENABLE				((i2c_protocol_stretch_t) (0x01))

/** @} */ // I2C_03_Driver_02_Protocol_04_Stretch

/*---------------------------------------------- I2C Protocol Structure ----------------------------------------------*/ 
/**
 * @brief    I2C Protocol Configuration Structure
 * @defgroup I2C_03_Driver_02_Protocol_05_Structure I2C Protocol Structure
 * @ingroup  I2C_03_Driver_02_Protocol
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
 * i2c_protocol_t protocol_config = 
 * {
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
 * @see @ref I2C_03_Driver_02_Protocol_01_SpeedMode for speed mode details
 * @see @ref I2C_03_Driver_02_Protocol_02_SpeedFMDuty for duty cycle details
 * </details>
 */
typedef struct
{
	/** 
	 * @brief I2C communication speed mode
	 * @details
	 * - Use @ref `I2C_PROTOCOL_SPEED_MODE_SM` for Standard Mode (100 kHz)
	 * - Use @ref `I2C_PROTOCOL_SPEED_MODE_FM` for Fast Mode (400 kHz)
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
	 * - Use @ref `I2C_PROTOCOL_SPEED_FM_DUTY_2_1` for 2:1 duty cycle (Thigh/Tlow = 2)
	 * - Use @ref `I2C_PROTOCOL_SPEED_FM_DUTY_16_9` for 16:9 duty cycle (Thigh/Tlow ≈ 1.78)
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
	 * - Use @ref `I2C_PROTOCOL_ACK_ENABLE` to enable acknowledgment (recommended)
	 * - Use @ref `I2C_PROTOCOL_ACK_DISABLE` to disable acknowledgment
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
	 * - Use @ref `I2C_PROTOCOL_STRETCH_ENABLE` to allow clock stretching (recommended)
	 * - Use @ref `I2C_PROTOCOL_STRETCH_DISABLE` to prevent clock stretching
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

/** @} */ // I2C_03_Driver_02_Protocol_05_Structure


/** @} */ // I2C_03_Driver_02_Protocol

/*---------------------------------------------- SMBus Protocol Structure ----------------------------------------------*/ 
/**
 * @brief    SMBus Protocol Configuration Structure
 * @defgroup I2C_03_Driver_03_SMBusProtocol SMBus Protocol Structure
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

/** @} */ // I2C_03_Driver_03_SMBusProtocol

/*---------------------------------- Address Configuration ----------------------------------*/

/**
 * @brief    I2C Address Configuration Structure 
 * @defgroup I2C_03_Driver_04_Address I2C Address Configuration Structure
 * @ingroup  I2C_03_Driver
 * @details
 * - Complete address configuration for I2C slave mode operation
 * - Supports 7-bit and 10-bit addressing modes with dual address capability
 * - Configures primary and secondary addresses with general call recognition
 * 
 * **Usage Example (7-bit addressing):**
 * @code
 * i2c_slave_address_config_t addr_config = 
 * {
 *     .addr1     = 0x68,                          // Primary address 0x68
 *     .addr2     = 0x00,                          // Secondary address (unused)
 *     .addr_mode = I2C_ADDRESS_MODE_7BIT,         // 7-bit addressing
 *     .dual_addr = I2C_DUAL_ADDRESS_DISABLE,      // Single address mode
 *     .gen_call  = I2C_GENERAL_CALL_ENABLE        // Respond to broadcast
 * };
 * @endcode
 * 
 * **Usage Example (10-bit dual addressing):**
 * @code
 * i2c_slave_address_config_t addr_config = 
 * {
 *     .addr1     = 0x123,                         // Primary address 0x123
 *     .addr2     = 0x456,                         // Secondary address 0x456  
 *     .addr_mode = I2C_ADDRESS_MODE_10BIT,        // 10-bit addressing
 *     .dual_addr = I2C_DUAL_ADDRESS_ENABLE,       // Dual address mode
 *     .gen_call  = I2C_GENERAL_CALL_DISABLE       // Ignore broadcast
 * };
 * @endcode
 * 
 * @note This configuration is only valid when I2C peripheral operates in slave mode
 * @see Reference Manual RM0008 - Section 24.6.3/24.6.4 Own Address Registers
 * @{
 */

/**
 * \section I2C_Driver_Address_Definitions I2C Driver Address Configuration Definitions
 * \brief I2C Address Mode and Control Definitions
 */

/** @brief I2C addressing mode type definition @typedef i2c_address_mode_t */
typedef uint8_t									i2c_address_mode_t;
/** @brief 7-bit addressing mode (0x08-0x77) @def I2C_ADDRESS_MODE_7BIT */
#define I2C_ADDRESS_MODE_7BIT					((i2c_address_mode_t)(0x00))
/** @brief 10-bit addressing mode (0x000-0x3FF) @def I2C_ADDRESS_MODE_10BIT */
#define I2C_ADDRESS_MODE_10BIT					((i2c_address_mode_t)(0x01))

/** @brief I2C dual addressing mode type definition @typedef i2c_dual_address_t */
typedef uint8_t									i2c_dual_address_t;
/** @brief Single address recognition mode @def I2C_DUAL_ADDRESS_DISABLE */
#define I2C_DUAL_ADDRESS_DISABLE				((i2c_dual_address_t)(0x00))
/** @brief Dual address recognition mode @def I2C_DUAL_ADDRESS_ENABLE */
#define I2C_DUAL_ADDRESS_ENABLE					((i2c_dual_address_t)(0x01))

/** @brief I2C general call recognition type definition @typedef i2c_general_call_t */
typedef uint8_t									i2c_general_call_t;
/** @brief Ignore general call address (0x00) @def I2C_GENERAL_CALL_DISABLE */
#define I2C_GENERAL_CALL_DISABLE				((i2c_general_call_t)(0x00))
/** @brief Respond to general call address (0x00) @def I2C_GENERAL_CALL_ENABLE */
#define I2C_GENERAL_CALL_ENABLE					((i2c_general_call_t)(0x01))

/** @brief I2C Address value type definition @typedef i2c_address_t */
typedef uint16_t 								i2c_address_t;

/**
 * \section I2C_Driver_Address_Structure I2C Driver Address Configuration Structure
 * \brief I2C Slave Address Configuration Structure
 */

/**
 * @brief I2C Address Configuration Structure (valid for Slave mode)
 * @typedef i2c_slave_address_config_t
 * @details
 * <details>
 * <summary><b>Click to expand I2C Address Configuration Details</b></summary>
 * 
 * Complete address configuration structure for I2C slave mode operation.
 * Configures all addressing-related parameters including primary and secondary
 * addresses, addressing mode, and special address recognition features.
 * 
 * **Bit Field Allocation:**
 * - `addr1` (11 bits): Primary 7-bit or 10-bit address
 * - `addr2` (11 bits): Secondary address for dual mode  
 * - `addr_mode` (1 bit): 7-bit or 10-bit addressing selection
 * - `dual_addr` (1 bit): Dual address recognition enable
 * - `gen_call` (1 bit): General call recognition enable
 * 
 * **Address Range Validation:**
 * - **7-bit mode**: addr1 must be in range 0x08-0x77 (0x00-0x07 and 0x78-0x7F reserved)
 * - **10-bit mode**: addr1 must be in range 0x000-0x3FF
 * 
 * **Configuration Rules:**
 * - When dual addressing is disabled, `addr2` is ignored
 * - General call address (0x00) is always recognized when enabled
 * - 10-bit addressing requires both master and slave support
 * 
 * @warning Address values outside valid ranges may cause undefined behavior
 * @see @ref `I2C_ADDRESS_MODE_7BIT` for 7-bit address range details
 * @see @ref `I2C_ADDRESS_MODE_10BIT` for 10-bit address range details
 * </details>
 */
typedef struct
{
	/** @brief Primary own address (7-bit: 0x08-0x77, 10-bit: 0x000-0x3FF) */
	i2c_address_t addr1				: 10;
	/** @brief Secondary address (only used when dual address enabled) */
	i2c_address_t addr2				: 10;
	/** @brief 7-bit or 10-bit addressing mode selection */
	i2c_address_mode_t addr_mode	: 1;
	/** @brief Enable secondary address recognition */
	i2c_dual_address_t dual_addr	: 1;
	/** @brief Enable general call address (0x00) recognition */
	i2c_general_call_t gen_call		: 1;
} i2c_slave_address_config_t;

/** @} */ // I2C_03_Driver_04_Address

/*---------------------------------- Mode Configuration ----------------------------------*/

/**
 * @brief    I2C Complete Configuration Structure
 * @defgroup I2C_03_Driver_05_Config I2C Configuration Structure
 * @ingroup  I2C_03_Driver
 * @details
 * - Defines I2C peripheral operational modes (Master and Slave)
 * - Master mode: Peripheral initiates communication and controls clock
 * - Slave mode: Peripheral responds to master requests and follows clock
 * - Mode selection affects available features and configuration requirements
 *
 * **Master Mode Characteristics:**
 * - Generates START and STOP conditions
 * - Controls SCL clock frequency
 * - Initiates data transfers to slave devices
 * - Supports multiple slave devices on same bus
 *
 * **Slave Mode Characteristics:**
 * - Responds to own address recognition
 * - Follows master-generated clock
 * - Can stretch clock if processing time required
 * - Supports dual addressing and general call
 * 
 * - Complete I2C peripheral configuration structure
 * - Combines operational mode, protocol timing, and slave addressing
 * - Used for initializing and configuring I2C peripheral instances
 * 
 * @code
 * i2c_config_t master_config = {
 *     .mode     = I2C_MODE_MASTER,
 *     .protocol = {
 *         .speed   = I2C_PROTOCOL_SPEED_MODE_FM,
 *         .duty    = I2C_PROTOCOL_SPEED_FM_DUTY_2_1,
 *         .ack     = I2C_PROTOCOL_ACK_ENABLE,
 *         .stretch = I2C_PROTOCOL_STRETCH_ENABLE
 *     },
 *     .slave    = {
 *         .addr1    = 0x00,  // Not used in master mode
 *         .addr_mode = I2C_ADDRESS_MODE_7BIT
 *     }
 * };
 * @endcode 
 *
 * @see Reference Manual RM0008 - Section 24.4 I2C functional description
 * @{
 */

/**
 * \section I2C_Driver_Mode_Definitions I2C Driver Operational Mode Definitions
 * \brief I2C Operational Mode Type and Constants
 */

/** @brief I2C operational mode type definition @typedef i2c_mode_t */
typedef uint8_t										i2c_mode_t;
/** @brief I2C Master mode (controller role) @def I2C_MODE_MASTER */
#define I2C_MODE_MASTER								((i2c_mode_t)(0x00))
/** @brief I2C Slave mode (responder role) @def I2C_MODE_SLAVE */
#define I2C_MODE_SLAVE								((i2c_mode_t)(0x01))

/**
 * \section I2C_Driver_Config_Structure I2C Driver Configuration Structure
 * \brief Complete I2C Configuration Structure
 */

/**
 * @brief I2C Complete Configuration Structure
 * @typedef i2c_config_t
 */
typedef struct
{
	/** @brief I2C operational mode (Master/Slave) */
	i2c_mode_t mode;
	/** @brief I2C protocol timing configuration */
	i2c_protocol_t protocol;
	/** @brief Slave address configuration (meaningful only in slave mode) */
	i2c_slave_address_config_t slave;
} i2c_config_t;

/** @} */ // I2C_03_Driver_05_Config

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
