/* 
 * Synth with FX.
 * accept line input.
 * accept MIDI note playing.
 * two oscilators.
 * two LFO's
 * 
 * inputs:
 *      knob1:      filter
 *      knob2:      envelope
 *      sw1:        waveform up
 *      sw2:        waveform down
 *      encoder:    FX mode selector
 *      encButton:  confirm mode
 * 
 * ouputs:
 *      audio:      synth output, mix in inputs
 *      led1:       set color for waveform selection
 *      led2:       set color for FX mode selection
 *      seedLed:    blink at LFO1 rate
 * 
 */
  
#include <stdio.h>
#include <string.h>
using namespace std;

#include "daisy_seed.h"
#include "daisy_pod.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

#include "PrintOut.h"
using namespace PrintOut;

DaisySeed seed;
DaisyPod pod;
Printer printer;

Oscillator osc1;
Oscillator osc2;

// static float NOTE_FREQ;

// static char buff[512];
// uint8_t sumbuff[1024];

// void UsbCallback(uint8_t* buf, uint32_t* len) {
//     for(size_t i = 0; i < *len; i++)     {
//         sumbuff[i] = buf[i];
//     }
// }

// void print(char *buff) {
//     seed.usb_handle.TransmitInternal((uint8_t*)buff, strlen(buff));
// }

// void printo(char *buff, const char* text) {
//     sprintf(buff, "%s", text);
//     seed.usb_handle.TransmitInternal((uint8_t*)buff, strlen(buff));
// }

char makeString();

int main(void) {
    // main function here
    seed.Configure();
    seed.Init();
    seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    seed.usb_handle.SetReceiveCallback(UsbCallback);

    int numbers = 0;

    printer.out("TESTING!!!!! NO VARIABLES!!!!");
    
    // loop it
    while (1) {

        // sprintf(buff, "print this shiiiiit %d %x\r\n", numbers, numbers++);
        // print(buff);
        printer.out("testing testing %d\r\n");
        numbers++;
        if (numbers == 100) {
            numbers = 0;
        }
        dsy_system_delay(1000);
    }

}