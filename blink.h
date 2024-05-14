//********************//
//    ___   ___  ____ //
//   / _ | / _ \/ __/ //
//  / __ |/ // / _/   //
// /_/ |_/____/___/   //
//********************//
//!
//! \file: blink.h
//! \brief: Header for blink library
//! \author: Jose Luis Unibaso

/********************** Include Files **************************/
#include <pigpio.h>

/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/
#define LED 21

/*********** Macros (Inline Functions) Definitions *************/
/******************* Variable Definitions **********************/
/******************** Function Prototypes **********************/

int blink(double time);
void configGPIO();
