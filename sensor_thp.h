
/********************** Include Files **************************/
#include <pigpio.h>

/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/
#define SDA 2
#define SCL 3

/*********** Macros (Inline Functions) Definitions *************/
/******************* Variable Definitions **********************/
/******************** Function Prototypes **********************/

int temp(double time);
int hum(double time);
int press(double time);
void configGPIO();
