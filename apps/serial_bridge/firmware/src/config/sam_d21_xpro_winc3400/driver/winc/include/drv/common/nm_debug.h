/*******************************************************************************
  File Name:
    nm_debug.h

  Summary:
    This module contains debug API declarations.

  Description:
    This module contains debug API declarations.
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

#ifndef _NM_DEBUG_H_
#define _NM_DEBUG_H_

#include "wdrv_winc_debug.h"

/**
 * @defgroup DebugDefines DebugDefines
 * @ingroup WlanDefines
 */

/**@{*/

#define M2M_ERR(...) WDRV_DBG_ERROR_PRINT(__VA_ARGS__)
#define M2M_INFO(...) WDRV_DBG_INFORM_PRINT(__VA_ARGS__)
#define M2M_DBG(...) WDRV_DBG_VERBOSE_PRINT(__VA_ARGS__)
#define M2M_PRINT(...) WDRV_DBG_VERBOSE_PRINT(__VA_ARGS__)

/**@}*/

#endif /* _NM_DEBUG_H_ */