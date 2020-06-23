#include "Timer.h"

namespace ClockTimer {
    
    cTimer::cTimer(): timeStamp(0) { }
    
    bool cTimer::Init() {
        return true;
    }

    void cTimer::setTimeStamp() {
        timeStamp = dsy_tim_get_ms();
        // printer.out("%d", timeStamp);
    }

    uint32_t cTimer::getTimeStamp() {
        return cTimer::timeStamp;
    }

}