// # QSPI
// ## Description
// Driver for QSPI peripheral to interface with external flash memory.
//
// Currently supported QSPI Devices:
//		* IS25LP080D
//
#ifndef DSY_QSPI
#define DSY_QSPI
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "daisy_core.h" // Added for dsy_gpio_pin typedef

// ## Error codes
// ~~~~
#define DSY_MEMORY_OK ((uint32_t)0x00)
#define DSY_MEMORY_ERROR ((uint32_t)0x01)
// ~~~~

// ## Section Attributes
// used for reading memory in memory_mapped mode.
// ~~~~
#define DSY_QSPI_TEXT __attribute__((section(".qspiflash_text")))
#define DSY_QSPI_DATA __attribute__((section(".qspiflash_data")))
#define DSY_QSPI_BSS __attribute__((section(".qspiflash_bss")))
    // ~~~~

    // ## Data
    // ### Pins
    // List of Pins used in QSPI (passed in during Init)
    // ~~~~
    typedef enum
    {
        DSY_QSPI_PIN_IO0,
        DSY_QSPI_PIN_IO1,
        DSY_QSPI_PIN_IO2,
        DSY_QSPI_PIN_IO3,
        DSY_QSPI_PIN_CLK,
        DSY_QSPI_PIN_NCS,
        DSY_QSPI_PIN_LAST,
    } dsy_qspi_pin;
    // ~~~~

    // ### Modes
    // Modes of operation.
    // /
    // Memory Mapped mode: QSPI configured so that the QSPI can be
    //		read from starting address 0x90000000. Writing is not
    //		possible in this mode.
    // Indirect Polling mode: Device driver enabled.
    //		Read/Write possible via dsy_qspi_* functions
    // ~~~~
    typedef enum
    {
        DSY_QSPI_MODE_DSY_MEMORY_MAPPED,
        DSY_QSPI_MODE_INDIRECT_POLLING,
        DSY_QSPI_MODE_LAST,
    } dsy_qspi_mode;
    // ~~~~

    // ### Device
    // Flash Devices supported. (Both of these are more-or-less the same,
    //		just different sizes).
    // ~~~~
    typedef enum
    {
        DSY_QSPI_DEVICE_IS25LP080D,
        DSY_QSPI_DEVICE_IS25LP064A,
        DSY_QSPI_DEVICE_LAST,
    } dsy_qspi_device;
    // ~~~~
    // ## dsy_qspi_handle
    // Configuration structure for interfacing with QSPI Driver.
    // ~~~~
    typedef struct
    {
        dsy_qspi_mode   mode;
        dsy_qspi_device device;
        dsy_gpio_pin    pin_config[DSY_QSPI_PIN_LAST];
    } dsy_qspi_handle;
    // ~~~~

    // ## Init
    // Initializes QSPI peripheral, and Resets, and prepares memory for access.
    //
    // hqspi should be populated with the mode, device and pin_config before calling this function.
    //
    // Returns DSY_MEMORY_OK or DSY_MEMORY_ERROR
    // ~~~~
    int dsy_qspi_init(dsy_qspi_handle* hqspi);
    // ~~~~

    // ### Deinit
    // Deinitializes the peripheral
    // This should be called before reinitializing QSPI in a different mode.
    //
    // Returns DSY_MEMORY_OK or DSY_MEMORY_ERROR
    // ~~~~
    int dsy_qspi_deinit();
    // ~~~~

    // ### writepage
    // Writes a single page to to the specified address on the QSPI chip.
    //
    // For IS25LP* page size is 256 bytes.
    //
    // Returns DSY_MEMORY_OK or DSY_MEMORY_ERROR
    // ~~~~
    int dsy_qspi_writepage(uint32_t adr, uint32_t sz, uint8_t* buf);
    // ~~~~

    // ### write
    // Writes data in buffer to to the QSPI. Starting at address to address+size
    // ~~~~
    int dsy_qspi_write(uint32_t address, uint32_t size, uint8_t* buffer);
    // ~~~~

    // ### erase
    // Erases the area specified on the chip.
    // Erasures will happen by 4K, 32K or 64K increments.
    //
    // Smallest erase possible is 4kB at a time. (on IS25LP*)
    // ~~~~
    int dsy_qspi_erase(uint32_t start_adr, uint32_t end_adr);
    // ~~~~

    // ## erasesector
    //  Erases a single sector of the chip.
	// 
    //  TODO: Document the size of this function.
	// ~~~~
    int dsy_qspi_erasesector(uint32_t addr);
    // ~~~~


#ifdef __cplusplus
}
#endif

#endif