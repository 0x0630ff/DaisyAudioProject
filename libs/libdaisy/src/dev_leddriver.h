// # LED Driver
// ## Description
//
// Device driver for PCA9685 16-channel 12-bit PWM generator
//
// ## TODO:
//
// * Move color usage to util_color
// * Add a function to dump out how long it takes to write all assigned LEDs.
// * Fix update function so that it doesn't only write one device per call
//
#pragma once
#ifndef SA_LED_DRIVER_H
#define SA_LED_DRIVER_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include "per_i2c.h"

// ## Defines
#define DSY_LED_DRIVER_MAX_DRIVERS 8

    // ## Data

    // ### Preset Colors
    // ~~~~
    enum
    {
        LED_COLOR_RED,
        LED_COLOR_GREEN,
        LED_COLOR_BLUE,
        LED_COLOR_WHITE,
        LED_COLOR_PURPLE,
        LED_COLOR_CYAN,
        LED_COLOR_GOLD,
        LED_COLOR_OFF,
        LED_COLOR_LAST
    };
    // ~~~~

    // ## Color
    // Simple color struct
    //
    // Different from util_color only in type (0-4095 vs 0-1)
    //
    // This could easily be migrated to work with those instead.
    // ~~~~
    typedef struct
    {
        uint16_t red, green, blue;
    } color;
    // ~~~~


	// ## Functions
	// ### Init
	// Initializes the LED Driver(s) on the specified I2C Bus
	// 
	// * dsy_i2c should be any dsy_i2c_handle with pins and speed configured.
	// * addr is either a pointer to 1 device address, or an array of addresses for multiple devices
	// * addr_cnt is the number of addresses passed in (use '1' for a single device)
	// 
	// ~~~~
    void   dsy_led_driver_init(dsy_i2c_handle *dsy_i2c,
                               uint8_t *       addr,
                               uint8_t         addr_cnt);
    // ~~~~

	// ### Update
	// Updates the LED Driver with the values set using the set function
	// 
    // Currently only updates one driver at a time due to the time it takes to update all of the devices.
	// 
	// This can likely be set up to use DMA so that the function doesn't block for so long.
	//
	// ~~~~
    void   dsy_led_driver_update();
	// ~~~~

	// ### set_led
	// sets the LED at the index to the specified brightness (0-1)
	//
    // Index is sequential so device 0 will have idx 0-15,
    // while device 1 will have idx 16-31, etc.
	//
	// ~~~~
    void   dsy_led_driver_set_led(uint8_t idx, float bright);
	// ~~~~

	// ### color_by_name
	// Passing in one of the preset colors will return a pointer to a 
    // color struct
	// ~~~~
    color *dsy_led_driver_color_by_name(uint8_t name);
	// ~~~~

#ifdef __cplusplus
}
#endif
#endif
