/*
 * unimplement_int.c
 *
 *  Created on: 2021Äê3ÔÂ26ÈÕ
 *      Author: nwz
 */

#include "fsl_common.h"
#include "fsl_sdio.h"
#include "unimplement_int.h"
#include "fsl_debug_console.h"

int host_network_process_ethernet_data22(void *buf, void *interface) {
	PRINTF("receive data from host_network_process_ethernet_data\n");
	return 0;
}

int xTaskIsTaskFinished(void *thread) {
	eTaskState state = eTaskGetState(thread);
	PRINTF("state:%d\n", state);
	return state == eDeleted;
}
