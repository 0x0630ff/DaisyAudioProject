// # DAC
// ## Description
// Driver for the built in DAC on the STM32
//
// The STM32 has 2 Channels of independently configurable
//		DACs, with up to 12-bit resolution.
//
// ## TODO:
//
// - Add Interrupt/DMA modes for block transfers, etc.
// - Add configuration for Buffer state, etc.
// - Add independent settings (bitdepth, etc.) for each channel
//
#pragma once
#ifndef DSY_DAC_H
#define DSY_DAC_H
#include "daisy_core.h"
#ifdef __cplusplus
extern "C"
{
#endif

    // ## Data
    // ### Mode
    // Currently only Polling is supported.
    // ~~~~
    typedef enum
    {
        DSY_DAC_MODE_POLLING,
        DSY_DAC_MODE_LAST,
    } dsy_dac_mode;
    // ~~~~

    // ### Bitdepth
    // Sets the bit depth of the DAC output
    //
    // This can be set independently for each channel.
    // ~~~~
    typedef enum
    {
        DSY_DAC_BITS_8,
        DSY_DAC_BITS_12,
        DSY_DAC_BITS_LAST,
    } dsy_dac_bitdepth;
    // ~~~~

    // ### Channel
    // Sets which channel(s) are initialized with the settings chosen.
    // ~~~~
    typedef enum
    {
        DSY_DAC_CHN1,
        DSY_DAC_CHN2,
        DSY_DAC_CHN_LAST,
        DSY_DAC_CHN_BOTH,
    } dsy_dac_channel;
    // ~~~~

	// ### dsy_dac_handle
	// Configuration structure for DAC initialization and settings.
	// 
    // pin_config must be filled out. However, the DACs are pretty
    //		consistently on pins PA4, and PA5 across all STM32 MCUs
    //		that I've used.
	//
    // ~~~~
    typedef struct
    {
        dsy_dac_mode     mode;
        dsy_dac_bitdepth bitdepth;
        dsy_gpio_pin     pin_config[DSY_DAC_CHN_LAST];
    } dsy_dac_handle;
    // ~~~~

	// ## Functions
	// ### Init
	// Initializes the specified channel(s) of the DAC
	// ~~~~
    void dsy_dac_init(dsy_dac_handle *dsy_hdac, dsy_dac_channel channel);
	// ~~~~

	// ### Start
	// Turns on the DAC and turns on any internal timer if necessary.
	// ~~~~
    void dsy_dac_start(dsy_dac_channel channel);
	// ~~~~

    // ### Write
    // Sets the specified channel of the dac to the value (within bitdepth) resolution.
    //
    // When set to 8-bit, val should be 0-255
    //
    // When set to 12-bit, val should be 0-4095
    // ~~~~
    void dsy_dac_write(dsy_dac_channel channel, uint16_t val);
    // ~~~~

#ifdef __cplusplus
}
#endif
#endif
