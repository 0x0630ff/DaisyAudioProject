// # Audio
// ## Description
// Audio Driver
// 
// Configures Audio Device and provides callback for signal processing.
//
// **Many of the hard-coded values here will change (increase), and/or
//   be replaced by configurable options**
//
#ifndef DSY_AUDIO_H
#define DSY_AUDIO_H
#include <stddef.h>
#include <stdint.h>
#include "per_sai.h"
#include "per_i2c.h"
#ifdef __cplusplus
extern "C"
{
#endif

   

// ## Defines
// Defines for generic maximums
//
// While 'Audio Channels Max' is set to 2, this is per-SAI 
// 
// 4x4 Audio I/O is possible using the dsy_audio_mc_callback
//
// Hard-coded samplerate is calculated from original clock tree.
//
// The new clock tree has less than 0.01% error for all supported samplerates
// ~~~~
#define DSY_AUDIO_BLOCK_SIZE_MAX 128
#define DSY_AUDIO_CHANNELS_MAX 2

#ifndef DSY_AUDIO_SAMPLE_RATE
#define DSY_AUDIO_SAMPLE_RATE 48014.0f
#endif
// ~~~~

	// ### Enum for specifying SAI Block
	//
	// Internally, there are two separate 'audio blocks' that can
	// be configured together or separately
	//
	// ~~~~
	enum
	{
		DSY_AUDIO_INTERNAL,
		DSY_AUDIO_EXTERNAL,
		DSY_AUDIO_LAST,
	};
	// ~~~~

	// ## Audio Handle
	//
	// Simple config struct that holds peripheral drivers.
	//
	// ~~~~
	typedef struct
	{
		size_t			block_size;
		dsy_sai_handle *sai;
		dsy_i2c_handle *dev0_i2c;
		dsy_i2c_handle *dev1_i2c;
	} dsy_audio_handle;
	// ~~~~

    // ## Callback Definitions
	// These are user-defineable callbacks that are called when 
    // audio data is ready to be received/transmitted.
    //
    // This function is called at samplerate/blocksize
	// (e.g. 1kHz when 

    // ### Interleaved Stereo callback
	//
    // Function to define for using a single Stereo device for I/O
    //
    // audio is packed as: { LEFT | RIGHT | LEFT | RIGHT }
    //
    // typical example:
    // ```C
    // void AudioCallback(float *in, float *out, size_t size)
    // {
    //		for (size_t i = 0; i < size; i+=2)
    //		{
    //			out[i] = in[i]; // Left
    //			out[i+1] = in[i+1]; // Right
    //		}
    // }
	// ```
	// ~~~~
    typedef void (*dsy_audio_callback)(float*, float*, size_t);
    // ~~~~

    // ### Non-Interleaved Multichannel callback
    // Defaults to 4 channels, and is fixed for now.
    // (still works for stereo, but will still fill buffers)
    //
    // audio is packed as:
    //
    // { LEFT | LEFT + 1 | . . . | LEFT + SIZE | RIGHT | RIGHT + 1 | . . . | RIGHT + SIZE  }
    //
    // typical example:
    // ```C
    // void AudioCallback(float **in, float **out, size_t size)
    // {
    //		for (size_t i = 0; i < size; i++)
    //		{
    //			for (size_t chn = 0; chn < num_channels; chn++)
	//			{
    //				out[chn] = in[chn]; 
	//			}
    //		}
    // }
    // ```
    // ~~~~
    typedef void (*dsy_audio_mc_callback)(float**, float**, size_t);
	// ~~~~

    // ## Functions
    // ### Init
    // Initializes the Audio Engine using configurations
    // set to the sai_handle
    //
    // i2c_handles can be set to NULL if not needed.
    //
    // ~~~~
    void dsy_audio_init(dsy_audio_handle* handle);
    // ~~~~

    // ### set_callback
	// Sets the user defined, interleaving callback to be called when audio
    // data is ready.
	// 
    // intext is a specifier for DSY_AUDIO_INT/EXT (which audio peripheral to use).
	// 
    // When using this, each 'audio block' can have completely independent callbacks.
	//
	// ~~~~
    void dsy_audio_set_callback(uint8_t intext, dsy_audio_callback cb);
	// ~~~~

	// ### set_mc_callback
	// Sets the user defined, non-interleaving callback to be called when audio
    // data is ready.
	//
	// This will always use both DSY_AUDIO_INT and DSY_AUDIO_EXT blocks together.
	//
    // To ensure clean audio you'll want to make sure the two SAIs are set to the same samplerate
	// ~~~~
    void dsy_audio_set_mc_callback(dsy_audio_mc_callback cb);
	// ~~~~

    // ### set_blocksize
    // Sets the number of samples (per-channel) to be handled in a single audio frame.
    //
	// ~~~~
    void dsy_audio_set_blocksize(uint8_t intext, size_t blocksize);
	// ~~~~

	// ### start
	// Starts Audio Engine, callbacks will begin getting called.
	//
    // When using with dsy_audio_mc_callback (for 4 channels), 
	// this function should be called for both audio blocks
	// ~~~~
    void dsy_audio_start(uint8_t intext);
	// ~~~~

	// ### stop
	// Stops transmitting/receiving audio on the specified audio block.
	// ~~~~
	void dsy_audio_stop(uint8_t intext);
	// ~~~~

	// ### enter bypass
	// 
	// If the device supports hardware bypass, enter that mode.
	//
    // **Only minimally tested with WM8731 codec.**
	//
	void dsy_audio_enter_bypass(uint8_t intext);

	// ### exit bypass
	//
	// If the device supports hardware bypass, exit that mode.
	//
    // **Only minimally tested with WM8731 codec.**
	//
	// ~~~~
	void dsy_audio_exit_bypass(uint8_t intext);
	// ~~~~

	// ## Default Callbacks
	// A few useful stereo-interleaved callbacks
	// ### passthru
    // Passes the input to the output
	// ~~~~
	void dsy_audio_passthru(float* in, float* out, size_t size);
	// ~~~~
	// ### silence
	// sets outputs to 0 without stopping the Audio Engine.
	// ~~~~
	void dsy_audio_silence(float* in, float* out, size_t size);
	// ~~~~

#ifdef __cplusplus
}
#endif
#endif
