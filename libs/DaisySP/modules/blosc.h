// # BlOsc
//
// Band Limited Oscillator
//
// ## Credits  
// * Based on bltriangle, blsaw, blsquare from soundpipe
// * Original Author(s): Paul Batchelor, saw2 Faust by Julius Smith
// * Ported by Ben Sergentanis, May 2020

#pragma once
#ifndef DSY_BLOSC_H
#define DSY_BLOSC_H

#include <stdint.h>
#ifdef __cplusplus

namespace daisysp
{
   
    class BlOsc
    {
    public:
        BlOsc() {}
	~BlOsc() {}

	// Bl Waveforms
	// ~~~~
	enum Waveforms
	{
	    WAVE_TRIANGLE,
	    WAVE_SAW,
	    WAVE_SQUARE,
	    WAVE_OFF,
	};
	// ~~~~
	
        // ###Init
	//
        // -Initialize oscillator.
	// -Defaults to: 440Hz, .5 amplitude, .5 pw, Triangle.
        //
        // #Argument:  float sample_rate: audio engine sample rate.
        // ~~~~
	    void Init(float sample_rate);
        // ~~~~

        // ###Process
        //
        // - Get next floating point oscillator sample.
        // ~~~~
     	    float Process();
        // ~~~~

	    
	// #Setters	
	//
	// ###SetFreq
	//
	// - Float freq: Set oscillator frequency in Hz.
	// ~~~~
            inline void SetFreq(float freq) { freq_ = freq; };
        // ~~~~
        
	// ###SetAmp
	//
	// - Float amp: Set oscillator amplitude, 0 to 1.
        // ~~~~
	    inline void SetAmp(float amp)   { amp_ = amp;};
        // ~~~~

        // ###SetPw
        //
        // - Float pw: Set square osc pulsewidth, 0 to 1. (no thru 0 at the moment)
        // ~~~~
	    inline void SetPw(float pw)   { pw_ = 1 - pw;};
        // ~~~~

	// ###SetWaveform
	//
	// - uint8_t waveform: select between waveforms from enum above.
	// - i.e. SetWaveform(BL_WAVEFORM_SAW); to set waveform to saw
	// ~~~~
	    inline void SetWaveform(uint8_t waveform){ mode_ = waveform;}
	// ~~~~

    private:
	float rec0_[2], rec1_[2], vec0_[2], vec1_[2], vec2_[4096],
	      freq_, amp_, pw_, sampling_freq_, half_sr_, quarter_sr_,
	      sec_per_sample_, two_over_sr_, four_over_sr_;
	uint8_t mode_;
	int iota_;
	
	float ProcessSquare();
	float ProcessTriangle();
	float ProcessSaw();
	void  Reset();
    };
} // namespace daisysp
#endif
#endif
