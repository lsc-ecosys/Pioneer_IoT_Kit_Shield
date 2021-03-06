/*******************************************************************************
* File Name: common.h
*
* Version 1.0
*
* Description:
*  Contains the function prototypes and constants for the example
*  project.
*
********************************************************************************
* Copyright 2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef COMMON_H
#define COMMON_H
    
#include <project.h>
#include <stdio.h>

#define PRINT_DEVICE_INFO(NUM, BD_ADRES, CONN_HANDLE, ROLE)                                                        \
                        DBG_PRINTF("%lx. address: %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x bdHandle:%x attId:%x %s \r\n", NUM,\
                                                     BD_ADRES.bdAddr[5u], BD_ADRES.bdAddr[4u], BD_ADRES.bdAddr[3u],\
                                                     BD_ADRES.bdAddr[2u], BD_ADRES.bdAddr[1u], BD_ADRES.bdAddr[0u],\
                                                     CONN_HANDLE.bdHandle, CONN_HANDLE.attId, ROLE);
    
#define PRINT_DEVICE_ADDR(BD_ADRES, CONN_HANDLE)                                                        \
                        DBG_PRINTF("Addr: %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x attId:%x\r\n",\
                                                     BD_ADRES.bdAddr[5u], BD_ADRES.bdAddr[4u], BD_ADRES.bdAddr[3u],\
                                                     BD_ADRES.bdAddr[2u], BD_ADRES.bdAddr[1u], BD_ADRES.bdAddr[0u],\
                                                     CONN_HANDLE.attId);
                                    
#define ENABLED                     (1u)
#define DISABLED                    (0u)

/***************************************
* Conditional Compilation Parameters
***************************************/
#define DEBUG_UART_ENABLED          ENABLED
#define DEBUG_FULL_ENABLED          DISABLED

    
#define AUTO_SCAN_CONNECT_MODE
           
    
#define CY_BLE_MAX_SCAN_DEVICES        (9u)
#define CY_BLE_MAX_CENTRAL_CONN_NUM    (4u)        /* master: */ 
                                                       
/***************************************
*           API Constants
***************************************/
#define TIMER_SLEEP_MODE            (10u)
#define TIMER_TIMEOUT               (1u)            /* Сounts in s */
#define INVALID_INDEX               (0xff) 
#define LED_TIMEOUT                 (1000u/300u)    /* Сounts depend on advertising interval parameter */

/***************************************
*       Data Type
***************************************/
typedef struct
{    

    /* Peer device handle */
    cy_stc_ble_conn_handle_t   connHandle[CY_BLE_CONN_COUNT];
    
    /* New notification flag */
    bool                       isNewNotification[CY_BLE_CONN_COUNT];
    
    
} app_stc_connection_info_t;

typedef struct
{
    /* Array for store peer device address */
    cy_stc_ble_gap_bd_addr_t  address[CY_BLE_MAX_SCAN_DEVICES];
    
    /* Number of peer device in list */
    uint32_t                  count;    
    
    /* Connection request, include number of device for connection */
    uint32_t                  connReq;   
    
    volatile bool             pauseScanProgress;
} app_stc_scan_device_list_t;

typedef struct
{
    uint8_t   deviceNumber;
    int32_t  temperature;
    uint32_t  pressure;
    uint32_t  humidity;
    uint16_t  tvoc;
    uint16_t  eco2; 
} app_stc_sensor_data_t;



/***************************************
*        Macros
***************************************/
#if (DEBUG_UART_ENABLED == ENABLED)
    #define DBG_PRINTF(...)                 (printf(__VA_ARGS__))
    #define UART_DEB_PUT_CHAR(...)           while(1UL != UART_DEB_Put(__VA_ARGS__))
    #define UART_DEB_GET_CHAR(...)          (UART_DEB_Get())
    #define UART_DEB_IS_TX_COMPLETE(...)    (UART_DEB_IsTxComplete())
    #define UART_DEB_WAIT_TX_COMPLETE(...)   while(UART_DEB_IS_TX_COMPLETE() == 0) ;    
    #define UART_DEB_SCB_CLEAR_RX_FIFO(...) (Cy_SCB_ClearRxFifo(UART_DEB_SCB__HW))
    #define UART_START(...)                 (UART_DEB_Start(__VA_ARGS__))
#else
    #define DBG_PRINTF(...)
    #define UART_DEB_PUT_CHAR(...)
    #define UART_DEB_GET_CHAR(...)          (0u)
    #define UART_DEB_IS_TX_COMPLETE(...)    (1u)
    #define UART_DEB_WAIT_TX_COMPLETE(...)  (0u)
    #define UART_DEB_SCB_CLEAR_RX_FIFO(...) (0u)
    #define UART_START(...)
#endif /* (DEBUG_UART_ENABLED == ENABLED) */

#define UART_DEB_NO_DATA                (char8) CY_SCB_UART_RX_NO_DATA

/***************************************
*        External Function Prototypes
***************************************/
int HostMain(void);
void Timer_Interrupt(void);
void Connect(uint8_t peerAddrType, uint8_t *peerBdAddr);
void Disconnect(cy_stc_ble_conn_handle_t connHandle);
app_stc_connection_info_t* GetAppConnInfoPtr(void);
app_stc_scan_device_list_t* GetAppScanDevInfoPtr(void);


/* Function Prototypes from debug.c */
void ShowValue(cy_stc_ble_gatt_value_t *value);
char HexToAscii(uint8_t value, uint8_t nibble);
void Set32ByPtr(uint8_t ptr[], uint32_t value);
void PrintStackVersion(void);
void PrintApiResult(cy_en_ble_api_result_t apiResult);
void ShowError(void);


#endif /* COMMON_H */

/* [] END OF FILE */
