/***************************************************************************************
 *  File: usart.h
 *  Created on: 21/09/2025
 *  Author: Shrey Shah
 ***************************************************************************************/

// Dependency
#include "usart.h"


#ifdef  __OLD_GPIO_METHOD__

/**
 * @brief Initialises USART based upon input Configuration Structure
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
void USART_Config(usart_config_t* USART_CONFIGx){
	// Configure the GPIO
	GPIO_Init(USART_CONFIGx->TX.GPIO, USART_CONFIGx->TX.PIN, USART_CONFIGx->TX.MODE, USART_CONFIGx->TX.CNF);
	GPIO_Init(USART_CONFIGx->RX.GPIO, USART_CONFIGx->RX.PIN, USART_CONFIGx->RX.MODE, USART_CONFIGx->RX.CNF);
	// Enable USART Clock
	USART_clk_enable(USART_CONFIGx);
	// Configure Baud Rate
	if(USART_CONFIGx->USARTx == USART1)
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(RCC_GetAPB2Clock()/(USART_CONFIGx->baud_rate));
	else
		USART_CONFIGx->USARTx->BRR.REG = (uint32_t)(RCC_GetBusFreq(RCC_APB1_BUS)/(USART_CONFIGx->baud_rate));
	// Configure Stop Bits
	USART_CONFIGx->USARTx->CR2.REG |= ((USART_CONFIGx->stop_bits & 0x03) << USART_CR2_STOP_Pos);
	// Configure Rest of the Parameters
	USART_CONFIGx->USARTx->CR1.REG |= (((USART_CONFIGx->word_length & 0x01) << USART_CR1_M_Pos) | 
									   ((USART_CONFIGx->enable_parity & 0x01) << USART_CR1_PCE_Pos) | 
									   ((USART_CONFIGx->parity_selection & 0x01) << USART_CR1_PS_Pos) | 
									   ((USART_CONFIGx->TXEIE & 0x01) << USART_CR1_TXEIE_Pos) | 
									   ((USART_CONFIGx->TCIE & 0x01) << USART_CR1_TXEIE_Pos) | 
									   ((USART_CONFIGx->RXNEIE & 0x01) << USART_CR1_RXNEIE_Pos) | 
									   ((USART_CONFIGx->TXE & 0x01) << USART_CR1_TE_Pos) | 
									   ((USART_CONFIGx->RXE & 0x01) << USART_CR1_RE_Pos));
	// IRQ Enable
	if(USART_CONFIGx->TCIE || USART_CONFIGx->TXEIE || USART_CONFIGx->RXNEIE)
		NVIC_IRQEnable(USART_get_IRQn(USART_CONFIGx->USARTx));
}

/**
 * @brief Transmits a character on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] c The character to be transmitted
 */
void USART_putc(usart_config_t* USART_CONFIGx, const char c){
	// Wait for TX to be Empty
	while (!(USART_CONFIGx->USARTx->SR.REG & USART_SR_TXE_Msk));
	// Transfer the data 
	USART_CONFIGx->USARTx->DR.REG = (c & 0x000000FF);
}

/**
 * @brief Reads the USARTx->DR
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns The value of the USARTx->DR
 */
uint16_t USART_getc(usart_config_t* USART_CONFIGx){
	// Result
	uint16_t data = 0;
	// Read the Data Register
	data = USART_CONFIGx->USARTx->DR.REG;
	// Return Result
	return data;
}

/**
 * @brief Transmits a string on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] str The character to be transmitted
 * @note '\0' is required for terminating sequence
 */
void USART_puts(usart_config_t* USART_CONFIGx, const char* str){
	// Termination Condition
	while(*str != '\0'){
		// Transmit the character
		USART_putc(USART_CONFIGx, *str);
		// Update the pointer to next position
		str++;
		// Delay
		for(volatile uint16_t local_delay = 0; local_delay < USARTx_STRING_TX_DELAY; local_delay++);
	}
}

/**
 * @brief Transmits formatted data on USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @param[in] format The formatted string
 * @note `float` decimal restricted max to 6 places
 */
void USART_printf(usart_config_t* USART_CONFIGx, const char* format, ...) {
	// Starts VA
	va_list args;
	va_start(args, format);
	// Data Present
	while (*format) {
		// Format Specifier Encountered
		if (*format == '%'){
			// Move to the next character
			format++;
			// Character
			if(*format == 'c'){
				// Handle character
				char c = (char)va_arg(args, int);
				USART_putc(USART_CONFIGx, c);
			}
			// String
			else if(*format == 's'){
				// Handle string
				char* str = va_arg(args, char*);
				while (*str) {
					USART_putc(USART_CONFIGx, *str++);
				}
			} 
			// Integer
			else if(*format == 'd'){
				// Handle integer
				int32_t num = va_arg(args, int);
				// Storing the integer value after converting it to character
				char buffer[10];
				// Buffer Index
				uint8_t i = 0;
				// Negative Number Indicator
				char isNegative = 0;
				// Negative Number
				if (num < 0) {
					isNegative = 1;
					num = -num;
				}
				// `int` to `char` (Reverse Storing)
				do {
					buffer[i++] = (num % 10) + '0';
					num /= 10;
				} while (num > 0);
				// Add negative sign if required
				if (isNegative) buffer[i++] = '-';
				// Print it in reverse order
				while (i > 0) {
					USART_putc(USART_CONFIGx, buffer[--i]);
				}
			}
			// Float Handling
			else if(*format == '.' || *format == 'f'){
				// Default precision
				uint8_t precision = 4;
				// Update Precision
				if(*format == '.'){
					// Go to next position
					format++;
					precision = (*format - '0');
					// Wrap precision if greater than 6 
					precision = (precision > 6)? 6 : precision;
					// Go to next position
					format++;
				}
				// Confirmation for float
				if(*format == 'f'){
					// Get float value
					float f = (float)va_arg(args, double);
					// Handle negative numbers
					uint8_t is_negative = 0;
					if(f < 0) {
						is_negative = 1;
						f = -f;
					}
					// Split into integer and fractional parts
					int32_t int_part = (int32_t)f;
					float frac_part = f - int_part;
					// Convert fractional part to fixed-point integer
					uint32_t frac_fixed = 0;
					for(uint8_t i = 0; i < precision; i++) {
						frac_part *= 10.0f;
						frac_fixed = frac_fixed * 10 + (uint32_t)frac_part;
						frac_part -= (uint32_t)frac_part;
					}
					// Print sign
					if(is_negative) 
						USART_putc(USART_CONFIGx, '-');
					// Print integer part
					char int_buf[12] = {'\0'};
					uint8_t idx = 0;
					do {
						int_buf[idx++] = (int_part % 10) + '0';
						int_part /= 10;
					} while(int_part > 0);
					// Print on the console
					while(idx > 0) {
						USART_putc(USART_CONFIGx, int_buf[--idx]);
					}
					// Print decimal point
					USART_putc(USART_CONFIGx, '.');
					// Print fractional part using fixed-point math
					char frac_buf[6] = {'\0'};
					for(uint8_t i = 0; i < precision; i++) {
						frac_buf[i] = (frac_fixed % 10) + '0';
						frac_fixed /= 10;
					}
					for(int8_t i = precision - 1; i >= 0; i--) {
						USART_putc(USART_CONFIGx, frac_buf[i]);
					}
				}
			}
			// Handle unknown format specifier
			else {
				const char* unknown_msg = "Unknown format specifier\n";
				while (*unknown_msg) {
					USART_putc(USART_CONFIGx, *unknown_msg++);
				}
			}
		}
		// Non-format specifier character
		else {
			USART_putc(USART_CONFIGx, *format);
		}
		// Go to next character
		format++;
	}
	// Ends the VA
	va_end(args);
}

/**
 * @brief Receives data using USART
 * @param[in] USART_CONFIGx USART Configuration Structure
 * @returns Data present in USARTx->DR
 * @note Polling Based Approach
 */
uint16_t USART_receive(usart_config_t* USART_CONFIGx){
	// Result
	uint16_t result = 0;
	// RXNE (Received data is ready to be read)
	while(!(USART_CONFIGx->USARTx->SR.REG & USART_SR_RXNE));
	// Read received data
	result = USART_getc(USART_CONFIGx);
	// Return Result
	return result;
}

/**
 * @brief Loads the default value for USART Struct
 * @param[in] USART_CONFIGx USART Configuration Structure
 */
void USART_load_default(usart_config_t* USART_CONFIGx){
	// Load default GPIO Configuration
	USART_CONFIGx->TX.MODE = GPIOx_MODE_OUT_50MHz;
	USART_CONFIGx->TX.CNF = GPIOx_CNF_OUT_AF_PP;
	USART_CONFIGx->RX.MODE = GPIOx_MODE_IN;
	USART_CONFIGx->RX.CNF = GPIOx_CNF_IN_FLOAT;
	// Set Baud Rate to 9600
	USART_CONFIGx->baud_rate = USARTx_BAUD_9600;
	// Set Stop Bit to 1
	USART_CONFIGx->stop_bits = USARTx_STOP_1_BIT;
	// Word Length
	USART_CONFIGx->word_length = USARTx_WORD_8_BITS;
	// USART Parity Disable
	USART_CONFIGx->enable_parity = USARTx_PARITY_DISABLE;
	// USART Parity Selection
	USART_CONFIGx->parity_selection = USARTx_PARITY_EVEN;
	// Disable Interrupts
	USART_CONFIGx->TXEIE = USARTx_TXEIE_DISABLE;
	USART_CONFIGx->RXNEIE = USARTx_RXNEIE_DISABLE;
	USART_CONFIGx->TCIE = USARTx_TCIE_DISABLE;
	// Enable TX
	USART_CONFIGx->TXE = USARTx_TX_ENABLE;
	// Enable RX
	USART_CONFIGx->RXE = USARTx_RX_ENABLE;
}

#else

// USART Driver Baud Rate Lookup Table
const static uint32_t __usartDriverBaudRateMapping__[] = {
	[USART_BAUD_9600] = 9600,
	[USART_BAUD_19200] = 19200,
	[USART_BAUD_38400] = 38400,
	[USART_BAUD_57600] = 57600,
	[USART_BAUD_115200] = 115200,
	[USART_BAUD_230400] = 230400,
	[USART_BAUD_460800] = 460800,
	[USART_BAUD_921600] = 921600,
};

/**
 * @brief USART Hardware Pins Configure
 * @param hardware Refer `usart_hardware_enable_t`
 * @param usartGpioConfig Refer `usart_gpio_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_GPIO_Config(const usart_hardware_enable_t hardware, usart_gpio_t* const usartGpioConfig){
	// Status
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	// Configure TX Pin
	if(hardware & USART_TX_ENABLE){
		status = GPIO_Init(usartGpioConfig->TX.GPIOx, usartGpioConfig->TX.pin, usartGpioConfig->TX.mode, usartGpioConfig->TX.config);
		ASSERT_DRIVER_STATUS(status);
	}
	// Configure RX Pin
	if(hardware & USART_RX_ENABLE){
		status = GPIO_Init(usartGpioConfig->RX.GPIOx, usartGpioConfig->RX.pin, usartGpioConfig->RX.mode, usartGpioConfig->RX.config);
		ASSERT_DRIVER_STATUS(status);
	}
	// Configure RTS Pin
	if(hardware & USART_RTS_ENABLE){
		status = GPIO_Init(usartGpioConfig->RTS.GPIOx, usartGpioConfig->RTS.pin, usartGpioConfig->RTS.mode, usartGpioConfig->RTS.config);
		ASSERT_DRIVER_STATUS(status);
	}
	// Configure CTS Pin
	if(hardware & USART_CTS_ENABLE){
		status = GPIO_Init(usartGpioConfig->CTS.GPIOx, usartGpioConfig->CTS.pin, usartGpioConfig->CTS.mode, usartGpioConfig->CTS.config);
		ASSERT_DRIVER_STATUS(status);
	}
	// Configure CK Pin
	if(hardware & USART_CK_ENABLE){
		status = GPIO_Init(usartGpioConfig->CK.GPIOx, usartGpioConfig->CK.pin, usartGpioConfig->CK.mode, usartGpioConfig->CK.config);
		ASSERT_DRIVER_STATUS(status);
	}
	// Status
	return status;
}

/**
 * @brief Set USART Baud Rate
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param baudRate Refer `usart_baud_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success 
 */
driver_status_t USART_BaudRate_Set(const usart_t usart, const usart_baud_t baudRate){
	// Get Clock Frequency
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	if((usart < USART_MIN) || (usart > USART_MAX))
		return status;
	uint32_t clockFreq = (usart == USART_1)? RCC_GetAPB2Clock() : RCC_GetBusFreq(RCC_APB1_BUS);
	// Update Baud Rate Register Value
	USART_Get_Mapping(usart)->BRR.REG = (uint32_t)(clockFreq/(__usartDriverBaudRateMapping__[baudRate]));
	// Return status
	status = DRIVER_STATUS_SUCCESS;
	return status;
}

/**
 * @brief Private function to update `USARTx->CR1` in input register as per hardware & data configuration
 * @param hardware Defines Hardware Feature Usage. Refer `usart_hardware_enable_t`
 * @param dataConfig Communication Standards for USART. Refer `usart_data_config_t`
 * @param reg Pointer to Register which contains the `USARTx->CR1` Register Value
 */
static void __USART_updateCR1__(const usart_hardware_enable_t hardware, const usart_data_config_t dataConfig, uint32_t *tempReg){
	// Temporary Variable
	uint8_t customDataConfig = 0x00;
	// Update TX status based on Configuration
	if(hardware & USART_TX_ENABLE){
		*tempReg |= USART_CR1_TE;
	}
	else{
		*tempReg &= ~USART_CR1_TE;
	}
	// Update RX status based on Configuration
	if(hardware & USART_RX_ENABLE){
		*tempReg |= USART_CR1_RE;
	}
	else{
		*tempReg &= ~USART_CR1_RE;
	}
	// Disable Parity Control & Even Parity Selection
	*tempReg &= ~(USART_CR1_PCE | USART_CR1_PS);
	// Determine Parity Bit Configuration
	customDataConfig = USART_EXTRACT_PARITY(dataConfig); 
	*tempReg |= (customDataConfig << USART_CR1_PS_Pos);
	// USART Data Bit Configuration
	*tempReg &= ~(USART_CR1_M);
	customDataConfig = USART_EXTRACT_DATA_BITS(dataConfig);
	*tempReg |= (customDataConfig << USART_CR1_M_Pos);
}

/**
 * @brief Private function to update `USARTx->CR2` in input register as per hardware & data configuration
 * @param hardware Defines Hardware Feature Usage. Refer `usart_hardware_enable_t`
 * @param dataConfig Communication Standards for USART. Refer `usart_data_config_t`
 * @param reg Pointer to Register which contains the `USARTx->CR2` Register Value
 */
static void __USART_updateCR2__(const usart_hardware_enable_t hardware, const usart_data_config_t dataConfig, uint32_t *tempReg){
	uint8_t customDataConfig = 0x00;
	// Update Clock Enable functionality
	*tempReg &= ~USART_CR2_CLKEN;
	if(hardware & USART_CK_ENABLE){
		*tempReg |= USART_CR2_CLKEN;
	}
	// Stop Bits Configuration
	*tempReg &= ~(USART_CR2_STOP_Msk);
	customDataConfig = USART_EXTRACT_STOP_BITS(dataConfig);
	*tempReg |= (customDataConfig << USART_CR2_STOP_Pos);
}

/**
 * @brief Sets the USART Communication Configuration
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param hardware Defines Hardware Feature Usage. Refer `usart_hardware_enable_t`
 * @param dataConfig Communication Standards for USART. Refer `usart_data_config_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success 
 */
driver_status_t USART_DataConfig_Set(const usart_t usart, const usart_hardware_enable_t hardware, const usart_data_config_t dataConfig){
	// Status
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	// Validate Parameters
	if((usart < USART_MIN) || (usart > USART_MAX))
		return status;
	uint32_t tempReg = 0x00000000;
	// Get USART Mapping 
	USART_TypeDef* USART = USART_Get_Mapping(usart);
	// Read USARTx->CR1
	tempReg = USART->CR1.REG;
	__USART_updateCR1__(hardware, dataConfig, &tempReg);
	// Write USARTx->CR1
	USART->CR1.REG = tempReg;
	// Read USARTx->CR2
	tempReg = USART->CR2.REG;
	__USART_updateCR2__(hardware, dataConfig, &tempReg);
	// Write USARTx->CR2
	USART->CR2.REG = tempReg;
	// Return status
	status = DRIVER_STATUS_SUCCESS;
	return status;
}

/**
 * @brief Configures the USART Module
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param usartConfig Pointer to USART Configuration Structure
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_Config(const usart_t usart, usart_config_t* const usartConfig){
	// Status
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	// Validate Parameters
	if((usart < USART_MIN) || (usart > USART_MAX) || (usartConfig == NULL)){
		return status;
	}
	// Enable Clock to USART
	__USART_enableClock__(usart);
	// Configure the GPIO
	usart_gpio_t* usartGpioConfig = USART_GPIO_Config_Get(usart);
	// Configure USART GPIO
	status = USART_GPIO_Config(usartConfig->hardware, usartGpioConfig);
	ASSERT_DRIVER_STATUS(status);
	// Set USART Baud Rate
	status = USART_BaudRate_Set(usart, usartConfig->baud_rate);
	ASSERT_DRIVER_STATUS(status);
	// Set USART Communication Configuration
	status = USART_DataConfig_Set(usart, usartConfig->hardware, usartConfig->config);
	ASSERT_DRIVER_STATUS(status);
	// Return status
	return status;
}

/**
 * @brief Enable USART Interrupts
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3` 
 * @param irq USART IRQ Combinations. Refer `usart_irq_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_IRQ_Enable(const usart_t usart, const usart_irq_t irq){
	// Status
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	USART_Get_Mapping(usart)->CR1.REG |= (uint32_t)((irq & 0x1F) << USART_CR1_IDLEIE_Pos);
	NVIC_IRQEnable(USART_Get_IRQn(usart));
	// Return Status
	status = DRIVER_STATUS_SUCCESS;
	return status;
}

/**
 * @brief Disables USART Interrupts
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3` 
 * @param irq USART IRQ Combinations. Refer `usart_irq_t`
 * @return Status of Driver Operation
 * @returns - DRIVER_STATUS_ERROR_FAIL: Failure
 * @returns - DRIVER_STATUS_SUCCESS: Success
 */
driver_status_t USART_IRQ_Disable(const usart_t usart, const usart_irq_t irq){
	// Status
	driver_status_t status = DRIVER_STATUS_ERROR_FAIL;
	USART_Get_Mapping(usart)->CR1.REG &= ~((uint32_t)((irq & 0x1F) << USART_CR1_IDLEIE_Pos));
	NVIC_IRQEnable(USART_Get_IRQn(usart));
	// Return status
	status = DRIVER_STATUS_SUCCESS;
	return status;
}

/**
 * @brief Ensuring precision & width in %X
 * @param format Pointer to pointer to string
 * @return Precision Value
 * @note Helper Function for `USART_printf()`
 */
static uint8_t __parse_precision__(const char** format){
	// Calculated precision value
    uint8_t precision = 0;
    if (**format == '.') {
        // Skip the '.'
		(*format)++;
        // Parse precision digits
        while (**format >= '0' && **format <= '9') {
            precision = precision * 10 + (**format - '0');
            (*format)++;
        }
    }
    // Return precision value
    return precision;
}

/**
 * @brief Transmits formatted data on USART
 * @param usart USART Instance: `USART_1`, `USART_2`, `USART_3`
 * @param format Formatted string
 * @note `float` decimal restricted max to 6 places
 */
void USART_printf(const usart_t usart, const char* format, ...){
	// Starts Variable Argument List
	va_list args;
	va_start(args, format);
	// Data Present
	while (*format) {
		// Format Specifier Encountered
		if(*format == '%'){
			// Move to the next character
			format++;
			// Character
			if(*format == 'c'){
				char c = (char)va_arg(args, int);
				USART_sendByte(usart, c);
			}
			// String
			else if(*format == 's'){
				char* str = va_arg(args, char*);
				// Send the whole string
				while (*str){
					USART_sendByte(usart, *str++);
				}
			} 
			// Integer
			else if(*format == 'd'){
				// Handle integer
				int32_t num = va_arg(args, int);
				// Storing the integer value after converting it to character
				char buffer[10];
				// Buffer Index
				uint8_t i = 0;
				// Negative Number Indicator
				char isNegative = 0;
				// Negative Number
				if (num < 0) {
					isNegative = 1;
					num = -num;
				}
				// `int` to `char` (Reverse Storing)
				do {
					buffer[i++] = (num % 10) + '0';
					num /= 10;
				} while (num > 0);
				// Add negative sign if required
				if (isNegative) buffer[i++] = '-';
				// Print it in reverse order
				while (i > 0) {
					USART_sendByte(usart, buffer[--i]);
				}
			}
			// Float Handling
			else if(*format == '.' || *format == 'f' || *format == 'X' || *format == 'x'){
				// Default precision
				uint8_t precision = 4;
				// Update Precision
				if(*format == '.'){
					// Go to next position
					format++;
					precision = (*format - '0');
					// Wrap precision if greater than 6 
					precision = (precision > 6)? 6 : precision;
					// Go to next position
					format++;
				}
				// Confirmation for float
				if(*format == 'f'){
					// Get float value
					float f = (float)va_arg(args, double);
					// Handle negative numbers
					uint8_t is_negative = 0;
					if(f < 0) {
						is_negative = 1;
						f = -f;
					}
					// Split into integer and fractional parts
					int32_t int_part = (int32_t)f;
					float frac_part = f - int_part;
					// Convert fractional part to fixed-point integer
					uint32_t frac_fixed = 0;
					for(uint8_t i = 0; i < precision; i++) {
						frac_part *= 10.0f;
						frac_fixed = frac_fixed * 10 + (uint32_t)frac_part;
						frac_part -= (uint32_t)frac_part;
					}
					// Print sign
					if(is_negative) 
						USART_sendByte(usart, '-');
					// Print integer part
					char int_buf[12] = {'\0'};
					uint8_t idx = 0;
					do {
						int_buf[idx++] = (int_part % 10) + '0';
						int_part /= 10;
					} while(int_part > 0);
					// Print on the console
					while(idx > 0) {
						USART_sendByte(usart, int_buf[--idx]);
					}
					// Print decimal point
					USART_sendByte(usart, '.');
					// Print fractional part using fixed-point math
					char frac_buf[6] = {'\0'};
					for(uint8_t i = 0; i < precision; i++) {
						frac_buf[i] = (frac_fixed % 10) + '0';
						frac_fixed /= 10;
					}
					for(int8_t i = precision - 1; i >= 0; i--) {
						USART_sendByte(usart, frac_buf[i]);
					}
				}
				// Hexadecimal
				else if(*format == 'X' || *format == 'x'){
					// Parse precision if present (e.g., %.4X)
					uint8_t precision = __parse_precision__(&format);
					// If no precision specified, default behavior
					if (precision == 0) {
						// Minimum 2 digit
						precision = 2;
					}
					uint32_t num = va_arg(args, uint32_t);
					char buffer[8] = {'0'};
					uint8_t i = 0;
					// Handle zero case with precision
					if (num == 0) {
						for (uint8_t j = 0; j < precision; j++) {
							buffer[i++] = '0';
						}
					} 
					else {
						// Convert to hexadecimal (reverse order)
						uint8_t digits_converted = 0;
						do {
							uint8_t digit = (num & 0x0F);
							buffer[i++] = (digit < 10) ? (digit + '0') : 
										((digit - 10) + ((*format == 'X') ? 'A' : 'a'));
							num >>= 4;
							digits_converted++;
						} while (num > 0);
						
						// Add leading zeros to meet precision requirement
						while (digits_converted < precision) {
							buffer[i++] = '0';
							digits_converted++;
						}
					}
					// Print in reverse order
					while(i > 0){
						USART_sendByte(usart, buffer[--i]);
					}
				}
				// Handle unknown format specifier
				else {
					const char* unknown_msg = "Unknown format specifier\n";
					while (*unknown_msg) {
						USART_sendByte(usart, *unknown_msg++);
					}
				}
			}
		}
		// Non-format specifier character
		else {
			USART_sendByte(usart, *format);
		}
		// Go to next character
		format++;
		// Ends the VA
		va_end(args);
	}
}

#endif /* __OLD_GPIO_METHOD__ */
