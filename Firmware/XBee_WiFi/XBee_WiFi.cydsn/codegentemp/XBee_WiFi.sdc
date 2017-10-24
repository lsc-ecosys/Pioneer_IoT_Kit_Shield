# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Dropbox\Projects\Pioneer_Kit_Shield\Firmware\XBee_WiFi\XBee_WiFi.cydsn\XBee_WiFi.cyprj
# Date: Mon, 23 Oct 2017 15:05:31 GMT
#set_units -time ns
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyHFClk0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_generated_clock -name {CyFastClk} -source [get_pins {ClockBlock/hfclk_0}] -edges {1 2 3} [list [get_pins {ClockBlock/fastclk}]]
create_generated_clock -name {CyPeriClk} -source [get_pins {ClockBlock/hfclk_0}] -edges {1 3 5} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CySlowClk} -source [get_pins {ClockBlock/hfclk_0}] -edges {1 3 5} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {SPI_SCBCLK} -source [get_pins {ClockBlock/hfclk_0}] -edges {1 13 29} [list [get_pins {ClockBlock/ff_div_0}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk_0}] -edges {1 869 1737} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Dropbox\Projects\Pioneer_Kit_Shield\Firmware\XBee_WiFi\XBee_WiFi.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Dropbox\Projects\Pioneer_Kit_Shield\Firmware\XBee_WiFi\XBee_WiFi.cydsn\XBee_WiFi.cyprj
# Date: Mon, 23 Oct 2017 15:05:29 GMT
