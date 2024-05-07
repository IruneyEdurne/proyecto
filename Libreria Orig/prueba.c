/********************** Include Files **************************/
//#include "sensor_thp.h"
# include <stdio.h>
//#include <stdint.h>
//#include <stddef.h>

//#ifndef BME280_INTF_RET_TYPE
//#define BME280_INTF_RET_TYPE
//#endif
///********************* Type Definitions ************************/
///******************* Constant Definitions **********************/

///*********** Macros (Inline Functions) Definitions *************/
///******************* Variable Definitions **********************/
///******************** Function Prototypes **********************/

////  archivo.h


//#define I2C_DEVICE "/dev/i2c-1"
//#define BME280_CHIP_ID //0x60
//#define BME280_I2C_ADDR  // 0x76
//#DEFINE BME280_INTF_RET_TYPE
////* Register addres*/





//// UNa struct es una clase

//struct miSensor {
	
	//uint8_t chip_id;
	//intf = BME280_I2C_INTF;
	//void *intf_ptr;
	
	//// Variable to store result of read/write function
	//BME280_INTF_RET_TYPE intf_rstl;
	
	////read function pointer
	//bme280_read_fptr_t read;

	////write function pointer
	//bme280_read_fptr_t write;
	
	
	
	
	//}

////// archivo.c

#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_DEVICE "/dev/i2c-1"
#define BME280_ADDRESS 0x76



//read temperature
int read_temperature(){
	
	int file;
	char filename[] = I2C_DEVICE;
	uint8_t reg_data[3];
	
	
	int msb;;		//temp[19:12]
	int lsb;		//temp[11:4]
	int xlsb;		//temp[3:0]
	
	
	if ((file= open(filename , 0_RDWR)) <0 ){
		
		perror("Failed to open the bus");
		return 1;
		}
		
	if (ioctl(file,I2C_SLAVE,BME280_ADDRESS)<0){
		
		perror("Failed to aquire bus acces and/or talk slave");
		return 1;
		}
		
	if (read(file,reg_data,3) != 3){
		
		perror("Failed to select temperature register");
		return 1;
		}	
	
	msb = i2cget -y 1 0x76 0xFA;
	lsb = i2cget -y 1 0x76 0xFB;
	xlsb = i2cget -y 1 0x76 0xFC;
	printf ("Temp leida\n");
	
	}






// Leer en que modo esta

//Ponerlo en modo forced

//


void greet(){
	
	printf("hola\n");
	}



int main() {
	read_temperature();
	printf("A ver que tal\n");
	return 0;
}	
	
