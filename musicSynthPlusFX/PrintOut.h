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
            int id = 1;
            char buffer[512];
            DaisySeed seed;

        public:
            Printer() {  //DaisySeed& seed 
            }  // Printer class constructor
            
            unsigned int checkSize(const char* texttocheck) {
                return strlen(texttocheck);
            }

            void out(const char* textout, ...) {
                memset(buffer, 0, sizeof(buffer));

                unsigned int sizeCheck = checkSize(textout) + 2;  // adding 2 chars for padding...
                if (sizeCheck > sizeof(buffer)) {
                    return;
                }
                else {
                    va_list va;
                    va_start (va, textout);
                    vsprintf (buffer, textout, va);
                    seed.usb_handle.TransmitInternal((uint8_t*)buffer, strlen(buffer));
                    va_end (va);
                    return;
                }  // end else for sizeCheck
                
            }  // end out 'out()' method

    };  // end of Printer class

}  // end of namespace PrintOut

#endif  // end of __PRINTOUT_H_
