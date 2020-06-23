#pragma once

#ifndef __TIMER_H_
#define __TIMER_H_

#include "daisy_seed.h"
using namespace daisy;

#ifndef __PRINTOUT_H_
#include "PrintOut.h"
using namespace PrintOut;
#endif

namespace ClockTimer {

    class cTimer {
        public:
            uint32_t timeStamp;
            int overflow;
            
            bool Init() {
                dsy_tim_init();
                dsy_tim_start();
                return true;
            }

            void setTimeStamp()  {
                timeStamp = dsy_tim_get_ms();
            }

            uint32_t getTimeStamp() {
                setTimeStamp();
                return timeStamp;
            }

            int getMS() {
                return dsy_tim_get_ms();
            }

            uint32_t getTick() {
                return dsy_tim_get_tick();
            }

    };

}

#endif
