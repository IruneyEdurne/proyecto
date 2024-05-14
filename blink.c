//********************//
//    ___   ___  ____ //
//   / _ | / _ \/ __/ //
//  / __ |/ // / _/   //
// /_/ |_/____/___/   //
//********************//
//!
//! \file: blink.c
//! \brief: Sample for using the GPIO on the Raspberry PI
//! \author: Jose Luis Unibaso

/********************** Include Files **************************/
#include "blink.h"

/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/

/*********** Macros (Inline Functions) Definitions *************/
/******************* Variable Definitions **********************/
/******************** Function Prototypes **********************/

void configGPIO() {
    gpioInitialise();
    gpioSetMode(LED, PI_OUTPUT);
    gpioWrite(LED, 0);
}

int blink(double time) {
    gpioWrite(LED, 1);
    time_sleep(time);
    gpioWrite(LED, 0);
    time_sleep(time);
    return 0;
}