#ifndef APP_INIT_H_
#define APP_INIT_H_

#include "stm32f1xx_data_types.h"

/**
 * @brief Initializes the hardware services explicitly selected by the application
 * @returns @ref driver_status_t "Application initialization status"
 * @retval - @ref `DRIVER_STATUS_SUCCESS`: Every enabled application service was initialized
 * @retval - @ref `DRIVER_STATUS_ERROR_INVALID_ARG`: An enabled service configuration was invalid
 * @retval - @ref `DRIVER_STATUS_ERROR_STATE`: An enabled service hardware precondition was not satisfied
 * @retval - @ref `DRIVER_STATUS_ERROR_TIMEOUT`: Clock or peripheral initialization timed out
 * @retval - @ref `DRIVER_STATUS_ERROR`: Hardware state could not be decoded during initialization
 */
driver_status_t App_Init(void);

#endif /* APP_INIT_H_ */
