/***************************************************************************//**
* \file cy_scb_spi.h
* \version 1.0
*
* Provides SPI API declarations of the SCB driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

/**
* \addtogroup group_scb_spi
* \{
* Driver API for SPI Bus Peripheral.
*
* Three different SPI protocols or modes are supported:
* * The original SPI protocol as defined by Motorola.
* * TI: Uses a short pulse on "spi_select" to indicate a start of transaction.
* * National Semiconductor (Microwire): Transmissions and Receptions occur
*   separately.
* In addition to the standard 8-bit word length, the component supports a
* configurable 4- to 16-bit data width for communicating at non-standard SPI
* data widths.
*
* \section group_scb_spi_configuration Configuration Considerations
*
* To set up an SPI, provide configuration parameters in the
* \ref cy_stc_scb_spi_config_t structure. For example: provide spiMode,
* subMode, sclkMode, oversample, rxDataWidth, and txDataWidth. The other
* parameters are optional for operation.
* To initialize driver call \ref Cy_SCB_SPI_Init function providing the pointer
* to populated configuration structure
* \ref cy_stc_scb_spi_config_t and the pointer to allocated context structure
* \ref cy_stc_scb_spi_context_t.
* The clock source connected to the SCB SPI must be configured to provide
* the sufficient frequency and set the appropriate oversampling (only matters
* for the master mode) to reach the desired data rate. Call
* \ref Cy_SCB_SPI_Enable to start the SPI operation after configuration is
* completed.
*
* The SPI API are the same for the master and slave mode operation and
* are divided into two categories: low-level and high-level. Do not
* mix high-level and low-level API because a low-level API can adversely
* affect the operation of a higher level API.
*
* The Low-level API's functions allow interacting directly with the hardware
* and do not use interrupts. These functions do not require context for
* operation, thus NULL can be passed in \ref Cy_SCB_SPI_Init and
* \ref Cy_SCB_SPI_Disable instead of a pointer to the context structure.
*
* * To write data into the TX FIFO, use one of the provided functions:
*   \ref Cy_SCB_SPI_Write, \ref Cy_SCB_SPI_WriteArray or
*   \ref Cy_SCB_SPI_WriteArrayBlocking.
*   Note that in the master mode, putting data into the TX FIFO starts a
*   transfer. Due to the SPI nature, the received data is put into the RX FIFO.
*
* * To read data from the RX FIFO, use one of the provided functions:
*   \ref Cy_SCB_SPI_Read or \ref Cy_SCB_SPI_ReadArray.
*
* * The statuses can be polled using: \ref Cy_SCB_SPI_GetRxFifoStatus,
*   \ref Cy_SCB_SPI_GetTxFifoStatus and \ref Cy_SCB_SPI_GetSlaveMasterStatus.
*   The statuses are W1C (Write 1 to Clear) and after a status is set,
*   it must be cleared. Note that there are statuses evaluated as level. These
*   statuses remain set when an event is true. Therefore, after the clear
*   operation, the status is cleared but then it is restored (if event is still
*   true).
*   For example: the TX FIFO empty interrupt source can be cleared when the
*   TX FIFO is not empty. Put at least two data elements (one goes to the
*   shifter and next to FIFO) before clearing this status.
*
* The High-level API uses interrupts to execute a transfer. Call
* \ref Cy_SCB_SPI_Transfer to start communication: for the master mode a
* transfer to the slave is started while for the slave mode the Read and Write
* buffers are prepared for the following communication with the master.
* After a transfer is started, the \ref Cy_SCB_SPI_Interrupt handles the
* transfer until its completion. Therefore it must be called inside the
* user interrupt handler to make the high-level API work. To monitor the status
* of the transfer operation, use \ref Cy_SCB_SPI_GetTransferStatus.
* Alternately, use \ref Cy_SCB_SPI_RegisterCallback to register a callback
* function to be notified about \ref group_scb_spi_macro_callback_events.
*
* \section group_scb_spi_more_information More Information
*
* For more information on the SCB peripheral, refer to the technical reference 
* manual (TRM).
*
* \section group_scb_spi_MISRA MISRA-C Compliance
* <table class="doxtable">
*   <tr>
*     <th>MISRA Rule</th>
*     <th>Rule Class (Required/Advisory)</th>
*     <th>Rule Description</th>
*     <th>Description of Deviation(s)</th>
*   </tr>
*   <tr>
*     <td>11.4</td>
*     <td>A</td>
*     <td>A cast should not be performed between a pointer to object type and
*         a different pointer to object type.</td>
*     <td>The pointer to the buffer memory is void to allow handling different
*         different data types: uint8_t (4-8 bits) or uint16_t (9-16 bits).
*         </td>
*   </tr>
*   <tr>
*     <td>14.2</td>
*     <td>R</td>
*     <td>All non-null statements shall either: a) have at least one side-effect
*         however executed, or b) cause control flow to change.</td>
*     <td>The unused function parameters are cast to void. This statement
*         has no side-effect and is used to suppress a compiler warning.</td>
*   </tr>
*   <tr>
*     <td>20.3</td>
*     <td>R</td>
*     <td>The validity of values passed to library functions shall be checked.
*     </td>
*     <td>The CY_ASSERT() macro is used for verification of pointer to context
*         parameter against NULL. This macro halts code execution if
*         verification fails what ensures that NULL pointer is not dereference.
*     </td>
*   </tr>
* </table>
*
* \section group_scb_spi_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_scb_spi_macro Macro
* \defgroup group_scb_spi_functions Functions
* \defgroup group_scb_spi_data_structures Data Structures
* \defgroup group_scb_spi_enums Enumerated Types
*/

#if !defined(CY_SCB_SPI_H)
#define CY_SCB_SPI_H

#include "cy_scb_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*          Enumerated Types
***************************************/

/**
* \addtogroup group_scb_spi_enums
* \{
*/

/** SPI status codes */
typedef enum 
{
    /** Operation completed successfully */
    CY_SCB_SPI_SUCCESS = 0x00U,

    /** One or more of input parameters are invalid */
    CY_SCB_SPI_BAD_PARAM = CY_SCB_ID | CY_PDL_STATUS_ERROR | CY_SCB_SPI_ID | 1UL,

    /**
    * The SPI is busy processing a transfer. Call this function again
    * once that transfer is completed or aborted.
    */
    CY_SCB_SPI_TRANSFER_BUSY
} cy_en_scb_spi_status_t;
/** \} group_scb_spi_enums */


/***************************************
*       Type Definitions
***************************************/

/**
* \addtogroup group_scb_spi_data_structures
* \{
*/

/**
* Provides the typedef for the callback function called in the
* \ref Cy_SCB_SPI_Interrupt to notify the user about occurrences of
* \ref group_scb_spi_macro_callback_events.
*/
typedef void (* scb_spi_handle_events_t)(uint32_t event);


/** SPI Configuration Structure */
typedef struct cy_stc_scb_spi_config
{
    /**
    * Specifies the mode of operation
    * (See \ref group_scb_spi_macro_modes for the set of constants)
    */
    uint32_t    spiMode;

    /**
    * Specifies the submode of SPI operation
    * (See \ref group_scb_spi_macro_sub_modes for the set of constants)
    */
    uint32_t    subMode;

    /**
    * Configures the SCLK operation for Motorola sub-mode, ignored for all
    * other submodes (See \ref group_scb_spi_macro_sclk_modes for the set
    * of constants)
    */
    uint32_t    sclkMode;

    /**
    * Oversample factor for SPI.
    * * For the master mode, the data rate is the SCB clock / oversample
    *   (valid range is 4-16).
    * * For the slave mode, the oversample value is ignored. The data rate is
    *   determined by the SCB clock frequency. See the device datasheet for
    *   more details.
    */
    uint32_t    oversample;

    /**
    * The width of RX data (valid range 4-16). It must be the same as
    * \ref txDataWidth except in National sub-mode.
    */
    uint32_t    rxDataWidth;

    /**
    * The width of TX data (valid range 4-16). It must be the same as
    * \ref rxDataWidth except in National sub-mode.
    */
    uint32_t    txDataWidth;

    /**
    * Enables the hardware to shift out the data element MSB first, otherwise,
    * LSB first
    */
    bool        enableMsbFirst;

    /**
    * Enables the master to generate a continuous SCLK regardless of whether
    * there is data to send
    */
    bool        enableFreeRunSclk;

    /**
    * Enables a digital 3-tap median filter to be applied to the input
    * of the RX FIFO to filter glitches on the line.
    */
    bool        enableInputFilter;

    /**
    * Enables the master to sample MISO line one half clock later to allow
    * better timings.
    */
    bool        enableMisoLateSample;

    /**
    * Enables the master to transmit each data element separated by a
    * de-assertion of the slave select line (only applicable for the master
    * mode)
    */
    bool        enableTransferSeperation;

    /**
    * Sets active polarity of each SS line.
    * This is a bit mask: bit 0 corresponds to SS0 and so on to SS3.
    * 1 means active high, a 0 means active low.
    */
    uint32_t    ssPolarity;

    /**
    * When set, the slave will wake the device when the slave select line
    * becomes active.
    * Note that not all SCBs support this mode. Consult the device
    * datasheet to determine which SCBs support wake from deep sleep.
    */
    bool        enableWakeFromSleep;

    /**
    * When there are more entries in the RX FIFO, then at this level
    * the RX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls the \ref CY_SCB_SPI_RX_TRIGGER interrupt source.
    */
    uint32_t    rxFifoTriggerLevel;

    /**
    * Bits set in this mask will allow events to cause an interrupt
    * (See \ref group_scb_spi_macro_rx_fifo_status for the set of constant)
    */
    uint32_t    rxFifoIntEnableMask;

    /**
    * When there are fewer entries in the TX FIFO, then at this level
    * the TX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls the \ref CY_SCB_SPI_TX_TRIGGER interrupt source.
    */
    uint32_t    txFifoTriggerLevel;

    /**
    * Bits set in this mask allow events to cause an interrupt
    * (See \ref group_scb_spi_macro_tx_fifo_status for the set of constants)
    */
    uint32_t    txFifoIntEnableMask;

    /**
    * Bits set in this mask allow events to cause an interrupt
    * (See \ref group_scb_spi_macro_master_slave_status for the set of
    * constants)
    */
    uint32_t    masterSlaveIntEnableMask;

}cy_stc_scb_spi_config_t;

/** SPI internal context structure */
typedef struct cy_stc_scb_spi_context
{
    uint32_t volatile status;       /**< Receive status */

    void    *rxBuf;                 /**< Pointer to receive buffer */
    uint32_t volatile rxBufSize;    /**< Receive buffer size */
    uint32_t volatile rxBufIdx;     /**< Pointer to receive buffer */

    void    *txBuf;                 /**< Pointer to transmit buffer */
    uint32_t volatile txBufSize;    /**< Transmit buffer size */
    uint32_t volatile txBufIdx;     /**< Index within transmit buffer */

    /**
    * The pointer to an event callback called when an SPI event occurs
    */
    scb_spi_handle_events_t cbEvents;

#if !defined(NDEBUG)
    uint32_t initKey;               /**< Tracks context initialization */
#endif /* !(NDEBUG) */
} cy_stc_scb_spi_context_t;

/** \} group_scb_spi_data_structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_scb_spi_functions
* \{
*/

/* Basic functions */
cy_en_scb_spi_status_t Cy_SCB_SPI_Init(CySCB_Type *base, cy_stc_scb_spi_config_t const *config,
                                       cy_stc_scb_spi_context_t *context);
void     Cy_SCB_SPI_DeInit (CySCB_Type *base);
__STATIC_INLINE void Cy_SCB_SPI_Enable(CySCB_Type *base);
void     Cy_SCB_SPI_Disable(CySCB_Type *base, cy_stc_scb_spi_context_t *context);

/* Low-power functions */
void Cy_SCB_SPI_DeepSleep(CySCB_Type *base);
void Cy_SCB_SPI_Wakeup   (CySCB_Type *base);

/* Configuration functions */
__STATIC_INLINE void Cy_SCB_SPI_SetActiveSlaveSelect(CySCB_Type *base, uint32_t slaveSelect);
__STATIC_INLINE void Cy_SCB_SPI_SetActiveSlaveSelectPolarity(CySCB_Type *base, uint32_t slaveSelect, uint32_t polarity);

/* Bus status */
__STATIC_INLINE bool Cy_SCB_SPI_IsBusBusy(CySCB_Type const *base);

/* Low-level: Receive direction */
__STATIC_INLINE uint32_t Cy_SCB_SPI_Read     (CySCB_Type const *base);
__STATIC_INLINE uint32_t Cy_SCB_SPI_ReadArray(CySCB_Type const *base, void *rxBuf, uint32_t size);

__STATIC_INLINE uint32_t Cy_SCB_SPI_GetRxFifoStatus  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SPI_ClearRxFifoStatus(CySCB_Type *base, uint32_t clearMask);
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetNumInRxFifo   (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SPI_ClearRxFifo      (CySCB_Type *base);

/* Low-level: Transmit direction */
__STATIC_INLINE uint32_t Cy_SCB_SPI_Write     (CySCB_Type *base, uint32_t data);
__STATIC_INLINE uint32_t Cy_SCB_SPI_WriteArray(CySCB_Type *base, void *txBuf, uint32_t size);
__STATIC_INLINE void     Cy_SCB_SPI_WriteArrayBlocking(CySCB_Type *base,  void *txBuf, uint32_t size);

__STATIC_INLINE uint32_t Cy_SCB_SPI_GetTxFifoStatus  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SPI_ClearTxFifoStatus(CySCB_Type *base, uint32_t clearMask);
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetNumInTxFifo   (CySCB_Type const *base);
__STATIC_INLINE bool     Cy_SCB_SPI_IsTxComplete     (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SPI_ClearTxFifo      (CySCB_Type *base);

/* Low-level: Master or slave status */
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetSlaveMasterStatus  (CySCB_Type const *base);
__STATIC_INLINE void     Cy_SCB_SPI_ClearSlaveMasterStatus(CySCB_Type *base, uint32_t clearMask);

/* High-level: callback */
__STATIC_INLINE void Cy_SCB_SPI_RegisterCallback(CySCB_Type const *base, scb_spi_handle_events_t callback,
                                                 cy_stc_scb_spi_context_t *context);

/* High-level: Transfer functions */
cy_en_scb_spi_status_t Cy_SCB_SPI_Transfer(CySCB_Type *base, void *txBuf, void *rxBuf, uint32_t size,
                                           cy_stc_scb_spi_context_t *context);
void     Cy_SCB_SPI_AbortTransfer    (CySCB_Type *base, cy_stc_scb_spi_context_t *context);
uint32_t Cy_SCB_SPI_GetNumTransfered (CySCB_Type const *base, cy_stc_scb_spi_context_t const *context);
uint32_t Cy_SCB_SPI_GetTransferStatus(CySCB_Type const *base,cy_stc_scb_spi_context_t const *context);

/* High-level: Interrupt handler */
void Cy_SCB_SPI_Interrupt(CySCB_Type *base, cy_stc_scb_spi_context_t *context);
/** \} group_scb_spi_functions */


/***************************************
*            API Constants
***************************************/

/**
* \addtogroup group_scb_spi_macro
* \{
*/

/**
* \defgroup group_scb_spi_macro_modes SPI Modes
* \{
*/
#define CY_SCB_SPI_SLAVE  (0UL) /**< Configures SCB for SPI Slave operation  */
#define CY_SCB_SPI_MASTER (1UL) /**< Configures SCB for SPI Master operation */
/** \} group_scb_spi_macro_modes */

/**
* \defgroup group_scb_spi_macro_sub_modes SPI Submodes
* \{
*/
/** Configures an SPI for a standard Motorola SPI operation */
#define CY_SCB_SPI_MOTOROLA        (0UL)

/**
* Configures the SPI for the TI SPI operation. In the TI mode, the slave select
* is a pulse. In this case, the pulse coincides with the first bit.
*/
#define CY_SCB_SPI_TI_COINCIDES    (1UL)

/**
* Configures an SPI for the TI SPI operation, in the TI mode. The slave select
* is a pulse. In this case the pulse precedes the first bit.
*/
#define CY_SCB_SPI_TI_PRECEDES     (1UL | CY_SCB_SPI_TI_PRECEDE)

/**
* Configures an SPI for the National SPI operation. This is a half-duplex
* mode of operation.
*/
#define CY_SCB_SPI_NATIONAL        (2UL)
/** \} group_scb_spi_macro_sub_modes */

/**
* \defgroup group_scb_spi_macro_sclk_modes SPI SCLK Modes
* \{
*/
#define CY_SCB_SPI_CPHA0_CPOL0 (0UL)   /**< Clock is active low, data is changed on first edge   */
#define CY_SCB_SPI_CPHA0_CPOL1 (1UL)   /**< Clock is active high, data is changed on first edge  */
#define CY_SCB_SPI_CPHA1_CPOL0 (2UL)   /**< Clock is active low, data is changed on second edge  */
#define CY_SCB_SPI_CPHA1_CPOL1 (3UL)   /**< Clock is active high, data is changed on second edge */
/** \} group_scb_spi_macro_sclk_modes */

/**
* \defgroup group_scb_spi_macro_slave_select SPI Slave Selects
* \{
*/
#define CY_SCB_SPI_SLAVE_SELECT0   (0UL)   /**< Master will use Slave Select 0 */
#define CY_SCB_SPI_SLAVE_SELECT1   (1UL)   /**< Master will use Slave Select 1 */
#define CY_SCB_SPI_SLAVE_SELECT2   (2UL)   /**< Master will use Slave Select 2 */
#define CY_SCB_SPI_SLAVE_SELECT3   (3UL)   /**< Master will use Slave Select 3 */
/** \} group_scb_spi_macro_slave_select */

/**
* \defgroup group_scb_spi_macro_tx_fifo_status SPI TX FIFO Statuses
* Each SPI TX FIFO status is encoded in a separate bit. Therefore multiple bits
* may be set to indicate the current status.
* \{
*/
/** The number of entries in the TX FIFO is less than the TX FIFO trigger level
* value
*/
#define CY_SCB_SPI_TX_TRIGGER      (SCB_INTR_TX_TRIGGER_Msk)

/** The TX FIFO is not full, there is a space for more data */
#define CY_SCB_SPI_TX_NOT_FULL     (SCB_INTR_TX_NOT_FULL_Msk)

/**
* The TX FIFO is empty, note that there may still be data in the shift register.
*/
#define CY_SCB_SPI_TX_EMPTY        (SCB_INTR_TX_EMPTY_Msk)

/** An attempt to write to the full TX FIFO */
#define CY_SCB_SPI_TX_OVERFLOW    (SCB_INTR_TX_OVERFLOW_Msk)

/**
* Applicable only for the slave mode. The master tried to read more
* data elements than available.
*/
#define CY_SCB_SPI_TX_UNDERFLOW    (SCB_INTR_TX_UNDERFLOW_Msk)
/** \} group_scb_spi_macro_tx_fifo_status */

/**
* \defgroup group_scb_spi_macro_rx_fifo_status SPI RX FIFO Statuses
* \{
* Each SPI RX FIFO status is encoded in a separate bit. Therefore, multiple
* bits may be set to indicate the current status.
*/
/** The number of entries in the RX FIFO is more than the RX FIFO trigger
* level value.
*/
#define CY_SCB_SPI_RX_TRIGGER      (SCB_INTR_RX_TRIGGER_Msk)

/** The RX FIFO is not empty, there is data to read */
#define CY_SCB_SPI_RX_NOT_EMPTY    (SCB_INTR_RX_NOT_EMPTY_Msk)

/**
* The RX FIFO is full. There is no more space for additional data.
* Any additional data will be dropped.
*/
#define CY_SCB_SPI_RX_FULL         (SCB_INTR_RX_FULL_Msk)

/**
* The RX FIFO was full and there was an attempt to write to it.
* This additional data was dropped.
*/
#define CY_SCB_SPI_RX_OVERFLOW     (SCB_INTR_RX_OVERFLOW_Msk)

/** An attempt to read from an empty RX FIFO */
#define CY_SCB_SPI_RX_UNDERFLOW    (SCB_INTR_RX_UNDERFLOW_Msk)
/** \} group_scb_spi_macro_rx_fifo_status */

/**
* \defgroup group_scb_spi_macro_master_slave_status SPI Master and Slave Statuses
* \{
*/
/** The slave was deselected at the wrong time */
#define CY_SCB_SPI_SLAVE_ERR       (SCB_INTR_S_SPI_BUS_ERROR_Msk)

/** The master has transmitted all data elements from FIFO and shifter */
#define CY_SCB_SPI_MASTER_DONE     (SCB_INTR_M_SPI_DONE_Msk)
/** \} group_scb_spi_macro_master_slave_status */

/**
* \defgroup group_scb_spi_macro_xfer_status SPI Transfer Status
* \{
* Each SPI transfer status is encoded in a separate bit, therefore multiple bits
* may be set to indicate the current status.
*/
/**
* Transfer started by \ref Cy_SCB_SPI_Transfer is in progress.
*/
#define CY_SCB_SPI_TRANSFER_ACTIVE     (0x01UL)

/**
* All TX data from \ref Cy_SCB_SPI_Transfer is in the TX FIFO.
*/
#define CY_SCB_SPI_TRANSFER_IN_FIFO    (0x02UL)

/** The slave was deselected at the wrong time. */
#define CY_SCB_SPI_SLAVE_TRANSFER_ERR  (SCB_INTR_S_SPI_BUS_ERROR_Msk)

/**
* RX FIFO was full and there was an attempt to write to it.
* This additional data was dropped.
*/
#define CY_SCB_SPI_TRANSFER_OVERFLOW   (SCB_INTR_RX_OVERFLOW_Msk)

/**
* Applicable only for the slave mode. The master tried to read more
* data elements than available in the TX FIFO.
*/
#define CY_SCB_SPI_TRANSFER_UNDERFLOW  (SCB_INTR_TX_UNDERFLOW_Msk)
/** \} group_scb_spi_macro_xfer_status */

/**
* \defgroup group_scb_spi_macro_callback_events SPI Callback Events
* \{
* Only single event is notified by the callback.
*/
/** All TX data from \ref Cy_SCB_SPI_Transfer is in the TX FIFO.*/
#define CY_SCB_SPI_TRANSFER_IN_FIFO_EVENT  (0x01U)

/** The transfer started by \ref Cy_SCB_SPI_Transfer is complete.*/
#define CY_SCB_SPI_TRANSFER_CMPLT_EVENT    (0x02U)

/**
* An error occurred during the transfer. This includes overflow, underflow
* and a transfer error. Check \ref Cy_SCB_SPI_GetTransferStatus.
*/
#define CY_SCB_SPI_TRANSFER_ERR_EVENT      (0x04U)
/** \} group_scb_spi_macro_callback_events */

/**
* \defgroup group_scb_spi_macro_polarity SPI Polarity
* \{
*/
#define CY_SCB_SPI_ACTIVE_LOW  (0UL) /**< Signal in question is active low */
#define CY_SCB_SPI_ACTIVE_HIGH (1UL) /**< Signal in question is active high */
/** \} group_scb_spi_macro_polarity */

/** Default TX value when no TX buffer is defined */
#define CY_SCB_SPI_DEFAULT_TX  (0x0000FFFFUL)

/** Data returned by the hardware when an empty RX FIFO is read */
#define CY_SCB_SPI_RX_NO_DATA  (0xFFFFFFFFUL)


/***************************************
*         Internal Constants
***************************************/

/** \cond INTERNAL */
#define CY_SCB_SPI_TI_PRECEDE      (0x10UL)

#define CY_SCB_SPI_RX_INTR         (CY_SCB_SPI_RX_TRIGGER  | CY_SCB_SPI_RX_NOT_EMPTY | CY_SCB_SPI_RX_FULL | \
                                    CY_SCB_SPI_RX_OVERFLOW | CY_SCB_SPI_RX_UNDERFLOW)

#define CY_SCB_SPI_TX_INTR         (CY_SCB_SPI_TX_TRIGGER  | CY_SCB_SPI_TX_NOT_FULL | CY_SCB_SPI_TX_EMPTY | \
                                    CY_SCB_SPI_TX_OVERFLOW | CY_SCB_SPI_TX_UNDERFLOW)

#define CY_SCB_SPI_TRANSFER_ERR    (CY_SCB_SPI_SLAVE_TRANSFER_ERR | CY_SCB_SPI_TRANSFER_OVERFLOW | \
                                    CY_SCB_SPI_TRANSFER_UNDERFLOW)

#define CY_SCB_SPI_INIT_KEY        (0x00ABCDEFUL)
/** \endcond */

/** \} group_scb_spi_macro */


/***************************************
*    In-line Function Implementation
***************************************/

/**
* \addtogroup group_scb_spi_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SCB_SPI_Enable
****************************************************************************//**
*
* Enables the SCB block for the SPI operation.
*
* \param base
* The pointer to the SPI SCB instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_Enable(CySCB_Type *base)
{
    base->CTRL |= SCB_CTRL_ENABLED_Msk;
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_IsBusBusy
****************************************************************************//**
*
* Returns whether the SPI bus is busy or not. The bus busy is determined using
* the slave select signal.
* * Motorola and National Semiconductor sub-modes: the bus is busy after the
*   slave select line is activated and lasts until the slave select line is
*   deactivated.
* * Texas Instrument sub-modes: The bus is busy at the moment of the initial
*   pulse on the slave select line and lasts until the transfer is complete.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* True - the bus is busy, false - the bus is idle.
*
* \note
* * The SPI master does not assign the slave select line immediately after
*   the 1st data element is written into the TX FIFO. It takes up to 2 SCLK
*   clocks to assign the slave select line. Before this happens, the bus
*   is considered idle.
* * If the SPI master is configured to separate a data elements transfer,
*   the bus is busy during each element transfer and is free between them.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_SPI_IsBusBusy(CySCB_Type const *base)
{
    return _FLD2BOOL(SCB_SPI_STATUS_BUS_BUSY, base->SPI_STATUS);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_SetActiveSlaveSelect
****************************************************************************//**
*
* Selects an active slave select line from one of four available.
* This function is applicable for the master and slave.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param slaveSelect
* The slave select line number.
* See \ref group_scb_spi_macro_slave_select for the set of constants.
*
* \note
* The SCB be idle or disabled before calling this function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_SetActiveSlaveSelect(CySCB_Type *base, uint32_t slaveSelect)
{
    base->SPI_CTRL = _CLR_SET_FLD32U(base->SPI_CTRL, SCB_SPI_CTRL_SSEL, slaveSelect);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_SetActiveSlaveSelectPolarity
****************************************************************************//**
*
* Sets the active polarity for the slave select line.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param slaveSelect
* The slave select line number.
* See \ref group_scb_spi_macro_slave_select for the set of constants.
*
* \param polarity
* The polarity of the slave select line.
* See \ref group_scb_spi_macro_polarity for the set of constants.
*
* \note
* The SCB be idle or disabled before calling this function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_SetActiveSlaveSelectPolarity(CySCB_Type *base, uint32_t slaveSelect, uint32_t polarity)
{
    uint32_t mask = _VAL2FLD(CY_SCB_SPI_CTRL_SSEL_POLARITY, (1UL << slaveSelect));

    if (0UL != polarity)
    {
        base->SPI_CTRL |= (uint32_t)  mask;
    }
    else
    {
        base->SPI_CTRL &= (uint32_t) ~mask;
    }
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_GetRxFifoStatus
****************************************************************************//**
*
* Returns the current status of the RX FIFO.
* Clear the active statuses to let the SCB hardware update them.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* \ref group_scb_spi_macro_rx_fifo_status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetRxFifoStatus(CySCB_Type const *base)
{
    return (Cy_SCB_GetRxInterruptStatus(base) & CY_SCB_SPI_RX_INTR);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ClearRxFifoStatus
****************************************************************************//**
*
* Clears the selected statuses of the RX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param clearMask
* The mask of which statuses to clear.
* See \ref group_scb_spi_macro_rx_fifo_status for the set of constants.
*
* \note
* * This status is also used for interrupt generation, so clearing it also
*   clears the interrupt sources.
* * Level sensitive statuses such as \ref CY_SCB_SPI_RX_TRIGGER,
*   \ref CY_SCB_SPI_RX_NOT_EMPTY and \ref CY_SCB_SPI_RX_FULL set high again after
*   being cleared if the condition remains true.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_ClearRxFifoStatus(CySCB_Type *base, uint32_t clearMask)
{
    Cy_SCB_ClearRxInterrupt(base, clearMask);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_GetNumInRxFifo
****************************************************************************//**
*
* Returns the number of data elements in the SPI RX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* The number of data elements in the RX FIFO.
* The size of a data element defined by the configured RX data width.
*
* \note
* This number does not include any data currently in the RX shifter.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetNumInRxFifo(CySCB_Type const *base)
{
    return Cy_SCB_GetNumInRxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ClearRxFifo
****************************************************************************//**
*
* Clears all data out of the SPI RX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \sideeffect
* Any data currently in the shifter is cleared and lost.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_ClearRxFifo(CySCB_Type *base)
{
    Cy_SCB_ClearRxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_GetTxFifoStatus
****************************************************************************//**
*
* Returns the current status of the TX FIFO.
* Clear the active statuses to let the SCB hardware update them.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* \ref group_scb_spi_macro_tx_fifo_status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetTxFifoStatus(CySCB_Type const *base)
{
    return (Cy_SCB_GetTxInterruptStatus(base) & CY_SCB_SPI_TX_INTR);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ClearTxFifoStatus
****************************************************************************//**
*
* Clears the selected statuses of the TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param clearMask
* The mask of which statuses to clear.
* See \ref group_scb_spi_macro_tx_fifo_status for the set of constants.
*
* \note
* * The status is also used for interrupt generation, so clearing it also
*   clears the interrupt sources.
* * Level sensitive statuses such as \ref CY_SCB_SPI_TX_TRIGGER,
*   \ref CY_SCB_SPI_TX_EMPTY and \ref CY_SCB_SPI_TX_NOT_FULL set high again after
*   being cleared if the condition remains true.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_ClearTxFifoStatus(CySCB_Type *base, uint32_t clearMask)
{
    Cy_SCB_ClearTxInterrupt(base, clearMask);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_GetNumInTxFifo
****************************************************************************//**
*
* Returns the number of data elements in the SPI TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* The number of data elements in the TX FIFO.
* The size of a data element defined by the configured TX data width.
*
* \note
* This number does not include any data currently in the TX shifter.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetNumInTxFifo(CySCB_Type const *base)
{
    return Cy_SCB_GetNumInTxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_IsTxComplete
****************************************************************************//**
*
* Checks if the TX FIFO and Shifter are empty and there is no more data to send
*
* \param base
* Pointer to the SPI SCB instance.
*
* \return
* If true, transmission complete. If false, transmission is not complete.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SCB_SPI_IsTxComplete(CySCB_Type const *base)
{
    return Cy_SCB_IsTxComplete(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ClearTxFifo
****************************************************************************//**
*
* Clears all data out of the SPI TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \sideeffect
* The TX FIFO clear operation also clears the shift register, so that
* the shifter could be cleared in the middle of a data element transfer,
* corrupting it. The data element corruption means that all bits which has
* not been transmitted are transmitted as 1s on the bus.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_ClearTxFifo(CySCB_Type *base)
{
    Cy_SCB_ClearTxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_GetSlaveMasterStatus
****************************************************************************//**
*
* Returns the current status of either the slave or the master, depending
* on the configured SPI mode.
* Clear the active statuses to let the SCB hardware update them.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* \ref group_scb_spi_macro_master_slave_status
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_GetSlaveMasterStatus(CySCB_Type const *base)
{
    uint32_t retStatus;

    if (_FLD2BOOL(SCB_SPI_CTRL_MASTER_MODE, base->SPI_CTRL))
    {
        retStatus = (Cy_SCB_GetMasterInterruptStatus(base) & CY_SCB_MASTER_INTR_SPI_DONE);
    }
    else
    {
        retStatus = (Cy_SCB_GetSlaveInterruptStatus(base) & CY_SCB_SLAVE_INTR_SPI_BUS_ERROR);
    }

    return (retStatus);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ClearSlaveMasterStatus
****************************************************************************//**
*
* Clears the selected statuses of either the slave or the master.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param clearMask
* The mask of which statuses to clear.
* See \ref group_scb_spi_macro_master_slave_status for the set of constants.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_ClearSlaveMasterStatus(CySCB_Type *base, uint32_t clearMask)
{
    if (_FLD2BOOL(SCB_SPI_CTRL_MASTER_MODE, base->SPI_CTRL))
    {
        Cy_SCB_ClearMasterInterrupt(base, clearMask);
    }
    else
    {
        Cy_SCB_ClearSlaveInterrupt(base, clearMask);
    }
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_Read
****************************************************************************//**
*
* Reads a single data element from the SPI RX FIFO.
* This function does not check if the RX FIFO has data before reading it.
* If the RX FIFO is empty, the function returns \ref CY_SCB_SPI_RX_NO_DATA.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \return
* Data from the RX FIFO.
* The data element size is defined by the configured RX data width.
*
* \note
* * This function only reads data available in the RX FIFO. It does not
*   initiate an SPI transfer.
* * When in the master mode, writes data into the TX FIFO and waits until
*   the transfer is completed before getting data from the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_Read(CySCB_Type const *base)
{
    return Cy_SCB_ReadRxFifo(base);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_ReadArray
****************************************************************************//**
*
* Reads an array of data out of the SPI RX FIFO.
* This function does not block. It returns how many data elements were read
* from the RX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param rxBuf
* The pointer to the location to place data read from the RX FIFO.
* The item size is defined by the data type which depends on the configured
* RX data width.
*
* \param size
* The number of data elements to read from the RX FIFO.
*
* \return
* The number of data elements read from the RX FIFO.
*
* \note
* * This function only reads data available in the RX FIFO. It does not
*   initiate an SPI transfer.
* * When in the master mode, writes data into the TX FIFO and waits until
*   the transfer is completed before getting data from the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_ReadArray(CySCB_Type const *base, void *rxBuf, uint32_t size)
{
    return Cy_SCB_ReadArray(base, rxBuf, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_Write
****************************************************************************//**
*
* Places a single data element in the SPI TX FIFO.
* This function does not block. It returns how many data elements were placed
* in the TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param data
* Data to put in the TX FIFO.
* The item size is defined by the data type, which depends on the configured
* TX data width.
*
* \return
* The number of data elements placed in the TX FIFO: 0 or 1.
*
* \note
* * When in the master mode, writing data into the TX FIFO starts an SPI
*   transfer.
* * When in the slave mode, writing data into the TX FIFO does not start
*   an SPI transfer. The data is loaded in the TX FIFO and will be sent
*   to the master on its request.
* * The SPI interface is full-duplex, therefore reads and writtes occur
*   at the same time. Thus for every data element transferred out of the
*   TX FIFO, one is transferred into the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_Write(CySCB_Type *base, uint32_t data)
{
    return Cy_SCB_Write(base, data);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_WriteArray
****************************************************************************//**
*
* Places an array of data in the SPI TX FIFO. This function does not
* block. It returns how many data elements were placed in the TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param txBuf
* The pointer to the data to place in the TX FIFO.
* The item size is defined by the data type, which depends on the configured
* TX data width.
*
* \param size
* The number of data elements to transmit.
*
* \return
* The number of data elements placed in the TX FIFO.
*
* \note
* * When in the master mode, writing data into the TX FIFO starts an SPI
*   transfer.
* * When in the slave mode, writing data into the TX FIFO does not start
*   an SPI transfer. The data is loaded in the TX FIFO and will be sent to
*   the master on its request.
* * The SPI interface is full-duplex, therefore reads and writtes occur
*   at the same time. Thus for every data element transferred out of the
*   TX FIFO, one is transferred into the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SCB_SPI_WriteArray(CySCB_Type *base, void *txBuf, uint32_t size)
{
    return Cy_SCB_WriteArray(base, txBuf, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_WriteArrayBlocking
****************************************************************************//**
*
* Places an array of data in the SPI TX FIFO. This function blocks
* until the number of data elements specified by size is placed in the SPI
* TX FIFO.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param txBuf
* The pointer to data to place in the TX FIFO.
* The item size is defined by the data type, which depends on the configured
* TX data width.
*
* \param size
* The number of data elements to write into the TX FIFO.
*
* \note
* * When in the master mode, writing data into the TX FIFO starts an SPI
*   transfer.
* * When in the slave mode, writing data into the TX FIFO does not start
*   an SPI transfer. The data is loaded in the TX FIFO and will be sent to
*   the master on its request.
* * The SPI interface is full-duplex, therefore reads and writtes occur
*   at the same time. Thus for every data element transferred out of the
*   TX FIFO, one is transferred into the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_WriteArrayBlocking(CySCB_Type *base, void *txBuf, uint32_t size)
{
    Cy_SCB_WriteArrayBlocking(base, txBuf, size);
}


/*******************************************************************************
* Function Name: Cy_SCB_SPI_RegisterCallback
****************************************************************************//**
*
* Registers a callback function, which notifies that
* \ref group_scb_spi_macro_callback_events occurred in the
* \ref Cy_SCB_SPI_Interrupt.
*
* \param base
* The pointer to the SPI SCB instance.
*
* \param callback
* The pointer to the callback function.
* See \ref scb_spi_handle_events_t for the function prototype.
*
* \param context
* The pointer to the context structure \ref cy_stc_scb_spi_context_t allocated
* by the user. The structure is used during the SPI operation for internal
* configuration and data keeping. The user should not modify anything
* in this structure.
*
* \note
* To remove the callback, pass NULL as the pointer to the callback function.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SCB_SPI_RegisterCallback(CySCB_Type const *base,
            scb_spi_handle_events_t callback, cy_stc_scb_spi_context_t *context)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    context->cbEvents = callback;
}

/** \} group_scb_spi_functions */

#if defined(__cplusplus)
}
#endif

/** \} group_scb_spi */

#endif /* (CY_SCB_SPI_H) */


/* [] END OF FILE */

