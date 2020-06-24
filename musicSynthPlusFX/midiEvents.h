/*
 * MIDI Events.
 */

#pragma once

#ifndef __MIDIEVENTS_H
#define __MIDIEVENTS_H

#include "daisy_pod.h"
#include "daisysp.h"
#include <stdio.h>
#include <string.h>

using namespace daisy;
using namespace daisysp;

// #ifndef __PRINTOUT_H_
// #include "PrintOut.h"
// using namespace PrintOut;

// #endif

namespace MidiManager {
    class MIDICom: public MidiHandler {
        //midi.StartReceive();
        private:
            int MidiChannelRec;
            int MidiChannelSend;
            int MidiBuff[255];
            
            MidiHandler midi;
            MidiInputMode midiInputMode = MidiInputMode::INPUT_MODE_UART1;
            MidiOutputMode midiOutputMode = MidiOutputMode::OUTPUT_MODE_NONE;

        public:
            void Init() {
                this->midi.Init(MIDICom::midiInputMode, MIDICom::midiOutputMode);
                this->midi.StartReceive();
            }

            void Start() {
                this->midi.StartReceive();
            }

            void setMidiChannelRec(int channel) {
                this->MidiChannelRec = channel;
            }

            void setMidiChannelSend(int channel) {
                this->MidiChannelSend = channel;
            }

            int getMidiInChannel() {
                return this->MidiChannelRec;
            }

            int getMidiOutChannel() {
                return this->MidiChannelSend;
            }

            //  Main MidiEvent Handler fucntion 
            MidiEvent handleMidiMessage(MidiEvent m) {
                switch (m.type) {

                    case NoteOn: {
                        // handle NoteOn type events
                        NoteOnEvent note = m.AsNoteOn();
                        if (m.data[1] != 0) {
                            note = m.AsNoteOn();
                            
                        }
                        return m;
                        break;
                    }

                    case ControlChange: {
                        // handle controlChanges
                        ControlChangeEvent cc = m.AsControlChange();
                        sendCC(cc);
                        return m;
                        break;
                    }
                    default: {
                        return m;
                        break;
                    }

                }  // end switch

            }  // handleMidiMessage end

            void sendCC(ControlChangeEvent cc) {
                // do stuff w/ cc events.
                // printer.out("CC Sent:\t%d\t%d\t%d\r\n", cc.control_number * 1.0, cc.value * 1.0);
            }

    };      // end class MIDICom

}       // end MidiManager


#endif