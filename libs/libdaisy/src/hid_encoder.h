// # Encoder
// ## Description
//
// Generic Class for handling Quadrature Encoders
//
// ## Files
// hid_encoder.*
//
// ## Credits
//
// **Author:** Stephen Hensley
//
// **Date:** December 2019
//
// Inspired/influenced by Mutable Instruments (pichenettes) Encoder classes
//
#pragma once
#ifndef DSY_ENCODER_H
#define DSY_ENCODER_H
#include "daisy_core.h"
#include "per_gpio.h"
#include "hid_switch.h"

namespace daisy
{
class Encoder
{
  public:
    Encoder() {}
    ~Encoder() {}

// ## General Functions
// ### Init
// Initializes the encoder with the specified hardware pins.
//
// Update rate should be the rate at which Debounce() gets called
// in Hertz.
//
// ~~~~
    void
    Init(dsy_gpio_pin a, dsy_gpio_pin b, dsy_gpio_pin click, float update_rate);
// ~~~~
// ### Debounce
// Called at update_rate to debounce and handle timing for the switch.
//
// In order for events not to be missed, its important that the Edge/Pressed checks
// be made at the same rate as the debounce function is being called.
// ~~~~
    void Debounce();
// ~~~~
// ### Increment
// Returns +1 if the encoder was turned clockwise, -1 if it was turned counter-clockwise, or 0 if it was not just turned.
// ~~~~
    inline int32_t Increment() const { return inc_; }
// ~~~~
// ### RisingEdge
// Returns true if the encoder was just pressed.
// ~~~~
    inline bool RisingEdge() const { return sw_.RisingEdge(); }
// ~~~~
// ### FallingEdge
// Returns true if the encoder was just released.
// ~~~~
    inline bool FallingEdge() const { return sw_.FallingEdge(); }
// ~~~~
// ### Pressed
// Returns true while the encoder is held down.
// ~~~~
    inline bool Pressed() const { return sw_.Pressed(); }
// ~~~~
// ### TimeHeldMs
// Returns the time in milliseconds that the encoder has been held down.
// ~~~~
    inline float TimeHeldMs() const { return sw_.TimeHeldMs(); }
// ~~~~

  private:
    Switch   sw_;
    dsy_gpio hw_a_, hw_b_;
    uint8_t  a_, b_;
    int32_t  inc_;
};
} // namespace daisy
#endif
