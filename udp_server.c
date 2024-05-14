/********************** Include Files **************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./bme280.h"
#include "lcd.h"
#include <time.h>
#include "blink.h"

/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/
//puerto del server
#define SERVER_PORT 5005

//tamaño máx del buffer
#define BUFFSIZE 1024

//

//
// Start of MAIN program
//

// función que devuelve la fecha actual en formato
// DD/MM/AAAA, HH:MM
char *fecha() {
    //tiempo actual
    time_t t = time(NULL);
    
    //convertir time_t en dia, hora etc
    struct tm *tm = localtime(&t);
    
    int year = tm -> tm_year + 1900;
    int month = tm -> tm_mon + 1;
    int day = tm -> tm_mday;
    int hour = tm -> tm_hour;
    int minute = tm -> tm_min;
    
    static char date[100];
    sprintf(date,"%02d/%02d/%04d, %02d:%02d", day, month, year, hour, minute);
    return date;
    }

//programa principal
int main() {
    
    //variables relacionadas con la temperatura, presión y humedad
    int T, P, H;
    
    int sock, num;
    socklen_t len;
    
    //buffer para la recogida de datos
    char buffer[BUFFSIZE];
    
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in serveraddr, clientaddr;
    
    //contador de minutos
    int m;

     // Configure the GPIOs
    configGPIO();

    // Create UDP socket:
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error while creating socket\n");
        return 1;
    }
    
     // receive the datagram
    len = sizeof(clientaddr);
    
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(SERVER_PORT);
    

    if (bind(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) {
        printf("Couldn't bind socket\n");
        return 1;
    }
    printf("Socket Binding OK\n");
    printf("Listening for incoming messages...\n\n");
    
    
    // Start listening
    while (1) {
        
        //receive message from server
        num = recvfrom(sock, buffer, BUFFSIZE, MSG_WAITALL,
                       (struct sockaddr *)&clientaddr, &len);
        
        // Blink for 0.1 seconds when message received:
        blink(0.1);    
            
        buffer[num] = '\0';
                       
        inet_ntop(AF_INET, &(clientaddr.sin_addr), str, INET_ADDRSTRLEN);

        printf("New message from %s:%d -- %s\n", str, ntohs(clientaddr.sin_port), buffer);   
        
        //comando de entrada
        char comando[6];
        //nombre del archivo de salida
        char filename[30];
        //minutos totales
        int minutos;
        
        //buffer de temperatura
        char buft[30];
        //buffer de humedad
        char bufh[30];
        //buffer de presión
        char bufp[30];
        
        char buf2t[30] = "La temperatura :";
        char buf2h[30] = "La humedad :";
        char buf2p[30] = "La presion :";
            
           if (wiringPiSetup () == -1) exit (1);

              fd = wiringPiI2CSetup(I2C_ADDR);

            //inicialización del lcd
              lcd_init();
            
        // si recibo caracter t que calcule teperatura      
         if (buffer[0] == 't'){
             //lectura de la temperatura en el sensor
             bme280Temperature(&T);
             T -= 150; 
             //imprime la temperatura en la terminal
             printf("Calibrated temp. = %3.2f C\n",(float)T/100.0);
             
            float numero = (float)T/100.0;
            sprintf(buft, "%3.2f", numero);
            
            //imprime el dato en el lcd
            lcdLoc(0x80);
            typeln(buf2t);
            
            lcdLoc(0xC0);
            
            strcat(buft," C");
            typeln(buft);
            
        // si recibo caracter p que calcule presion 
         } else if (strcmp(buffer,"p") == 0){
             //lectura de la presión en el sensor
             bme280Pressure(&P);
             //imprime la presión en la terminal
             printf("Calibrated pres. = %6.2f Pa\n",(float)P/256.0);
             
            float numerop = (float)P/256.0;
            sprintf(bufp, "%6.2f", numerop);
            
            //imprime el dato en el lcd
            lcdLoc(0x80);
            typeln(buf2p);
            
            lcdLoc(0xC0);
            strcat(bufp," Pa");
            typeln(bufp);
            
            
        // si recibo caracter h que calcule humedad  
        } else if (strcmp(buffer,"h") == 0){
            //lectura de la humedad en el sensor
             bme280Humidity(&H);
             //imprime la humedad en la pantalla
             printf("Calibrated hum. = %2.2f%%\n",(float)H/1024.0);
             
            float numeroh = (float)H/1024.0;
            sprintf(bufh, "%2.2f", numeroh);
            
            //imprime el dato en el lcd
            lcdLoc(0x80);
            typeln(buf2h);
            
            lcdLoc(0xC0);
            strcat(bufh," %");
            typeln(bufh);
            
        // si recibo el comando print y el nombre de un fichero 
        // se imprime en mi fichero de texto los parametros y la fecha
        } else if (sscanf(buffer,"%s %s", comando, filename) == 2 && strcmp(comando,"print") == 0){
            
             //ruta del archivo
             char ruta[100]= "/home/ADE-MASTER/Desktop/";
             //concatenar el nombre con la extensión
             strcat(filename, ".txt");
             strcat(ruta, filename);
             
             //abrir el archivo
             //si no existe, lo crea
             //si existe, empieza a escribir desde la última línea
             FILE *file = fopen(ruta, "a+");
             
             //lectura de la temperatura en el sensor
             bme280Temperature(&T);
             T -= 150;
             //lectura de la presión en el sensor
             bme280Pressure(&P);
             //lectura de la humedad en el sensor
             bme280Humidity(&H);
             
             //escribe la fecha actual en el fichero especificado
             fprintf(file, fecha());
             fprintf(file,"\n");
             
             //escribe los parámetros T, P y H en el fichero especificado
             fprintf(file, "T = %3.2f C\n",(float)T/100.0);
             fprintf(file, "P = %6.2f Pa\n",(float)P/256.0);
             fprintf(file, "H = %2.2f%%\n",(float)H/1024.0);
             
             //salto de línea
             fprintf(file, "\n");
             
             //cierre del fichero
             fclose(file);
             lcdLoc(0x80);
             typeln(filename);
             
             lcdLoc(0xC0);
             typeln("ha sido escrito");
            
             printf("Escritura de %s realizada con exito\n", filename);
            
        // si recibo el comando start minutos y el nombre de un fichero
        // se imprime en mi fichero de texto los datos recopilados durante esos x minutos
        } else if (sscanf(buffer,"%s %d %s", comando, &minutos, filename) == 3 && strcmp(comando,"start") == 0){
            
             char ruta[100]= "/home/ADE-MASTER/Desktop/";
             strcat(filename, ".txt");
             strcat(ruta, filename);
             FILE *file = fopen(ruta, "a+");
             
             fprintf(file, "fecha, hora, T (C), P (Pa), H (%%)\n");
             m = 0;
             
             while (m < minutos){
             bme280Temperature(&T);
             T -= 150;
             bme280Pressure(&P);
             bme280Humidity(&H);
             
             fprintf(file, fecha());
             fprintf(file, ", %3.2f, ",(float)T/100.0);
             fprintf(file, "%6.2f, ",(float)P/256.0);
             fprintf(file, "%2.2f\n",(float)H/1024.0);
             
             m += 1;
             
             float numfloat;
            
             //se muestran los datos por pantalla cada 20s
             
             //temperatura
             numfloat = (float)T/100.0;
             sprintf(buft, "%3.2f", numfloat);
             lcdLoc(0x80);
             typeln(buf2t);
            
             lcdLoc(0xC0);
             strcat(buft," C");
             typeln(buft);
             
             sleep(20);
             ClrLcd();
             //presion
             numfloat = (float)P/256.0;
             sprintf(bufp, "%6.2f", numfloat);
             lcdLoc(0x80);
             typeln(buf2p);
            
             lcdLoc(0xC0);
             strcat(bufp," Pa");
             typeln(bufp);
             
             sleep(20);
             ClrLcd();
             //humedad 
             numfloat = (float)H/1024.0;
             sprintf(bufh, "%2.2f", numfloat);
             lcdLoc(0x80);
             typeln(buf2h);
            
             lcdLoc(0xC0);
             strcat(bufh," %");
             typeln(bufh);
            
             sleep(20);
             ClrLcd();
              }
              
             fprintf(file, "\n");
             
             fclose(file);
             lcdLoc(0x80);
             typeln(filename);
            
             lcdLoc(0xC0);
             typeln("ha sido escrito");
            
             printf("Escritura de %s realizada con exito\n", filename);
                  
        // If receive x char, close socket:     
        } else if (buffer[0] == 'x'){
             printf("Closing socket...\n");
             break;
             
        } else {
            printf("No se que quieres\n");
        }
           
        
                       
        // Send echo back:
        sendto(sock, &buffer, strlen(buffer), MSG_CONFIRM,
               (struct sockaddr *)&clientaddr, len);
    }

    

    close(sock);
}
