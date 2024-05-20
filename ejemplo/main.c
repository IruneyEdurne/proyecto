#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
//libreria del sensor
#include "../lib/bme280.h"
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
//libreria del lcd
#include "../lib/lcd.h"

// delay between samples in microseconds
#define DELAY 1000000

// Comandos de control para el LCD
#define LCD_CMD_CLEAR           0x01
#define LCD_CMD_HOME            0x02
#define LCD_CMD_ENTRY_MODE      0x04
#define LCD_CMD_DISPLAY_CONTROL 0x08
#define LCD_CMD_FUNCTION_SET    0x20
#define LCD_CMD_SET_CGRAM_ADDR  0x40
#define LCD_CMD_SET_DDRAM_ADDR  0x80

// Comandos de control específicos para el modo de entrada de texto
#define LCD_ENTRY_MODE_INCREASE 0x02
#define LCD_ENTRY_MODE_SHIFT    0x01

// Comandos de control específicos para el control de visualización
#define LCD_DISPLAY_ON          0x04
#define LCD_DISPLAY_OFF         0x00
#define LCD_CURSOR_ON           0x02
#define LCD_CURSOR_OFF          0x00
#define LCD_BLINK_ON            0x01
#define LCD_BLINK_OFF           0x00

// Tamaño de la pantalla LCD
#define LCD_NUM_ROWS            2
#define LCD_NUM_COLS            16

int main(int argc, char *argv[])
{
//int i;
int T, P, H;
	if (wiringPiSetup () == -1) exit (1);

  fd = wiringPiI2CSetup(I2C_ADDR);

  //printf("fd = %d ", fd);

  lcd_init(); // setup LCD
  
  //leer la temperatura medida por el sensor
	bme280Temperature(&T);
	T -= 150; 
	//imprimir en la terminal la temperatura
	printf("Calibrated temp. = %3.2f C\n",(float)T/100.0);
	//leer la presion medida por el sensor
	bme280Pressure(&P);
	//imprimir en la terminal la presion
	printf("Calibrated pres. = %6.2f Pa\n",(float)P/256.0);
	//leer la humedad medida por el sensor
	bme280Humidity(&H);
	//imprimir en la terminal la humedad
	printf("Calibrated hum. = %2.2f%%\n",(float)H/1024.0);
  
    
    char buf[30];
    float numero = (float)T/100.0;
    sprintf(buf, "%f", numero);
	
    //imprimir en el LCD la temperatura
    char buf2[30] = "La temperatura :";
    
    lcdLoc(0x80);
    typeln(buf2);
    
    lcdLoc(0xC0);
    typeln(buf);
    
    

return 0;
} 
