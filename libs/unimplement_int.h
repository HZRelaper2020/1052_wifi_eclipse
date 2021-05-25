/*
 * unimplement_int.h
 *
 *  Created on: 2021Äê3ÔÂ26ÈÕ
 *      Author: nwz
 */

#ifndef LIBS_UNIMPLEMENT_INT_H_
#define LIBS_UNIMPLEMENT_INT_H_

#include "fsl_sdio.h"
#define  wwd_result_t int

int host_platform_set_total(sdio_card_t* sdio,
		status_t (*sdio_before_init)(),
		status_t (*sdio_init)(sdio_card_t *),
		status_t (*sdio_switch_highspeed)(sdio_card_t* ),
		status_t (*sdio_set_buswidth)(sdio_card_t* ,sdio_bus_width_t ),
		status_t (*sdio_transfer)(sdio_card_t *card,
                          sdio_command_t cmd,
                          uint32_t argument,
                          uint32_t blockSize,
                          uint8_t *txData,
                          uint8_t *rxData,
                          uint16_t dataSize,
                          uint32_t *response));

wwd_result_t wwd_buffer_init(void*);
wwd_result_t wwd_management_wifi_on(int);

void dhcp_main(uint8_t* ssid,uint8_t* password);
#endif /* LIBS_UNIMPLEMENT_INT_H_ */
