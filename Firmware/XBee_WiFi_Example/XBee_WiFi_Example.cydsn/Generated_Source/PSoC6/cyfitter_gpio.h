/*******************************************************************************
* File Name: cyfitter_gpio.h
* 
* PSoC Creator  4.2
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2017 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_GPIO_H
#define INCLUDED_CYFITTER_GPIO_H
#include "cy_device_headers.h"

/* D7 */
#define D7_0_DRIVEMODE CY_GPIO_DM_PULLUP
#define D7_0_INBUF_ENABLED 1u
#define D7_0_INIT_DRIVESTATE 1u
#define D7_0_INIT_MUXSEL 0u
#define D7_0_INPUT_SYNC 2u
#define D7_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define D7_0_NUM 2u
#define D7_0_PORT GPIO_PRT0
#define D7_0_SLEWRATE CY_GPIO_SLEW_FAST
#define D7_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define D7_DRIVEMODE CY_GPIO_DM_PULLUP
#define D7_INBUF_ENABLED 1u
#define D7_INIT_DRIVESTATE 1u
#define D7_INIT_MUXSEL 0u
#define D7_INPUT_SYNC 2u
#define D7_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define D7_NUM 2u
#define D7_PORT GPIO_PRT0
#define D7_SLEWRATE CY_GPIO_SLEW_FAST
#define D7_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* D9 */
#define D9_0_DRIVEMODE CY_GPIO_DM_PULLUP
#define D9_0_INBUF_ENABLED 1u
#define D9_0_INIT_DRIVESTATE 1u
#define D9_0_INIT_MUXSEL 0u
#define D9_0_INPUT_SYNC 2u
#define D9_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define D9_0_NUM 1u
#define D9_0_PORT GPIO_PRT13
#define D9_0_SLEWRATE CY_GPIO_SLEW_FAST
#define D9_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define D9_DRIVEMODE CY_GPIO_DM_PULLUP
#define D9_INBUF_ENABLED 1u
#define D9_INIT_DRIVESTATE 1u
#define D9_INIT_MUXSEL 0u
#define D9_INPUT_SYNC 2u
#define D9_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define D9_NUM 1u
#define D9_PORT GPIO_PRT13
#define D9_SLEWRATE CY_GPIO_SLEW_FAST
#define D9_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* Red_LED */
#define Red_LED_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Red_LED_0_INBUF_ENABLED 0u
#define Red_LED_0_INIT_DRIVESTATE 0u
#define Red_LED_0_INIT_MUXSEL 0u
#define Red_LED_0_INPUT_SYNC 2u
#define Red_LED_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Red_LED_0_NUM 3u
#define Red_LED_0_PORT GPIO_PRT0
#define Red_LED_0_SLEWRATE CY_GPIO_SLEW_FAST
#define Red_LED_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define Red_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Red_LED_INBUF_ENABLED 0u
#define Red_LED_INIT_DRIVESTATE 0u
#define Red_LED_INIT_MUXSEL 0u
#define Red_LED_INPUT_SYNC 2u
#define Red_LED_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Red_LED_NUM 3u
#define Red_LED_PORT GPIO_PRT0
#define Red_LED_SLEWRATE CY_GPIO_SLEW_FAST
#define Red_LED_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_rx */
#define UART_rx_0_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_0_INBUF_ENABLED 1u
#define UART_rx_0_INIT_DRIVESTATE 1u
#define UART_rx_0_INIT_MUXSEL 18u
#define UART_rx_0_INPUT_SYNC 2u
#define UART_rx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_0_NUM 0u
#define UART_rx_0_PORT GPIO_PRT5
#define UART_rx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_rx_DRIVEMODE CY_GPIO_DM_HIGHZ
#define UART_rx_INBUF_ENABLED 1u
#define UART_rx_INIT_DRIVESTATE 1u
#define UART_rx_INIT_MUXSEL 18u
#define UART_rx_INPUT_SYNC 2u
#define UART_rx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_rx_NUM 0u
#define UART_rx_PORT GPIO_PRT5
#define UART_rx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_rx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* UART_tx */
#define UART_tx_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_0_INBUF_ENABLED 0u
#define UART_tx_0_INIT_DRIVESTATE 1u
#define UART_tx_0_INIT_MUXSEL 18u
#define UART_tx_0_INPUT_SYNC 2u
#define UART_tx_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_0_NUM 1u
#define UART_tx_0_PORT GPIO_PRT5
#define UART_tx_0_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define UART_tx_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define UART_tx_INBUF_ENABLED 0u
#define UART_tx_INIT_DRIVESTATE 1u
#define UART_tx_INIT_MUXSEL 18u
#define UART_tx_INPUT_SYNC 2u
#define UART_tx_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define UART_tx_NUM 1u
#define UART_tx_PORT GPIO_PRT5
#define UART_tx_SLEWRATE CY_GPIO_SLEW_FAST
#define UART_tx_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

/* Blue_LED */
#define Blue_LED_0_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Blue_LED_0_INBUF_ENABLED 0u
#define Blue_LED_0_INIT_DRIVESTATE 0u
#define Blue_LED_0_INIT_MUXSEL 0u
#define Blue_LED_0_INPUT_SYNC 2u
#define Blue_LED_0_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Blue_LED_0_NUM 1u
#define Blue_LED_0_PORT GPIO_PRT11
#define Blue_LED_0_SLEWRATE CY_GPIO_SLEW_FAST
#define Blue_LED_0_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS
#define Blue_LED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define Blue_LED_INBUF_ENABLED 0u
#define Blue_LED_INIT_DRIVESTATE 0u
#define Blue_LED_INIT_MUXSEL 0u
#define Blue_LED_INPUT_SYNC 2u
#define Blue_LED_INTERRUPT_MODE CY_GPIO_INTR_DISABLE
#define Blue_LED_NUM 1u
#define Blue_LED_PORT GPIO_PRT11
#define Blue_LED_SLEWRATE CY_GPIO_SLEW_FAST
#define Blue_LED_THRESHOLD_LEVEL CY_GPIO_VTRIP_CMOS

#endif /* INCLUDED_CYFITTER_GPIO_H */
