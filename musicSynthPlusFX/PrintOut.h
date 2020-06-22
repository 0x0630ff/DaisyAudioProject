#pragma once

#ifndef __PRINTOUT_H_
#define __PRINTOUT_H_

#include <stdio.h>
#include <string.h>

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
                out("Printing: \r\n");
            }

            void out(const char* textout) {
                sprintf(this->buffer, textout);
                seed.usb_handle.TransmitInternal((uint8_t*)buffer, strlen(buffer));
            }

    };

}  // end of namespace PrintOut

#endif  // end of __PRINTOUT_H_
