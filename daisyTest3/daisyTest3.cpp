#include "daisy_pod.h"
#include "daisysp.h"
#include <math.h>

using namespace daisy;
using namespace daisysp;

/*
 * This got slightly more complex, but also copied from example projects a lot.
 */

// Set max delay time to 0.75 of samplerate.
#define MAX_DELAY static_cast<size_t>(48000 * 2.5f)

DaisyPod pod;
DaisySeed seed;

static Parameter deltime, cutoffParam;

static Oscillator osc1;
static Oscillator osc2;


static float   freq;
float          sig;
static int     waveform, octave;

const int NUM_WAVEFORMS = 4;

uint8_t waveforms[NUM_WAVEFORMS] = {
    Oscillator::WAVE_SIN,
    Oscillator::WAVE_TRI,
    Oscillator::WAVE_POLYBLEP_SAW,
    Oscillator::WAVE_POLYBLEP_SQUARE,
};

static ReverbSc  rev;
static DelayLine<float, MAX_DELAY> DSY_SDRAM_BSS dell;
static DelayLine<float, MAX_DELAY> DSY_SDRAM_BSS delr;

long unsigned int BLINK_TIME = 250;

const int N_MODES = 3;
const int REV = 0;
const int DEL = 1;

static bool led_state = true;
float currentDelay, feedback, delayTarget;
float cutoff, drywet;
int mode = REV;


void UpdateButtons(bool& b1, bool& b2) {

}


void blinkLED() {
    if (dsy_tim_get_ms() > BLINK_TIME) {
        led_state = !led_state;
        seed.SetLed(led_state);
        dsy_tim_init();
        dsy_tim_start();
    }
}


void UpdateKnobs(float& k1, float& k2) {
    k1 = pod.knob1.Process();
    k2 = pod.knob2.Process();

    switch (mode)
    {
    case REV:
        drywet = k1;
        rev.SetFeedback(k2);
        break;
    case DEL:
        delayTarget = deltime.Process();
        feedback = k2;
        break;
    }
}


void UpdateEncoder() {
    mode = mode + pod.encoder.Increment();
    mode = (mode % N_MODES + N_MODES) % N_MODES;
}


void UpdateLeds(float k1, float k2) {
    float BRIGHTNESS = 0.8;
    pod.led1.Set(   k1 * (mode == N_MODES - 1) * BRIGHTNESS, 
                    k1 * (mode == N_MODES - 2) * BRIGHTNESS, 
                    k1 * (mode == 0 || mode == N_MODES - 1) * BRIGHTNESS);

    pod.led2.Set(   k2 * (mode == N_MODES - 1) * BRIGHTNESS, 
                    k2 * (mode == N_MODES - 2) * BRIGHTNESS, 
                    k2 * (mode == 0 || mode == N_MODES - 1) * BRIGHTNESS);

    pod.UpdateLeds();
}


void Controls() {
    // setup the controllers
    float k1, k2;
    bool b1, b2;

    delayTarget = feedback = drywet = 0;

    pod.UpdateAnalogControls();
    pod.DebounceControls();

    UpdateButtons(b1, b2);
    UpdateKnobs(k1, k2);
    UpdateEncoder();
    UpdateLeds(k1, k2);
}


void GetReverbSample(float& outl, float& outr, float inl, float inr) {
    rev.Process(inl, inr, &outl, &outr);
    outl = drywet * outl + (1 - drywet) * inl;
    outr = drywet * outr + (1 - drywet) * inr;
}


void GetDelaySample(float& outl, float& outr, float inl, float inr) {
    fonepole(currentDelay, delayTarget, .00007f);

    dell.SetDelay(currentDelay);
    delr.SetDelay(currentDelay);

    outl = dell.Read();
    outr = delr.Read();

    dell.Write((feedback * outl) + inl);
    outl = (feedback * outl) + ((1.0f - feedback) * inl);

    delr.Write((feedback * outr) + inr);
    outr = (feedback * outr) + ((1.0f - feedback) * inr);
}


void AudioCallback(float* in, float* out, size_t size) {
    // Audio callback stuff
    float outl, outr, inl, inr;

    Controls();
    
    for (size_t i = 0; i < size; i += 2) {
        inl = in[i];
        inr = in[i + 1];

        switch (mode) {
            case REV:
                // reverb setting
                GetReverbSample(outl, outr, inl, inr);
                break;
            case DEL:
                // delay mode settings
                GetDelaySample(outl, outr, inl, inr);
                break;
            default:
                outl = outr = 0;
        }  // end switch

    // left out
    out[i] = outl;

    // right out
    out[i + 1] = outr;

    } // end audio loop
}


int main(void) {
    seed.Configure();
    pod.Init();
    float sample_rate = pod.AudioSampleRate();

    // oscilator init
    osc1.Init(sample_rate);
    osc2.Init(sample_rate);

    // effects init
    rev.Init(sample_rate);
    dell.Init();
    delr.Init();

    //set parameters
    deltime.Init(pod.knob1, sample_rate * .05, MAX_DELAY, deltime.LOGARITHMIC);
    cutoffParam.Init(pod.knob1, 500, 20000, cutoffParam.LOGARITHMIC);

    //reverb parameters
    rev.SetLpFreq(18000.0f);
    rev.SetFeedback(0.85f);

    //delay parameters
    currentDelay = delayTarget = sample_rate * 0.75f;
    dell.SetDelay(currentDelay);
    delr.SetDelay(currentDelay);

    // hardware init
    pod.led1.Set(0, 0, 0);
    pod.led2.Set(0, 0, 0);
    pod.UpdateLeds();

    // timer set up and start (mainly for blink right now)
    dsy_tim_init();
    dsy_tim_start();

    // start the audio input
    pod.StartAdc();
    // start sound generation with callback
    pod.StartAudio(AudioCallback);

    while(true) {
        blinkLED();  // blink the onboard led.
    }

}