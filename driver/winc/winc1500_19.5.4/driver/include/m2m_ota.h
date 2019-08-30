/*******************************************************************************
  WINC1500 OTA Upgrade API Interface

  File Name:
    m2m_ota.h

  Summary:
    WINC1500 OTA Upgrade API Interface

  Description:
    WINC1500 OTA Upgrade API Interface
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef __M2M_OTA_H__
#define __M2M_OTA_H__

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "nm_common.h"
#include "m2m_types.h"
#include "nmdrv.h"

/**@addtogroup WlanEnums DataTypes
 * @ingroup m2m_wifi
 */
 /* @{ */


/*!
@typedef void (*tpfOtaNotifCb) (tstrOtaUpdateInfo *);

@brief
        A callback to get notification about a potential OTA update.

@param[in] pstrOtaUpdateInfo
        A structure to provide notification payload.
@sa
    tstrOtaUpdateInfo
@warning
        The notification is not supported (Not implemented yet)

*/
typedef void (*tpfOtaNotifCb) (tstrOtaUpdateInfo * pstrOtaUpdateInfo);


/*!
@typedef void (*tpfOtaUpdateCb) (uint8_t u8OtaUpdateStatusType ,uint8_t u8OtaUpdateStatus);

@brief
   A callback to get OTA status update, the callback provide the status type and its status.
   The OTA callback provides the download status, the switch to the downloaded firmware status and roll-back status.

@param[in] u8OtaUpdateStatusType Possible values are listed in tenuOtaUpdateStatusType.

@param[in] u8OtaUpdateStatus Possible values are listed as enumerated by @ref tenuOtaUpdateStatus.

@see
    tenuOtaUpdateStatusType
    tenuOtaUpdateStatus
 */
typedef void (*tpfOtaUpdateCb) (uint8_t u8OtaUpdateStatusType ,uint8_t u8OtaUpdateStatus);
 /**@}*/
/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
FUNCTION PROTOTYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifdef __cplusplus
     extern "C" {
#endif

/** @defgroup OtaInitFn m2m_ota_init
 *  @ingroup WLANAPI
* Synchronous initialization function for the OTA layer by registering the update callback.
* The notification callback is not supported at the current version. Calling this API is a
* MUST for all the OTA API's.

 */
 /**@{*/
/*!
@fn \
    int8_t  m2m_ota_init(tpfOtaUpdateCb  pfOtaUpdateCb,tpfOtaNotifCb  pfOtaNotifCb)

@param [in] pfOtaUpdateCb
                OTA Update callback function

@param [in] pfOtaNotifCb
                OTA notify callback function

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t  m2m_ota_init(tpfOtaUpdateCb  pfOtaUpdateCb,tpfOtaNotifCb  pfOtaNotifCb);
 /**@}*/

 /** @defgroup OtaNotifStFn m2m_ota_notif_set_url
 *  @ingroup WLANAPI
 * Set the OTA notification server URL, the functions need to be called before any check for update
 */
 /**@{*/
/*!
@fn \
    int8_t  m2m_ota_notif_set_url(uint8_t * u8Url);

@param [in] u8Url
             Set the OTA notification server URL, the functions need to be called before any check for update.
@warning
            Calling m2m_ota_init is required
            Notification Server is not supported in the current version (function is not implemented)
@see
            m2m_ota_init
@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t  m2m_ota_notif_set_url(uint8_t * u8Url);
 /**@}*/
 /** @defgroup OtaNotifCheckFn m2m_ota_notif_check_for_update
 *  @ingroup WLANAPI
 * Synchronous function to check for the OTA update using the Notification Server
 * URL. Function is not implemented (not supported at the current version)
 *
 */
  /**@{*/
/*!
@fn \
    int8_t  m2m_ota_notif_check_for_update(void);

@warning
        Function is not implemented (not supported at the current version)

@sa
            m2m_ota_init
            m2m_ota_notif_set_url
@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t  m2m_ota_notif_check_for_update(void);
 /**@}*/
 /** @defgroup OtaSched m2m_ota_notif_sched
*  @ingroup WLANAPI
* Schedule OTA notification Server check for update request after specific number of days
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_notif_sched(uint32_t u32Period);


@param [in] u32Period
            Period in days

@sa
        m2m_ota_init
        m2m_ota_notif_check_for_update
        m2m_ota_notif_set_url
@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_notif_sched(uint32_t u32Period);
  /**@}*/
/** @defgroup OtaStartUpdatefn m2m_ota_start_update
*  @ingroup WLANAPI
*   Request OTA start update using the downloaded URL, the OTA module will download the OTA image and ensure integrity of the image,
*   and update the validity of the image in control structure. Switching to that image requires calling @ref m2m_ota_switch_firmware API.
*   As a prerequisite @ref m2m_ota_init should be called before using @ref m2m_ota_start().
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_start_update(uint8_t * u8DownloadUrl);

@param [in] u8DownloadUrl
        The download firmware URL, you get it from device info according to the application server

@warning
    Calling this API does not guarantee OTA WINC image update, It depends on the connection with the download server and the validity of the image.
    If the API response is failure this may invalidate the roll-back image if it was previously valid, since the WINC does not have any internal memory
    except the flash roll-back image location to validate the downloaded image from

@see
        m2m_ota_init
        tpfOtaUpdateCb

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
\section Example
   The example shows an example of how the OTA image update is carried out.
@code
static void OtaUpdateCb(uint8_t u8OtaUpdateStatusType ,uint8_t u8OtaUpdateStatus)
{
    if(u8OtaUpdateStatusType == DL_STATUS) {
        if(u8OtaUpdateStatus == OTA_STATUS_SUCCESS) {
            //switch to the upgraded firmware
            m2m_ota_switch_firmware();
        }
    }
    else if(u8OtaUpdateStatusType == SW_STATUS) {
        if(u8OtaUpdateStatus == OTA_STATUS_SUCCESS) {
            M2M_INFO("Now OTA successfully done");
            //start the host SW upgrade then system reset is required (Reinitialize the driver)
        }
    }
}
void wifi_event_cb(uint8_t u8WiFiEvent, void * pvMsg)
{
    case M2M_WIFI_REQ_DHCP_CONF:
    {
        //after successfully connection, start the over air upgrade
        m2m_ota_start_update(OTA_URL);
    }
    break;
    default:
    break;
}
int main (void)
{
    tstrWifiInitParam param;
    tstr1xAuthCredentials gstrCred1x    = AUTH_CREDENTIALS;
    nm_bsp_init();

    memset((uint8_t*)&param, 0, sizeof(param));
    param.pfAppWifiCb = wifi_event_cb;

    //Initialize the WINC Driver
    ret = m2m_wifi_init(&param);
    if (M2M_SUCCESS != ret)
    {
        M2M_ERR("Driver Init Failed <%d>\n",ret);
        while(1);
    }
    //Initialize the OTA module
    m2m_ota_init(OtaUpdateCb,NULL);
    //connect to AP that provide connection to the OTA server
    m2m_wifi_default_connect();

    while(1)
    {

        //Handle the app state machine plus the WINC event handler
        while(m2m_wifi_handle_events(NULL) != M2M_SUCCESS) {

        }

    }
}
@endcode

*/
int8_t m2m_ota_start_update(uint8_t * u8DownloadUrl);
    /**@}*/
/** @defgroup OtaStartUpdatefn m2m_ota_start_update_crt
*  @ingroup WLANAPI
*   Request OTA start for cortus application image using the downloaded URL, the OTA module will download the OTA image and ensure integrity of the image,
*   and update the validity of the image in control structure. Switching to that image requires calling @ref m2m_ota_switch_crt API.
*   As a prerequisite @ref m2m_ota_init should be called before using @ref m2m_ota_start_update_crt().
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_start_update_crt(uint8_t * u8DownloadUrl);

@param [in] u8DownloadUrl
        The cortus application image url.
@warning
    Calling this API does not guarantee cortus application image update, It depends on the connection with the download server and the validity of the image.
    If the API response is failure this may invalidate the roll-back image if it was previously valid, since the WINC does not have any internal memory
    except the flash roll-back image location to validate the downloaded image from

@see
        m2m_ota_init
        tpfOtaUpdateCb

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_start_update_crt(uint8_t * u8DownloadUrl);
  /**@}*/
/** @defgroup OtaRollbackfn m2m_ota_rollback
*  @ingroup WLANAPI
    Request OTA Roll-back to the old (other) WINC image, the WINC firmware will check the validation of the Roll-back image
    and switch to it if it is valid.
    If the API response is success, system restart is required (re-initialize the driver with hardware rest) update the host driver version may
    be required if it is did not match the minimum version supported by the  WINC firmware.

*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_rollback(void);

@sa
    m2m_ota_init
    m2m_ota_start_update

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_rollback(void);
    /**@}*/
/** @defgroup OtaRollbackfn m2m_ota_rollback_crt
*  @ingroup WLANAPI
    Request Cortus application OTA Roll-back to the old (other) cortus application image, the WINC firmware will check the validation of the Roll-back image
    and switch to it if it is valid.
    If the API response is success, system restart is required (re-initialize the driver with hardware rest) update the host driver version may
    be required.

*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_rollback_crt(void);

@sa
    m2m_ota_init
    m2m_ota_start_update_crt

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_rollback_crt(void);
  /**@}*/
/** @defgroup OtaAbortfn m2m_ota_abort
*  @ingroup WLANAPI
    Request abort of current OTA download.
    The WINC firmware will terminate the OTA download if one is in progress.
    If no download is in progress, the API will respond with failure.
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_abort(void);

@return
    The function returns @ref M2M_SUCCESS for successful operation and a negative value otherwise.
*/
int8_t m2m_ota_abort(void);
  /**@}*/
  /**@}*/
/** @defgroup OtaSwitchFirmware m2m_ota_switch_firmware
*  @ingroup WLANAPI
* Switch to the upgraded Firmware, that API will update the control structure working image to the upgraded image
  take effect will be on the next system restart
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_switch_firmware(void);

@warning
   It is important to note that if the API succeeds, system restart is required (re-initializing the driver with hardware reset) updating the host driver version may be required
   if it does not match the minimum driver version supported by the WINC's firmware.
@sa
    m2m_ota_init
    m2m_ota_start_update

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_switch_firmware(void);
  /**@}*/
  /**@}*/
/** @defgroup OtaSwitchFirmware m2m_ota_switch_crt
*  @ingroup WLANAPI
* Switch to the upgraded cortus application, that API will update the control structure working image to the upgraded image
  take effect will be on the next system restart
*/
  /**@{*/
/*!
@fn \
    int8_t m2m_ota_switch_firmware(void);

@warning
   It is important to note that if the API succeeds, system restart is required (re-initializing the driver with hardware reset) updating the host driver version may be required
   if it does not match the minimum driver version supported by the WINC's firmware.
@sa
    m2m_ota_init
    m2m_ota_start_update_crt

@return
    The function returns @ref M2M_SUCCESS for successful operations  and a negative value otherwise.
*/
int8_t m2m_ota_switch_crt(void);
/*!
@fn \
    int8_t m2m_ota_get_firmware_version(void);

@brief
    Get the OTA Firmware version.

@return
    The function SHALL return 0 for success and a negative value otherwise.
*/
int8_t m2m_ota_get_firmware_version(tstrM2mRev *pstrRev);
  /**@}*/
int8_t m2m_ota_test(void);

#ifdef __cplusplus
}
#endif
#endif /* __M2M_OTA_H__ */
