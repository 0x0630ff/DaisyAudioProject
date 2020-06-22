// # System
// ## Description
// Low level System Configuration
#ifndef DSY_SYSTEM_H
#define DSY_SYSTEM_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

// ## Functions
// ### dsy_system_init
// Initializes Clock tree, MPU, and internal memories voltage regulators.
// 
// This function _must_ be called at the beginning of any program using libdaisy
//
// Higher level daisy_ files call this through the DaisySeed object.
//
// ~~~~
void dsy_system_init();
// ~~~~

// ### dsy_system_jumpto
// Jump to an address within the internal memory
//
// **This may not work correctly, and may not be very useful 
//   with the single sector of memory on the stm32h750**
// ~~~~
void dsy_system_jumpto(uint32_t addr);
// ~~~~

// ### dsy_system_jumptoqspi()
// Jumps to the first address of the external flash chip (0x90000000)
//
// If there is no code there, the chip will likely fall through to the while() loop
//
// Documentation/Loader for using external flash coming soon.
// ~~~~
void     dsy_system_jumptoqspi();
// ~~~~

// ### dsy_system_getnow
// Returns a uint32_t value of milliseconds since the SysTick started
// ~~~~
uint32_t dsy_system_getnow(); // returns HAL_GetTick()
// ~~~~

// Blocking Delay that uses the SysTick (1ms callback) to wait.
// ~~~~
void dsy_system_delay(uint32_t delay_ms);
// ~~~~

#ifdef __cplusplus
};
#endif
#endif
