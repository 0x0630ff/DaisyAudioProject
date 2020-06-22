//
// # Pluck
//
// Produces a naturally decaying plucked string or drum sound based on the Karplus-Strong algorithms.
// 
// This code has been extracted from the Csound opcode "pluck"
// It has been modified to work as a Daisy Soundpipe module.
// 
// Original Author(s): Barry Vercoe, John ffitch
//
// Year: 1991
//
// Location: OOps/ugens4.c
//

#pragma once
#ifndef DSY_PLUCK_H
#define DSY_PLUCK_H

#include <stdint.h>
#ifdef __cplusplus

namespace daisysp
{

// ## Mode
// The method of natural decay that the algorithm will use.
//
// - RECURSIVE: 1st order recursive filter, with coefs .5.
// - WEIGHTED_AVERAGE: weighted averaging. 
// ~~~~
	enum 
	{
		PLUCK_MODE_RECURSIVE,
		PLUCK_MODE_WEIGHTED_AVERAGE,
        PLUCK_LAST,
	};
// ~~~~

	class Pluck
	{
	public:
		Pluck() {}
		~Pluck() {}

// ### Init
// 
// Initializes the Pluck module.
//
// Arguments:
// 
// - sample_rate: Sample rate of the audio engine being run.
// - buf: buffer used as an impulse when triggering the Pluck algorithm
// - npt: number of elementes in buf.
// - mode: Sets the mode of the algorithm.
// 
// ~~~~
		void Init (float sample_rate, float *buf, int32_t npt, int32_t mode);
// ~~~~

// ### Process
//
// Processes the waveform to be generated, returning one sample. This should be called once per sample period.
// ~~~~
		float Process (float &trig);
// ~~~~

// ## Mutators
// 
// ### SetAmp
// 
// Sets the amplitude of the output signal.
// 
// Input range: 0-1?
// 
// ~~~~
		inline void SetAmp(float amp) { amp_ = amp; }
// ~~~~

// ### SetFreq
// 
// Sets the frequency of the output signal in Hz.
// 
// Input range: Any positive value
// 
// ~~~~
		inline void SetFreq(float freq) { freq_ = freq; }
// ~~~~

// ### SetDecay
// 
// Sets the time it takes for a triggered note to end in seconds.
// 
// Input range: 0-1
// 
// ~~~~
		inline void SetDecay(float decay) { decay_ = decay; }
// ~~~~
//
// ### SetDamp
// 
// Sets the dampening factor applied by the filter (based on PLUCK_MODE)
// 
// Input range: 0-1
// 
// ~~~~
		inline void SetDamp(float damp) { damp_ = damp; }
// ~~~~

// ### SetMode
// 
// Sets the mode of the algorithm.
// 
// ~~~~
		inline void SetMode(int32_t mode) { mode_ = mode; }
// ~~~~

// ## Accessors
// 
// ### GetAmp
// 
// Returns the current value for amp.
// 
// ~~~~
		inline float GetAmp() { return amp_; }
// ~~~~

// ### GetFreq
// 
// Returns the current value for freq.
// 
// ~~~~
		inline float GetFreq() { return freq_; }
// ~~~~

// ### GetDecay
// 
// Returns the current value for decay.
// 
// ~~~~
		inline float GetDecay() { return decay_; }
// ~~~~
//
// ### GetDamp
// 
// Returns the current value for damp.
// 
// ~~~~
		inline float GetDamp() { return damp_; }
// ~~~~

// ### GetMode
// 
// Returns the current value for mode.
// 
// ~~~~
		inline int32_t GetMode() { return mode_; }
// ~~~~

	private:
		void Reinit();
		float amp_, freq_, decay_, damp_, ifreq_;
	    float sicps_;
	    int32_t phs256_, npts_, maxpts_;
	    float *buf_;
	    float sample_rate_;
	    char init_;
	    int32_t mode_;
	};
} // namespace daisysp
#endif
#endif
