// # Compressor
// 
// influenced by compressor in soundpipe (from faust).
// 
// Modifications made to do:
// 
// - Less calculations during each process loop (coefficients recalculated on parameter change).
// - C++-ified
// - added sidechain support
//
// TODO:
// 
// - With fixed controls this is relatively quick, but changing controls now costs a lot more
// - Still pretty expensive
// - Add soft/hard knee settings 
// - Maybe make stereo possible? (needing two for stereo is a bit silly, 
// and their gain shouldn't be totally unique.
// 
// 
// by: shensley
//
#pragma once
#ifndef DSY_COMPRESSOR_H
#define DSY_COMPRESSOR_H

namespace daisysp
{

class Compressor
{
    public:
    Compressor() {}
    ~Compressor() {}

// ### Init
//
// Initializes compressor
// 
// sample_rate - rate at which samples will be produced by the audio engine.
// ~~~~
    void Init(float sample_rate);
// ~~~~

// ### Process
// compresses the audio input signal, either keyed by itself, or a secondary input.
// 
// in - audio input signal (to be compressed)
// 
// (optional) key - audio input that will be used to side-chain the compressor. 
// ~~~~
	float Process(float in, float key);
	float Process(float in);
// ~~~~

// ## setters

// ### SetRatio
// amount of gain reduction applied to compressed signals
// 
// Expects 1.0 -> 40. (untested with values < 1.0)
// ~~~~
    inline void SetRatio(const float &ratio)
// ~~~~
    {
        ratio_ = ratio;
		RecalculateSlopes();
	}

// ### SetThreshold
// threshold in dB at which compression will be applied
// 
// Expects 0.0 -> -80.
// ~~~~
    inline void SetThreshold(const float &thresh)
// ~~~~
    {
        thresh_ = thresh;
		RecalculateSlopes();
	}

// ### SetAttack
// envelope time for onset of compression for signals above the threshold.
// 
// Expects 0.001 -> 10
// ~~~~
    inline void SetAttack(const float &atk)
// ~~~~
    {
        atk_ = atk;
		RecalculateSlopes();
    }

// ### SetRelease
// envelope time for release of compression as input signal falls below threshold.
// 
// Expects 0.001 -> 10
// ~~~~
    inline void SetRelease(const float &rel)
// ~~~~
    {
        rel_ = rel;
		RecalculateSlopes();
    }

    private:
	  void  RecalculateSlopes();
	  float sr_;
	  float ratio_, thresh_, atk_, rel_;
	  float makeup_gain_;
	  // internals from faust struct
	  float f_rec2_[2], f_rec1_[2], f_rec0_[2];
	  float f_slow0_, f_slow1_, f_slow2_, f_slow3_, f_slow4_, f_slow5_;
	  int   i_const0_;
	  float f_const1_, f_const2_;
};

} // namespace daisysp

#endif // DSY_COMPRESSOR_H
