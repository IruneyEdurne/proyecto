//
// BME280 sample app
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
//libreria sensor
#include "../lib/bme280.h"
//librería I2C
//#include <wiringPiI2C.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "../lib/lcd.h"

// delay between samples in microseconds
#define DELAY 1000000







// Dirección I2C del dispositivo LCD
//#define LCD_ADDR 0x27


//#define LCD_CMD 0x00    // Comando de control del LCD
//#define LCD_DATA 0x40   // Datos del LCD

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
//static int file_i2c = 0;

//// Función para enviar un comando al LCD
//void lcd_send_cmd(int fd, unsigned char cmd) {
    //wiringPiI2CWriteReg8(fd, 0x00, cmd);
//}

//// Función para enviar un carácter al LCD
//void lcd_send_char(int fd, char data) {
    //wiringPiI2CWriteReg8(fd, 0x40, data);
//}

//// Función para inicializar el LCD
//void lcd_init(int fd) {
    //lcd_send_cmd(fd, LCD_CMD_FUNCTION_SET | 0x08); // 2 líneas de pantalla
    //lcd_send_cmd(fd, LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);
    //lcd_send_cmd(fd, LCD_CMD_CLEAR); // Borrar pantalla
    //lcd_send_cmd(fd, LCD_CMD_ENTRY_MODE | LCD_ENTRY_MODE_INCREASE); // Desplazamiento de texto
//}

//// Función para escribir texto en el LCD
//void lcd_write_text(int fd, const char *text) {
    //while (*text) {
        //lcd_send_char(fd, *text++);
    //}
//}













int main(int argc, char *argv[])
{
//int i;
int T, P, H;
	if (wiringPiSetup () == -1) exit (1);

  fd = wiringPiI2CSetup(I2C_ADDR);

  //printf("fd = %d ", fd);

  lcd_init(); // setup LCD
  
	bme280Temperature(&T);
	T -= 150; 
	printf("Calibrated temp. = %3.2f C\n",(float)T/100.0);
	bme280Pressure(&P);
	printf("Calibrated pres. = %6.2f Pa\n",(float)P/256.0);
	bme280Humidity(&H);
	printf("Calibrated hum. = %2.2f%%\n",(float)H/1024.0);
	
	
    
    
  
    
    char buf[30];
    float numero = (float)T/100.0;
    sprintf(buf, "%f", numero);
    
    char buf2[30] = "La temperatura :";
    
    lcdLoc(0x80);
    typeln(buf2);
    
    lcdLoc(0xC0);
    typeln(buf);
    
    

return 0;
} 
