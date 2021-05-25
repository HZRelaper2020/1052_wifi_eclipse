/*
 * main_user.c
 *
 *  Created on: 2021年3月25日
 *      Author: nwz
 */
#include "fsl_sdio.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "sdmmc_config.h"
#include "fsl_common.h"
#include "led/bsp_led.h"
#include "sdmmc_config.h"
#include "libs/unimplement_int.h"

// 因为这个已经在  wlan_bus_sdio.c 中已经定义
static sdio_card_t g_sdio;

static void SDIO_DetectCallBack(bool isInserted, void *userData) {
	PRINTF("SDIO_DetectCallBack\n");
}

static void SDIO_CardInterruptCallBack(void *userData) {
	PRINTF("SDIO_CardInterruptCallBack");
}

static void LedLoop(void *pvParameters) {
	led_config();
	while (1) {
		vTaskDelay(500);
		set_led(0);
		vTaskDelay(500);
		set_led(1);
	}
}

void MySDIO_SetCardPower(sdio_card_t *card, bool enable) {
	gpio_pin_config_t WiFi_POWEr_config = { .direction = kGPIO_DigitalOutput,
			.outputLogic = enable ? 1 : 0, .interruptMode = kGPIO_NoIntmode };
	/* Initialize GPIO functionality on GPIO_AD_B0_00 (pin M14) */
	GPIO_PinInit(GPIO1, 0U, &WiFi_POWEr_config);
}

void scan_main(void);

static status_t InitBeforeSDIO() {
	sdio_card_t *card = &g_sdio;

	BOARD_SDIO_Config(card, NULL, BOARD_SDMMC_SDIO_HOST_IRQ_PRIORITY, NULL);

	MySDIO_SetCardPower(card, false);
	vTaskDelay(100);
	MySDIO_SetCardPower(card, true);
	vTaskDelay(100);
	card->currentTiming = kSD_TimingSDR25HighSpeedMode;

	return 0;
}
#include "lwip/init.h"
#include "lwip/pbuf.h"
static void InitSDIO(void *pvParameters) {

	host_platform_set_total(&g_sdio, InitBeforeSDIO, SDIO_Init,
			SDIO_SwitchToHighSpeed, SDIO_SetDataBusWidth, SDIO_IO_Transfer);

//	dhcp_main("nwztest","123456789");
	dhcp_main("test_rk3288", "123456789");
//	tcp_echo(3307);
	tcp_send_test("192.168.1.201",8837,100);
//	dhcp_main("Relaper-H3C-2.4G","hzrelaper");
	while (1) {
		vTaskDelay(1000);
	}
}
#include "fsl_clock.h"
//#include "cm_backtrace.h"
TaskHandle_t handle2;
TaskHandle_t handle1;

static void print_stack_usage(void *arg) {
	char buf[2048];
	while (1) {
		uint8_t c = DbgConsole_Getchar();
//		PRINTF("c is                                    0x%x\n",c);
		if (c == 13) {
			vTaskList(buf);
			PRINTF("%s", buf);
		}
	}
}

static void test2(void *arg) {
	char buf[10];

	int t = 0;
	while (1) {
//		int a = xTaskGetTickCount();
		PRINTF("2");
	}
}

static void lwip_init_ok(void *arg) {
	PRINTF("lwip ok\n");
	return;
//	LWIP_PLATFORM_ASSERT(0);
	for (int i=0;i<1;i++){
	struct pbuf *buf = pbuf_alloc(PBUF_LINK, 350, 0x280);
	PRINTF("\n\n%d\n",i);
	PRINTF("0x%x 0x%x %d\n", buf, buf->payload, buf->tot_len);
	if (0 != pbuf_add_header(buf, 14)) {
		ERROR("pbuf head failed\n");
		return;
	}
	PRINTF("0x%x 0x%x %d\n", buf, buf->payload, buf->tot_len);
	if (0 != pbuf_header(buf, -22)) {
		ERROR("pbuf head failed\n");
		return;
	}

	PRINTF("0x%x 0x%x %d\n", buf, buf->payload, buf->tot_len);
	}
}
#include "lwip/tcpip.h"
void main() {
	BOARD_ConfigMPU();
	BOARD_InitPins();

	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	NVIC_SetPriority(BOARD_UART_IRQ, 5U);
	NVIC_SetPriority(USDHC2_IRQn, 5U);

	tcpip_init(lwip_init_ok, NULL);
//	cm_backtrace_init("Wifi_SDIO_Test", "1.0", "1.0");
	if (pdPASS != xTaskCreate(LedLoop, "LedLoop", 512, NULL, 2, NULL)) {
		return;
	}

	if (pdPASS != xTaskCreate(InitSDIO, "InitSDIO", 8 * 4096, NULL, 2, NULL)) {
		return;
	}

	if (pdPASS
			!= xTaskCreate(print_stack_usage, "print_stack_usage", 2048, NULL,
					1, NULL)) {
		return;
	}

//	if (pdPASS != xTaskCreate(test2, "test2", 256, NULL, 4, NULL)) {
//		return;
//	}

	vTaskStartScheduler();

	while (1)
		PRINTF("1");
}
