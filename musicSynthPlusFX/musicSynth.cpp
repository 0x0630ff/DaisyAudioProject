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
#include "PrintOut.h"
#include "Timer.h"

using namespace daisy;
using namespace daisysp;
using namespace PrintOut;
using namespace ClockTimer;

DaisySeed seed;
DaisyPod pod;

Oscillator osc1;
Oscillator osc2;

// my Custom Classes
Printer print;
cTimer timer;

int counter = 0;

void setup() {
    seed.Configure();
    pod.Init();
    float samplerate;
    samplerate = pod.AudioSampleRate();
    dsy_tim_init();
    dsy_tim_start();
    seed.usb_handle.Init(UsbHandle::FS_INTERNAL);
    seed.usb_handle.SetReceiveCallback(UsbCallback);
}

int main(void) {
    setup();
    while (true) {
        uint32_t ts = timer.getMS();
        print.out("Counter:%6d  ||  TimeStamp:%6u\r\n", counter++, ts);
        dsy_tim_delay_ms(250);
    }

}