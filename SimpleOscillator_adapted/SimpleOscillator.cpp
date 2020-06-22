#include "daisy_pod.h"
#include "daisy_seed.h"
#include "daisysp.h"

#define NUM_WAVEFORMS 8

using namespace daisy;
using namespace daisysp;


// set up for the blinkLED function
DaisySeed seed;
DaisyPod   hw;
bool led_state = false;
float BLINK_DELAY = 250.0;

void blinkLED(float BLINK_TIME) {
    if (dsy_tim_get_ms() > BLINK_TIME) {
        led_state = !led_state;
        seed.SetLed(led_state);
        dsy_tim_init();
        dsy_tim_start();
    }
}


Oscillator osc, osc2;
Parameter  p_freq;
MoogLadder moogflt;
CrossFade cf_Mixer;

uint8_t waveforms[NUM_WAVEFORMS] = {
    Oscillator::WAVE_SIN,
    Oscillator::WAVE_TRI,
    Oscillator::WAVE_POLYBLEP_SAW,
    Oscillator::WAVE_POLYBLEP_SQUARE,
    Oscillator::WAVE_SIN,
    Oscillator::WAVE_TRI,
    Oscillator::WAVE_POLYBLEP_SAW,
    Oscillator::WAVE_POLYBLEP_SQUARE,
};

static float   freq, freq2;
float          sig;
static int     waveform, octave;

static void AudioCallback(float *in, float *out, size_t size)
{
    blinkLED(BLINK_DELAY);
    hw.DebounceControls();

    waveform += hw.encoder.Increment();
    waveform = DSY_CLAMP(waveform, 0, NUM_WAVEFORMS);

    osc.SetWaveform(waveforms[waveform]);
    osc2.SetWaveform(waveforms[waveform + 1]);

    if(hw.button2.RisingEdge())
        octave++;
    if(hw.button1.RisingEdge())
        octave--;
    octave = DSY_CLAMP(octave, 2, 5);

    // convert MIDI to frequency and multiply by octave size
    freq = mtof( (p_freq.Process()) + ((octave) * 12) );  // mtof == midi to freq
    freq2 = mtof( (p_freq.Process()) + ((octave) * 12) + 5);  // mtof == midi to freq

    osc.SetFreq(freq);
    osc2.SetFreq(freq2);

    float MAX_FILTER_FREQ = 440.0 * 5;
    moogflt.SetFreq(hw.knob2.Process() * MAX_FILTER_FREQ);

    float osc1_out = osc.Process();
    float osc2_out = osc2.Process();

    cf_Mixer.SetPos(0.0);

    // send the two sources into the mixer
    float mixed_audio = cf_Mixer.Process(osc1_out, osc2_out );

    // Audio Loop
    for(size_t i = 0; i < size; i += 2)
    {
        // Process
        sig        = moogflt.Process(mixed_audio);
        out[i]     = sig;
        out[i + 1] = sig;
    }
}

void InitSynth(float samplerate)
{
    // Init freq Parameter to knob1 using MIDI note numbers
    // min 10, max 127, curve linear
    p_freq.Init(hw.knob1, 0, 127, Parameter::LINEAR);
    moogflt.Init(samplerate);
    moogflt.SetRes(0.1);

    osc.Init(samplerate);
    osc.SetAmp(0.99f);
    osc2.Init(samplerate);
    osc2.SetAmp(0.99f);

    waveform = 1;
    octave   = 2;
}


int main(void)
{
    float samplerate;

    seed.Configure();
    dsy_tim_init();
    dsy_tim_start();

    // Init everything
    hw.Init();
    samplerate = hw.AudioSampleRate();
    InitSynth(samplerate);

    moogflt.SetFreq(0);

    // start callbacks
    hw.StartAdc();
    hw.StartAudio(AudioCallback);

    while(1) { }
}
