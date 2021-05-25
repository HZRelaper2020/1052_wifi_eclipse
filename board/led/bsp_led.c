/*
 * bsp_led.c
 *
 *  Created on: 2021Äê1ÔÂ5ÈÕ
 *      Author: nwz
 */


#include "bsp_led.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"

static int g_times =0 ;
static int g_currenttimes = 0;
static int g_on = 0;

void led_config(void)
{
	  gpio_pin_config_t gpio1_pinF14_config = {
	      .direction = kGPIO_DigitalOutput,
	      .outputLogic = 0U,
	      .interruptMode = kGPIO_NoIntmode
	  };
	  /* Initialize GPIO functionality on GPIO_AD_B0_09 (pin F14) */
	  GPIO_PinInit(GPIO1, 9U, &gpio1_pinF14_config);

	  IOMUXC_SetPinMux(
	      IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,        /* GPIO_AD_B0_09 is configured as GPIO1_IO09 */
	      0U);
}

void set_led(int on)
{
	GPIO_PinWrite(GPIO1, 9, on);
}

void set_led_loop(int times)
{
	if (g_times != times){
		g_times = times;
		g_currenttimes=0;
	}else{
		g_currenttimes++;
		if (g_currenttimes > g_times){
			g_currenttimes = 0;
			g_on = !g_on;
			set_led(g_on);
		}
	}
}
