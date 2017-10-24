
/*******************************************************************************
* File Name: cyfitter_cfg.c
* 
* PSoC Creator  4.1
*
* Description:
* This file contains device initialization code.
* Except for the user defined sections in CyClockStartupError(), this file should not be modified.
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2017 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "gpio/cy_gpio.h"
#include "syslib/cy_syslib.h"
#include "cyfitter_cfg.h"
#include "cyapicallbacks.h"
#include "sysclk/cy_sysclk.h"
#include "systick/cy_systick.h"

#define CY_NEED_CYCLOCKSTARTUPERROR 1


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #ifndef CY_CFG_SECTION
        #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    #endif
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif

#ifndef CYCODE
    #define CYCODE
#endif
#ifndef CYDATA
    #define CYDATA
#endif
#ifndef CYFAR
    #define CYFAR
#endif
#ifndef CYXDATA
    #define CYXDATA
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}




/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u
#define CYCLOCKSTART_FLL_ERROR   4u


#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

#ifdef CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK
    CY_CFG_Clock_Startup_ErrorCallback();
#else
    while(1) {}
#endif /* CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK */
}
#endif

void ClockInit(void);
void ClockInit(void)
{
	uint32_t status;

	/* Enable all source clocks */
	Cy_SysClk_LfClkSetSource(CY_SYSCLK_LFCLK_IN_ILO);

	/* Configure CPU clock dividers */
	Cy_SysClk_FastClkSetDivider(0u);
	Cy_SysClk_PeriClkSetDivider(1u);
	Cy_SysClk_SlowClkSetDivider(0u);

	/* Configure LF & HF clocks */
	Cy_SysClk_HfClockSetSource(0u, CY_SYSCLK_HFCLK_IN_CLKPATH0);
	Cy_SysClk_HfClockSetDivider(0u, CY_SYSCLK_HFCLK_NO_DIVIDE);
	Cy_SysClk_ClkHfEnable(0u);

	/* Configure Path Clocks */
	Cy_SysClk_ClkPathSetSource(0, CY_SYSCLK_CLKPATH_IN_IMO);
	Cy_SysClk_ClkPathSetSource(1, CY_SYSCLK_CLKPATH_IN_IMO);
	Cy_SysClk_ClkPathSetSource(2, CY_SYSCLK_CLKPATH_IN_IMO);
	{
		const cy_stc_fll_manual_config_t fllConfig = 
		{
			.fllMult =         1825u,
			.refDiv =          73u,
			.ccoRange =        CY_SYSCLK_FLL_CCO_RANGE4,
			.enableOutputDiv = true,
			.lockTolerance =   20u,
			.igain =           7u,
			.pgain =           5u,
			.settlingCount =   8u,
			.outputMode =      CY_SYSCLK_FLLPLL_OUTPUT_AUTO
		};
		status = Cy_SysClk_FllManualConfigure(&fllConfig);
		if (CY_RET_SUCCESS != status)
		{
			CyClockStartupError(CYCLOCKSTART_FLL_ERROR);
		}
	}
	status = Cy_SysClk_FllEnable(10000u);
	if (CY_RET_SUCCESS != status)
	{
		CyClockStartupError(CYCLOCKSTART_FLL_ERROR);
	}

	/* Configure miscellaneous clocks */
	Cy_SysClk_ClkTimerSetSource(CY_SYSCLK_CLKTIMER_IN_IMO);
	Cy_SysClk_ClkTimerSetDivider(0);
	Cy_SysClk_ClkTimerEnable();
	Cy_SysClk_ClkPumpSetSource(CY_SYSCLK_PUMP_IN_CLKPATH0);
	Cy_SysClk_ClkPumpSetDivider(CY_SYSCLK_PUMP_NO_DIV);
	Cy_SysClk_ClkPumpEnable();
	Cy_SysClk_ClkBakSetSource(CY_SYSCLK_BAK_IN_CLKLF);
	Cy_SysTick_SetClockSource(CY_SYSTICK_CLOCK_SOURCE_CLK_LF);
	Cy_SysClk_IloEnable();

	/* Set memory wait states based on 100 MHz HFClk[0] */
	Cy_SysLib_SetWaitStates(false, 100);

	/* Configure peripheral clock dividers */
	Cy_SysClk_PeriphAssignDivider(PCLK_SCB5_CLOCK, CY_SYSCLK_DIV_16_BIT, 0u);
	Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 0u, 433u);
	Cy_SysClk_PeriphPhaseAlignDivider(CY_SYSCLK_DIV_16_BIT, 0u, CY_SYSCLK_DIV_24_5_BIT, 0xFF);
	Cy_SysClk_PeriphAssignDivider(PCLK_SCB6_CLOCK, CY_SYSCLK_DIV_8_BIT, 0u);
	Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_8_BIT, 0u, 6u);
	Cy_SysClk_PeriphPhaseAlignDivider(CY_SYSCLK_DIV_8_BIT, 0u, CY_SYSCLK_DIV_24_5_BIT, 0xFF);
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
}

#define CY_AMUX_UNUSED CYREG_CPUSS_CM0_STATUS


/*******************************************************************************
* Function Name: Cy_SystemInit
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/

void Cy_SystemInit(void)
{
	/* Set worst case memory wait states (150 MHz), ClockInit() will update */
	Cy_SysLib_SetWaitStates(false, 150);

	/* Pin6_6 configuration */
	{
	    const cy_stc_gpio_pin_config_t pin6_6_cfg =
	    {
	        .outVal    = 0x00,
	        .driveMode = 0x06,
	        .hsiom     = P6_6_CPUSS_SWJ_SWDIO_TMS,
	    };
	    Cy_GPIO_Pin_Init(GPIO_PRT6, 6, &pin6_6_cfg);
	}

	/* Pin6_7 configuration */
	{
	    const cy_stc_gpio_pin_config_t pin6_7_cfg =
	    {
	        .outVal    = 0x00,
	        .driveMode = 0x06,
	        .hsiom     = P6_7_CPUSS_SWJ_SWCLK_TCLK,
	    };
	    Cy_GPIO_Pin_Init(GPIO_PRT6, 7, &pin6_7_cfg);
	}

	/* Clock */
	ClockInit();

	/* Port0 configuration */
	{
	    const cy_stc_gpio_prt_config_t port0_cfg =
	    {
	        .out        = 0x00000008,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x00666866,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x00000000,
	        .sel1Active = 0x00000000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT0, &port0_cfg);
	}

	/* Port5 configuration */
	{
	    const cy_stc_gpio_prt_config_t port5_cfg =
	    {
	        .out        = 0x00000003,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x00000068,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x00001212,
	        .sel1Active = 0x00000000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT5, &port5_cfg);
	}

	/* Port6 configuration */
	{
	    const cy_stc_gpio_prt_config_t port6_cfg =
	    {
	        .out        = 0x00000000,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x66000000,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x00000000,
	        .sel1Active = 0x1D1D0000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT6, &port6_cfg);
	}

	/* Port11 configuration */
	{
	    const cy_stc_gpio_prt_config_t port11_cfg =
	    {
	        .out        = 0x00000002,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x00000060,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x00000000,
	        .sel1Active = 0x00000000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT11, &port11_cfg);
	}

	/* Port12 configuration */
	{
	    const cy_stc_gpio_prt_config_t port12_cfg =
	    {
	        .out        = 0x0000000F,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x00008868,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x14141414,
	        .sel1Active = 0x00000000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT12, &port12_cfg);
	}

	/* Port13 configuration */
	{
	    const cy_stc_gpio_prt_config_t port13_cfg =
	    {
	        .out        = 0x00000000,
	        .intrMask   = 0x00000000,
	        .intrCfg    = 0x00000000,
	        .cfg        = 0x00000080,
	        .cfgIn      = 0x00000000,
	        .cfgOut     = 0x00000000,
	        .cfgSIO     = 0x00000000,
	        .sel0Active = 0x00000000,
	        .sel1Active = 0x00000000,
	    };
	    Cy_GPIO_Port_Init(GPIO_PRT13, &port13_cfg);
	}


	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

}