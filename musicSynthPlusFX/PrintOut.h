#pragma once

#ifndef __PRINTOUT_H_
#define __PRINTOUT_H_

#include <stdio.h>
#include <cstring>
#include <stdarg.h>

#include "daisy_seed.h"
using namespace daisy;

namespace PrintOut {

    char sumbuff[1024];

    void UsbCallback(uint8_t* buf, uint32_t* len) {
        for(size_t i = 0; i < *len; i++)     {
            sumbuff[i] = buf[i];
        }
    }

    class Printer: public DaisySeed {
        private:
            char buffer[512];
            DaisySeed seed;

        public:
            Printer() {  //DaisySeed& seed 
            }  // Printer class constructor
            
            unsigned int checkSize(const char* texttocheck) {
                return strlen(texttocheck);
            }

            void out(const char* textout, ...) {
                // char buffer[128];
                memset(buffer, 0, sizeof(buffer));
                va_list va;
                va_start (va, textout);
                vsprintf (buffer, textout, va);
                va_end (va);
                seed.usb_handle.TransmitInternal((uint8_t*)buffer, strlen(buffer));
                // return;

                // }  // end else for sizeCheck
                
            }  // end out 'out()' method

    };  // end of Printer class

}  // end of namespace PrintOut

#endif  // end of __PRINTOUT_H_
