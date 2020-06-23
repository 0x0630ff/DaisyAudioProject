#pragma once

#ifndef __TIMER_H_
#define __TIMER_H_

#include "daisy_seed.h"
using namespace daisy;

#include "PrintOut.h"
using namespace PrintOut;

namespace ClockTimer {

    class cTimer {
        public:
            cTimer();
            bool Init();
            uint32_t timeStamp;
            
            void setTimeStamp();
            uint32_t getTimeStamp();

    };

}

#endif
