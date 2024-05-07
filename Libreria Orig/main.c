#include "bme280.h"
#include <pigpio.h>
#include <stdio.h>

#define PIN 2
#define BME280_CHIP_ID_ADDR 0xD0


int main() {
	
	struct bme280_dev dev;
	
	
	int8_t rslt = BME280_OK;

	
	rslt = bme280_init(&dev);
	printf("2 %d\n",rslt);
	
	//if (rslt != BME280_OK){
		//printf("Error en la inizializacion : %d\n",rslt);
		//return 1;
	//}
		
	//uint8_t chip_id;
	//rslt = bme280_get_regs(BME280_CHIP_ID_ADDR,&chip_id,1,&dev);
		
		
	//printf("Chip ID: %d\n",chip_id);

	
  
    return 0;
}
