/********************** Include Files **************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./bme280.h"


/********************* Type Definitions ************************/
/******************* Constant Definitions **********************/
#define SERVER_PORT 5005
#define BUFFSIZE 1024

//
// Start of MAIN program
//


int main() {
    
    int T, P, H;
    int sock, num;
    socklen_t len;
    char buffer[BUFFSIZE];
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in serveraddr, clientaddr;


     // Configure the GPIOs
    //configGPIO();

    // Create UDP socket:
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("Error while creating socket\n");
        return 1;
    }
    
     // recive the datagram
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
            
            
        buffer[num] = '\0';
                       
        inet_ntop(AF_INET, &(clientaddr.sin_addr), str, INET_ADDRSTRLEN);

        printf("New message from %s:%d -- %s\n", str, ntohs(clientaddr.sin_port), buffer);    
            
            
            
        // si recivo caracter t que calcule teperatura      
         if (buffer[0] == 't'){
             bme280Temperature(&T);
             T -= 150; 
             printf("Calibrated temp. = %3.2f C\n",(float)T/100.0);
        // si recivo caracter p que calcule presion 
         } else if (strcmp(buffer,"p") == 0){
             bme280Pressure(&P);
             printf("Calibrated pres. = %6.2f Pa\n",(float)P/256.0);
        // si recivo caracter h que calcule humedad  
        } else if (strcmp(buffer,"h") == 0){
             bme280Humidity(&H);
             printf("Calibrated hum. = %2.2f%%\n",(float)H/1024.0);
             
             
       
             
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
