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

// #include "daisy_seed.h"
#include "daisy_pod.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed seed;
DaisyPod pod;

Oscillator osc1;
Oscillator osc2;

// lasy class for printing char strings out...
#include "PrintOut.h"
// using namespace PrintOut;
PrintOut::Printer printer;

bool led_state = false;

static int counter = 0;

int main(void) {
    seed.Configure();
    seed.Init();
    seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    seed.usb_handle.SetReceiveCallback(PrintOut::UsbCallback);

    seed.SetLed(1);

    while (true) {
        printer.out("WTF!!!! %d\r\n", 8);
        counter++;

        dsy_tim_delay_ms(250);

    }

}