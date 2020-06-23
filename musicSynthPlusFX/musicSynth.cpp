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

// lasy class for printing char strings out...
#include "PrintOut.h"
using namespace PrintOut;

DaisySeed seed;
DaisyPod pod;
Printer printer;

Oscillator osc1;
Oscillator osc2;

char makeString();

int main(void) {
    seed.Configure();
    seed.Init();
    seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    seed.usb_handle.SetReceiveCallback(UsbCallback);

    int numbers = 0;

    // char buffer[512];

    printer.out("TESTING!!!!! NO VARIABLES!!!!");

    char charstring[] = "HOW BIG IS THIS SENTENCE?";
    
    int textSize = printer.checkSize(charstring);

    // loop it
    while (true) {
        
        printer.out("testing testing %d\r\n", numbers);

        printer.out("The sentence is %d char long.\r\n", textSize);

        numbers++;

        if (numbers == 100) {
            numbers = 0;
        }

        dsy_system_delay(1000);
    }

}