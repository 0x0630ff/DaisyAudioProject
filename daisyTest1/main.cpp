#include "daisy_pod.h"

using namespace daisy;

static DaisyPod pod;
static uint8_t led_sel;
static int32_t inc;

Color set_colors[5];

const int NUM_COLORS = 5;

Parameter p_knob1, p_knob2;

float knob1val;

static void callback(float* in, float* out, size_t size)
{
    // Debounce the encoder at a steady, fixed rate.
    pod.encoder.Debounce();
    inc = pod.encoder.Increment();
    // Change the selected LED based on the increment.
    if (inc > 0)
    {
        led_sel += 1;
        // Wrap around
        if (led_sel > NUM_COLORS - 1)
        {
            led_sel = 0;
        }
    }
    else if (inc < 0)
    {
        // Wrap around
        if (led_sel == 0)
        {
            led_sel = NUM_COLORS - 1;
        }
        else
        {
            led_sel -= 1;
        }
    }
    if (pod.encoder.RisingEdge())
    {
        led_sel = 4;
    }
    pod.ClearLeds();
    pod.led1.SetColor(set_colors[led_sel]);
    pod.led2.SetColor(set_colors[led_sel]);
    pod.UpdateLeds();
}

int main() {

	pod.Init();
	led_sel = 0;
	inc = 0;

    p_knob1.Init(pod.knob1, 0, 1, Parameter::LINEAR);
    p_knob2.Init(pod.knob2, 0, 1, Parameter::LINEAR);


	pod.StartAudio(callback);

	while (true) {
        knob1val = p_knob1.Process();

        set_colors[0].Init(255 - knob1val, 0, 0);
        set_colors[1].Init(0, 255 - knob1val, 0);
        set_colors[2].Init(Color::PresetColor::BLUE);
        set_colors[3].Init(Color::PresetColor::WHITE);
        set_colors[4].Init(Color::PresetColor::OFF);

        pod.led1.SetColor(set_colors[led_sel]);

	}
}