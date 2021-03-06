/*************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *           Copyright 2014 Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 *************************************************************
 *
 * SFP Management Interface.
 *
 ************************************************************/
#ifndef __ONLP_SFP_H__
#define __ONLP_SFP_H__

#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include <AIM/aim_bitmap.h>
#include <AIM/aim_pvs.h>
#include <sff/sff.h>

/* <auto.start.enum(onlp_sfp_status).define> */
/** onlp_sfp_status */
typedef enum onlp_sfp_status_e {
    ONLP_SFP_STATUS_TX_FAILURE = (1 << 0),
    ONLP_SFP_STATUS_RX_LOS = (1 << 1),
} onlp_sfp_status_t;
/* <auto.end.enum(onlp_sfp_status).define> */


/**
 * Initialize the SFP subsystem.
 */
int onlp_sfp_init(void);

/**
 * Valid SFP Port bitmaps are communicated using this type.
 */
typedef aim_bitmap256_t onlp_sfp_bitmap_t;

/**
 * @brief Get the set of valid {Q}SFP ports.
 * @param bmap Returns the valid set of SFP-capable port numbers.
 */
int onlp_sfp_bitmap_get(onlp_sfp_bitmap_t* bmap);

/**
 * @brief Determine if a given port number is a valid SFP port.
 * @param port The port number.
 */
int onlp_sfp_port_valid(int port);

/**
 * @brief Determine if an SFP is currently plugged in.
 * @param port The SFP port number.
 * @returns 1 if an SFP is present.
 * @returns 0 if an SFP is not present.
 * @returns <0 on error.
 */
int onlp_sfp_is_present(int port);

/**
 * @brief Read IEEE standard EEPROM data from the given port.
 * @param port The SFP Port
 * @param rv Receives a buffer containing the EEPROM data.
 * @notes The buffer must be freed after use.
 * @returns The size of the eeprom data, if successful
 * @returns -1 on error.
 */
int onlp_sfp_eeprom_read(int port, uint8_t** rv);

/**
 * @brief Reset the SFP on the given port.
 * @param port The SFP port.
 */
int onlp_sfp_reset(int port);

/**
 * @brief Reset all SFP ports.
 */
int onlp_sfp_reset_all(void);

/**
 * @brief Deinitialize the SFP subsystem.
 */
int onlp_sfp_denit(void);

/**
 * @brief Set the enable state on the given SFP.
 * @param port The SFP port.
 * @param enable The new enable state.
 */
int onlp_sfp_enable_set(int port, int enable);

/**
 * @brief Get the enable state of the given SFP.
 * @param port The SFP port.
 * @param [out] enable Receives the enable state.
 */
int onlp_sfp_enable_get(int port, int* enable);

typedef void (onlp_sfp_event_handler_f)(int port, void* cookie);

/**
 * @brief Register for notifications on SFP events.
 * @param handler The event handler.
 * @param cookie The cookie passed to the handler.
 */
int onlp_sfp_event_register(onlp_sfp_event_handler_f hander, void* cookie);

/**
 * @brief Start or stop event processing.
 */
int onlp_sfp_events_enable_set(int enable);

/**
 * @brief Query event processing status.
 */
int onlp_sfp_events_enable_get(int* enable);

/**
 * @brief Dump the status of all SFPs
 * @param pvs The output pvs.
 */
void onlp_sfp_dump(aim_pvs_t* pvs);

/**
 * @brief Issue an ioctl to the SFP interface.
 * @param port The port.
 * @param ... Ioctl arguments.
 */
int onlp_sfp_ioctl(int port, ...);

/**
 * @brief Call the SFP post-insertion handler.
 *
 */
int onlp_sfp_post_insert(int port, sff_info_t* info);

/**
 * @brief Retrieve the SFP status flags.
 * @param port The port.
 * @param [out] flags Receives the flags.
 * @note See onlp_sfp_status_t
 */
int onlp_sfp_status_get(int port, uint32_t* flags);


#endif /* __ONLP_SFP_H__ */
