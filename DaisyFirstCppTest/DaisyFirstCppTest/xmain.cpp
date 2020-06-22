#include "daisysp.h"
#include "daisy_pod.h"

using namespace daisysp;
using namespace daisy;

static DaisyPod pod; 
static MoogLadder flt;
static Oscillator osc, lfo;

float k1, k2;  // knobs 1 and 2

float sample_rate;
float FLT_FREQ, FLT_RES;
float LFO_FREQ, LFP_AMP;
float NOTE_FREQ, NOTE_VOL;

void UpdateKnobs(float& k1, float& k2) {
    k1 = pod.knob1.Process();
    k2 = pod.knob2.Process();

    FLT_FREQ = k1;
    LFO_FREQ = k2;
}

void Controls() {
    //pod.UpdateAnalogControls();
    //pod.DebounceControls();
    UpdateKnobs(k1, k2);
}

static void callback(float* in, float* out, size_t size) {
	float saw, freq, output;

    Controls();

    for (size_t i = 0; i < size; i += 2)
    {
        freq = NOTE_FREQ + (lfo.Process() * LFO_FREQ);
        saw = osc.Process();

        flt.SetFreq(freq);
        output = flt.Process(saw);

        // left out
        out[i] = output;

        // right out
        out[i + 1] = output;
    }
}

int main(void) {
    NOTE_FREQ = 110.0;
    NOTE_VOL = 0.24;
    LFO_FREQ = 0.5;
    FLT_FREQ = 109.5;
    FLT_RES = 0.7;

	pod.Init();  // init the pod hardware
    sample_rate = pod.AudioSampleRate();

    pod.led1.Set(k1, 0, k2);
    pod.led1.Set(k2, 0, k1);

    flt.Init(sample_rate);
    flt.SetFreq(FLT_FREQ);  // update with knob1 
    flt.SetRes(FLT_RES);

    lfo.Init(sample_rate);
    lfo.SetWaveform(Oscillator::WAVE_RAMP);
    lfo.SetAmp(1);
    lfo.SetFreq(LFO_FREQ);  // update with knob2

    osc.Init(sample_rate);
    osc.SetWaveform(Oscillator::WAVE_SQUARE);
    osc.SetFreq(NOTE_FREQ);
    osc.SetAmp(NOTE_VOL);

	pod.StartAudio(callback);

	while (true) {

	}
}