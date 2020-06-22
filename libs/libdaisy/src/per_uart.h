// # UART
// ## Description
// Uart Peripheral
//
// ## Credit
// Written by: shensley
// Date Added: March 2020
//
// ## TODO:
//
// - Add flexible config for:
//     - data size, stop bits, parity, baud, etc.
//     - dma vs interrupt (or not).
// - Error handling
// - Transmit function improvements.
// - Other UART Peripherals (currently only handles USART1 in UART mode.
// - Overflow handling, etc. for Rx Queue.

#pragma once
#ifndef DSY_UART_H
#define DSY_UART_H
#include "daisy_core.h"

namespace daisy
{
const size_t kUartMaxBufferSize = 32;
class UartHandler
{
  public:
    UartHandler() {}
    ~UartHandler() {}

    // ## Functions
    // ### Init
    // Initializes the UART Peripheral
	// ~~~~
    void Init();
	// ~~~~

    // ### PollReceive
    // Reads the amount of bytes in blocking mode with a 10ms timeout.
    // ~~~~
    int PollReceive(uint8_t *buff, size_t size, uint32_t timeout);
    // ~~~~
    // ### StartRx
    // Starts a DMA Receive callback to fill a buffer of specified size.
    //
    // Data is populated into a FIFO queue, and can be queried with the
    // functions below.
    // Maximum Buffer size is defined above.
    //
    // If a value outside of the maximum is specified,
    // the size will be set to the maximum.
    //
    // ~~~~
    int StartRx(size_t size);
    // ~~~~

    // ### RxActive
    // Returns whether Rx DMA is listening or not.
    bool RxActive();

    // ### FlushRx
    // Flushes the Receive Queue
	// 
    // ~~~~
    int FlushRx();
    // ~~~~

    // ### PollTx
	// Sends an amount of data in blocking mode.
	// ~~~~
    int PollTx(uint8_t *buff, size_t size);
	// ~~~~

	// ### PopRx
    // Pops the oldest byte from the FIFO.
    // ~~~~
    uint8_t PopRx();
	// ~~~~
	// ### Readable
    // Checks if there are any unread bytes in the FIFO
	// ~~~~
    size_t  Readable();
	// ~~~~

    // ### CheckError
    // Returns the result of HAL_UART_GetError() to the user.
    // ~~~~
    int CheckError();
    // ~~~~

  private:
};

} // namespace daisy

#endif
