/********************** Include Files **************************/
#include "sensor_thp.h"

/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/

/*********** Macros (Inline Functions) Definitions *************/
/******************* Variable Definitions **********************/
/******************** Function Prototypes **********************/

void configGPIO() {
    gpioInitialise();
    gpioSetMode(LED, PI_OUTPUT);
}

int mediciones(double time) {
    gpioRead(SLA);
    return 0;
}
