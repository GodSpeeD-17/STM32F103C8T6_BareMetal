/**
 * @file stm32f1xx_i2c.h
 * @author Shrey Shah
 * @defgroup I2C Inter-Integrated Circuit (I2C)
 * @brief This file contains all the I2C peripheral register definitions for STM32F1
 * @version v1.0
 * @date 16-11-2025
 * @details
 *  I2C Peripheral Initialization Steps:
	*  ** I2Cx->CR2.BIT.FREQ: I2C Clock Frequency 
	* 	Generally same as APBx Clock Frequency
	* 	APB1 Clock = 36MHz -> I2C Clock = 36MHz i.e (0x24)
	*  ** I2Cx->CCR.BIT.CCR: In I2C protocol, the transistors of master devices pull down the lines and the pull-up resistors pull
	* 	the lines up. Since the internal resistance of transistors are much less than the pull-up resistors, the fall
	* 	time is much less than the rise time. Using the I2C_TRISE, we mention the amount of time that the rise
	* 	time might take
	*  * I2C Duty Cycle and Baud Rate Configuration
	*  * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
	*  * | 	F/S 	  | DUTY |Duty Cycle for SCL |    Tlow     |    Thigh    | TI2C (Tlow+Thigh) |  **Baud Rate (1/TI2C)**	|
	*  * |--------------|------|-------------------|-------------|-------------|-------------------|--------------------------|
	*  * | 0 (Standard) |  X   |       50%    	 | CCR × TPCLK | CCR × TPCLK | 2×CCR×TPCLK       |  (APB1 Clock)/(2×CCR)    |
	*  * | 1 (Fast)     |  0   |		33.3%  		 | CCR × TPCLK | 2×CCR×TPCLK | 3×CCR×TPCLK       |  (APB1 Clock)/(3×CCR)    |
	*  * | 1 (Fast)     |  1   |		 36%    	 | 9×CCR×TPCLK | 16×CCR×TPCLK| 25×CCR×TPCLK      |  (APB1 Clock)/(25×CCR)   |
	*  * ----------------------------------------------------------------------------------------------------------------------
	*  * 
	*  * Thus;
	*  * For Standard Mode:
	*  * 	DUTY = x:
	*  * 		CCR = (APB1 Clock)/(100kHz * 2) = (APB1 Clock)/(200kHz);
	*  * For Fast Mode:
	*  * 	DUTY = 0:
	*  * 		CCR = (APB1 Clock)/(400kHz * 3) = (APB1 Clock)/(1200kHz);
	*  * 	DUTY = 1:
	*  * 		CCR = (APB1 Clock)/(400kHz * 25) = (APB1 Clock)/(10MHz);
	*  * 
	*  ** TRISE:
	*  - For Standard Mode: 100kHz
	* 	I2C_TRISE = (APB1 Clock/1MHz) + 1
	* 	I2C_TRISE = (36MHz/1MHz) + 1 = 36 + 1 = 37
	*  - For Fast Mode: 400kHz
	* 	I2C_TRISE = (0.3 * (APB1 Clock/1MHz)) + 1
	* 	I2C_TRISE = (0.3 * (36MHz/1MHz)) + 1 = (0.3 * 36) + 1 = (10.8) + 1 = 11.8 ~ 12
	*
 */

// Header Guards
#ifndef STM32F1XX_I2C_H_
#define STM32F1XX_I2C_H_

// Includes
#include <stdint.h>

// C++ Safeguards
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief	I2C Peripheral Memory Size
 * @def		 I2C_PERIPHERAL_SIZE 
 * @details  
 * Each I2C peripheral (I2C1–I2C2) on the STM32F103C8T6 occupies a fixed <b>1 kB (0x400 bytes)</b>
 * address block in the <b>APB1 peripheral memory space</b>
 *
 * Although the @ref I2C_TypeDef "I2C register structure" uses only 0x24 bytes
 * (the sum of all defined registers), the hardware reserves a full 0x400-byte
 * region per I2C instance. This spacing ensures aligned, uniform addressing
 * for all I2C peripherals and simplifies peripheral bus decoding logic.
 *
 * @note 
 * - Use this constant when computing peripheral index offsets or bit positions.
 * - Do **not** use `sizeof(I2C_TypeDef)` for address-based calculations, as it
 *   does not reflect the physical memory spacing.
 *
 * @see Reference Manual RM0008, Section 3.2 "Memory Map"
 * @see @ref I2C_01_Registers_02_Memory "I2C Peripheral Memory Address"
 * @see @ref `BIT_POS`() "Peripheral Index Computation"
 */
#define I2C_PERIPHERAL_SIZE						((uint32_t) 0x400UL)

/**
 * @brief I2C Peripheral Hardware Register Mapping
 * @defgroup  I2C_01_Registers I2C Registers
 * @ingroup   I2C
 * @details
 * - STM32F103C8T6 I2C peripheral provides I2C bus interface functionality
 * - Supports standard-mode (Sm) up to 100 kHz and fast-mode (Fm) up to 400 kHz
 * - Implements multi-master and slave communication with 7-bit/10-bit addressing
 *
 * - I2C Register Map:
 *
 * | Offset | Register | Name | Description |
 * |--------|----------|------|-------------|
 * | 0x00   | I2C_CR1    | Control Register 1 | Controls peripheral enable, addressing modes, and protocol features |
 * | 0x04   | I2C_CR2    | Control Register 2 | Configures clock frequency, interrupts, and DMA |
 * | 0x08   | I2C_OAR1   | Own Address Register 1 | Sets primary device address for slave mode |
 * | 0x0C   | I2C_OAR2   | Own Address Register 2 | Sets secondary address for dual addressing mode |
 * | 0x10   | I2C_DR     | Data Register | Holds data for transmission/reception |
 * | 0x14   | I2C_SR1    | Status Register 1 | Monitors communication status and events |
 * | 0x18   | I2C_SR2    | Status Register 2 | Provides additional status information |
 * | 0x1C   | I2C_CCR    | Clock Control Register | Configures I2C timing and speed modes |
 * | 0x20   | I2C_TRISE  | TRISE Register | Sets maximum rise time for timing compliance |
 *
 * - Key Features:
 * <ul>
 * <li> Communication Modes:
 * 	<ul>
 *   <li> Master transmitter/receiver mode </li>
 *   <li> Slave transmitter/receiver mode </li>
 *   <li> Multi-master capability with arbitration </li>
 * 	</ul>
 * </li>
 * <li> Addressing Capabilities:
 * 	<ul>
 *   <li> 7-bit addressing with 112 addresses </li>
 *   <li> 10-bit addressing for extended address range </li>
 *   <li> Dual addressing mode for multiple slave addresses </li>
 *   <li> General call address recognition </li>
 * 	</ul>
 * </li>
 * <li> Advanced Features:
 * 	<ul>
 *   <li> Clock stretching support for slow slaves </li>
 *   <li> SMBus protocol compatibility </li>
 *   <li> Packet Error Checking (PEC) for data integrity </li>
 *   <li> DMA support for efficient data transfer </li>
 *   <li> Error detection (BERR, ARLO, AF, OVR) </li>
 * 	</ul>
 * </li>
 * <li> Performance:
 * 	<ul>
 *   <li> Standard mode: up to 100 kbit/s </li>
 *   <li> Fast mode: up to 400 kbit/s </li>
 *   <li> Fast mode plus: up to 1 Mbit/s (device dependent) </li>
 * 	</ul>
 * </li>
 * </ul>
 *
 * @note I2C initialization must follow proper sequence: disable PE → configure → enable PE
 * @warning Changing I2C configuration while bus is active may cause communication errors
 * @warning Clock frequency (CR2.FREQ) must match actual APB1 clock frequency for correct timing
 *
 * @see Reference Manual RM0008 - Section 24. Inter-Integrated Circuit (I2C) interface
 * @see Datasheet DS5319 - Section 5. Memory mapping
 * @{ 
 */

/**
 * @defgroup I2C_01_Registers_01_Structure I2C Registers Encapsulation
 * @ingroup  I2C_01_Registers
 * @brief    I2C Registers representation using structure
 */

/**
 * @defgroup I2C_01_Registers_02_Memory I2C Memory Address
 * @ingroup  I2C_01_Registers 
 * @brief    STM32F1xx I2C Memory Address Mapping
 */

/**
 * @defgroup I2C_01_Registers_03_API I2C Register Access APIs
 * @ingroup  I2C_01_Registers 
 * @brief    APIs to access @ref I2C_01_Registers_01_Structure "I2C Registers"
 */

/** @} */ // I2C_01_Registers


// =============================================================================
// I2C Register Definitions
// =============================================================================

/**
 * @addtogroup I2C_01_Registers_01_Structure
 * @{
 * @brief I2C Peripheral Register Structure
 * @typedef I2C_TypeDef
 */
typedef volatile struct __I2C_TypeDef 
{
	/**
	 * @brief Control Register 1 (CR1)
	 * @details
	 * - Main control register for I2C configuration and operation
	 * - Controls peripheral enable, SMBus mode, and protocol features
	 * - Manages start/stop generation and clock stretching
	 * @union I2C_CR1
	 */
	union I2C_CR1
	{
		volatile uint32_t REG;
		struct 
		{
			// Peripheral enable
			volatile uint32_t PE: 1;
			// SMBus mode
			volatile uint32_t SMBUS: 1;
			volatile uint32_t RESERVED_1: 1;
			volatile uint32_t SMBTYPE: 1;
			// ARP enable
			volatile uint32_t ENARP: 1;
			// PEC enable
			volatile uint32_t ENPEC: 1;
			// General call enable
			volatile uint32_t ENGC: 1;
			// Clock stretching disable (Slave mode)
			volatile uint32_t NOSTRETCH: 1;
			// Start generation
			volatile uint32_t START: 1;
			// Stop generation
			volatile uint32_t STOP: 1;
			// Acknowledge enable
			volatile uint32_t ACK: 1;
			// Acknowledge/PEC Position (for data reception)
			volatile uint32_t POS: 1;
			volatile uint32_t PEC: 1;
			volatile uint32_t ALERT: 1;
			volatile uint32_t RESERVED_2: 1;
			// Software reset
			volatile uint32_t SWRST: 1;
			volatile uint32_t RESERVED_3: 16;
		} BIT;
	} CR1;
	/**
	 * @brief Control Register 2 (CR2)
	 * @details
	 * - Clock control and interrupt configuration register
	 * - Sets peripheral clock frequency for timing generation
	 * - Controls interrupt enable flags and DMA configuration
	 * @union I2C_CR2
	 */
	union I2C_CR2 
	{
		volatile uint32_t REG;
		struct
		{
			// Peripheral clock frequency
			volatile uint32_t FREQ: 6;
			volatile uint32_t RESERVED_1: 2;
			// Error interrupt enable
			volatile uint32_t ITERREN: 1;
			// Event interrupt enable
			volatile uint32_t ITEVTEN: 1;
			// Buffer interrupt enable
			volatile uint32_t ITBUFEN: 1;
			// DMA requests enable
			volatile uint32_t DMAEN: 1;
			// DMA last transfer
			volatile uint32_t LAST: 1;
			volatile uint32_t RESERVED_2: 19;
		} BIT;
	} CR2;
	/**
	 * @brief Own Address Register 1 (OAR1)
	 * @details
	 * - Primary device address configuration register
	 * - Configures 7-bit or 10-bit addressing mode
	 * - Contains device own address for slave mode operation
	 * @union I2C_OAR1
	 */
	union I2C_OAR1 
	{
		volatile uint32_t REG;
		struct 
		{
			volatile uint32_t ADD0: 1;
			volatile uint32_t ADD1_7: 7;
			volatile uint32_t ADD8_9: 2;
			volatile uint32_t RESERVED_1: 5;
			volatile uint32_t ADDMODE: 1;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} OAR1;
	/**
	 * @brief Own Address Register 2 (OAR2)
	 * @details
	 * - Secondary device address configuration register
	 * - Enables dual addressing mode for multiple device addresses
	 * - Contains second I2C address when dual mode is enabled
	 * @union I2C_OAR2
	 */
	union I2C_OAR2
	{
		volatile uint32_t REG;
		struct 
		{
			volatile uint32_t ENDUAL: 1;
			volatile uint32_t ADD2_1_7: 7;
			volatile uint32_t RESERVED: 24;
		} BIT;
	} OAR2;
	/**
	 * @brief Data Register (DR)
	 * @details
	 * - Data transfer register for I2C communication
	 * - Used for both transmit and receive data operations
	 * - Contains 8-bit data value for I2C frame transmission
	 * @union I2C_DR
	 */
	union I2C_DR
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t DR: 8;
			volatile uint32_t RESERVED: 24;
		} BIT;
	} DR;
	/**
	 * @brief Status Register 1 (SR1)
	 * @details
	 * - Primary status register for I2C operation flags
	 * - Contains event flags for start condition, address match, and data transfer
	 * - Includes error flags for bus errors and arbitration loss
	 * @union I2C_SR1
	 */
	union I2C_SR1
	{
		volatile uint32_t REG;
		struct
		{
			// Start bit (Master mode)
			volatile uint32_t SB: 1;
			// Address sent (master mode)/matched (slave mode)
			volatile uint32_t ADDR: 1;
			// Byte transfer finished
			volatile uint32_t BTF: 1;
			// 10-bit header sent (Master mode)
			volatile uint32_t ADD10: 1;
			// Stop detection (slave mode)
			volatile uint32_t STOPF: 1;
			volatile uint32_t RESERVED_1: 1;
			// Data register not empty (receivers)
			volatile uint32_t RxNE: 1;
			// Data register empty (transmitters)
			volatile uint32_t TxE: 1;
			// Bus error
			volatile uint32_t BERR: 1;
			// Arbitration lost (master mode)
			volatile uint32_t ARLO: 1;
			// Acknowledge failure
			volatile uint32_t AF: 1;
			// Overrun/Underrun
			volatile uint32_t OVR: 1;
			volatile uint32_t PECERR: 1;
			volatile uint32_t RESERVED_2: 1;
			// Timeout or Tlow error
			volatile uint32_t TIMEOUT: 1;
			volatile uint32_t SMBALERT: 1;
			volatile uint32_t RESERVED_3: 16;
		} BIT;
	} SR1;
	/**
	 * @brief Status Register 2 (SR2)
	 * @details
	 * - Secondary status register with additional status information
	 * - Contains master/slave mode indicator and bus busy flag
	 * - Includes transmitter/receiver direction and PEC value
	 * @union I2C_SR2
	 */
	union I2C_SR2
	{
		volatile uint32_t REG;
		struct
		{
			volatile uint32_t MSL: 1;
			volatile uint32_t BUSY: 1;
			// Transmitter/receiver
			volatile uint32_t TRA: 1;
			volatile uint32_t RESERVED_1: 1;
			volatile uint32_t GENCALL: 1;
			volatile uint32_t SMBDEFAULT: 1;
			volatile uint32_t SMBHOST: 1;
			volatile uint32_t DUALF: 1;
			volatile uint32_t PEC: 8;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} SR2;
	/**
	 * @brief Clock Control Register (CCR)
	 * @details
	 * - I2C clock configuration and timing control register
	 * - Sets I2C communication speed in standard and fast modes
	 * - Controls duty cycle for fast mode operation
	 * @union I2C_CCR
	 */
	union I2C_CCR
	{
		volatile uint32_t REG;
		struct {
			volatile uint32_t CCR: 12;
			volatile uint32_t RESERVED_1: 2;
			// Fm mode duty cycle
			volatile uint32_t DUTY: 1;
			// I2C master mode selection
			volatile uint32_t F_S: 1;
			volatile uint32_t RESERVED_2: 16;
		} BIT;
	} CCR;
		/**
	 * @brief TRISE Register (TRISE)
	 * @details
	 * - Maximum rise time configuration register
	 * - Sets maximum SCL rise time for I2C timing compliance
	 * - Used in both standard and fast mode master operation
	 * @union I2C_TRISE
	 */
	union I2C_TRISE
	{
		volatile uint32_t REG;
		struct
		{
			// Maximum rise time in Fm/Sm mode (Master mode)
			volatile uint32_t TRISE: 6;
			volatile uint32_t RESERVED: 26;
		} BIT;
	} TRISE;
} I2C_TypeDef;

/** @} */ // I2C_01_Registers_01_Structure

// C++ Safeguards
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32F1XX_I2C_H_ */
