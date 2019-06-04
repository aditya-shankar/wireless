/*******************************************************************************
  This module contains WINC3400 SPI protocol bus APIs implementation.

  File Name:
    nmspi.h

  Summary:
    This module contains WINC3400 SPI protocol bus APIs implementation.

  Description:
    This module contains WINC3400 SPI protocol bus APIs implementation.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc. All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

#ifndef _NMSPI_H_
#define _NMSPI_H_

#include "nm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @fn         nm_spi_init
 *  @brief      Initialize the SPI
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
*/
int8_t nm_spi_init(void);

/**
*   @fn     nm_spi_lock_init
*   @brief  Initialize the SPI lock
*   @return None
*/
void nm_spi_lock_init(void);

/**
 *  @fn         nm_spi_reset
 *  @brief      Reset the SPI
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_reset(void);

/**
 *  @fn         nm_spi_deinit
 *  @brief      DeInitialize the SPI
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_deinit(void);

/**
 *  @fn         nm_spi_read_reg
 *  @brief      Read register
 *  @param[in]  u32Addr
 *                  Register address
 *  @return     Register value
 */
uint32_t nm_spi_read_reg(uint32_t u32Addr);

/**
 *  @fn         nm_spi_read_reg_with_ret
 *  @brief      Read register with error code return
 *  @param[in]  u32Addr
 *                  Register address
 *  @param[out] pu32RetVal
 *                  Pointer to u32 variable used to return the read value
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_read_reg_with_ret(uint32_t u32Addr, uint32_t* pu32RetVal);

/**
 *  @fn         nm_spi_write_reg
 *  @brief      Write register
 *  @param[in]  u32Addr
 *                  Register address
 *  @param[in]  u32Val
 *                  Value to be written to the register
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_write_reg(uint32_t u32Addr, uint32_t u32Val);

/**
 *  @fn         nm_spi_read_block
 *  @brief      Read block of data
 *  @param[in]  u32Addr
 *                  Start address
 *  @param[out] puBuf
 *                  Pointer to a buffer used to return the read data
 *  @param[in]  u16Sz
 *                  Number of bytes to read. The buffer size must be >= u16Sz
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_read_block(uint32_t u32Addr, uint8_t *puBuf, uint16_t u16Sz);

/**
 *  @fn         nm_spi_write_block
 *  @brief      Write block of data
 *  @param[in]  u32Addr
 *                  Start address
 *  @param[in]  puBuf
 *                  Pointer to the buffer holding the data to be written
 *  @param[in]  u16Sz
 *                  Number of bytes to write. The buffer size must be >= u16Sz
 *  @return     @ref M2M_SUCCESS in case of success and @ref M2M_ERR_BUS_FAIL in case of failure
 */
int8_t nm_spi_write_block(uint32_t u32Addr, uint8_t *puBuf, uint16_t u16Sz);

#ifdef __cplusplus
}
#endif

#endif /* _NMSPI_H_ */