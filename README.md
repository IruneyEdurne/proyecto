# Servidor UDP para medida de **temperatura, humedad y presión ambiental**

Servidor UDP en C que arranca con el sistema operativo Linux de la Raspberry Pi y que mediante comandos mostrará la temperatura, humedad y presión en una pantalla LCD. También se podrán almacenar los datos en ficheros de texto.

## Herramientas 🔧

En el proyecto se han utilizado:
* Raspberry Pi 4
* Sensor de humedad, temperatura y presión BME280
* Diodo LED

Para la realización del proyecto se han necesitado las siguientes herramientas de software:
* GCC compiler: para compilar el código en C
* App para teléfonos que actúe como UDP Client
    * Android: [UDP](https://play.google.com/store/apps/details?id=com.jamstudios.udp_sender)
    * Apple: [Network Debugger: TCP/UDP](https://apps.apple.com/es/app/network-debugger-tcp-udp/id1562086552)


## Comenzando 🚀

Comienza clonando el proyecto en tu repositorio local.

```
git clone https://github.com/IruneyEdurne/proyecto
```
Dentro del proyecto podrás encontrar las siguientes carpetas:

* [WiringPi](https://github.com/IruneyEdurne/proyecto/tree/main/WiringPi): Carpeta que contiene los recursos de la librería WiringPi.
* [codigo](https://github.com/IruneyEdurne/proyecto/tree/main/codigo): Contiene el [código](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.c) en c del programa y el archivo de configuración [udp_server.service](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.service).
* [ejemplo](https://github.com/IruneyEdurne/proyecto/tree/main/ejemplo): Ejemplo sencillo para comprobar la lectura del sensor.
* [lib](https://github.com/IruneyEdurne/proyecto/tree/main/lib): Carpeta que contiene librerías utilizadas para el proyecto.

## Proyecto ⚙️

La carpeta [ejemplo](https://github.com/IruneyEdurne/proyecto/tree/main/ejemplo) contiene un ejemplo sencillo para comprobar que el sensor lee los datos correctamente y que el LCD funciona. El programa final es el archivo [udp_server.c](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.c). 

### [Ejemplo 📂](https://github.com/IruneyEdurne/proyecto/tree/main/ejemplo)

Al ejecutarlo, se mostrarán en la terminal de Linux los valores de temperatura, humedad y presión medidos. En la pantalla del LCD se mostrará la temperatura medida.

### [Código 📂](https://github.com/IruneyEdurne/proyecto/tree/main/codigo)

Los comando para interactuar con el servidor son los siguientes:

* `t`: Muestra en el LCD la temperatura en ºC.
* `h`: Muestra en el LCD el tanto por ciento (%) de humedad.
* `p`: Muestra en el LCD la presión en Pa.
* `print [archivo]`: Escribe la fecha actual y los parámetros de temperatura, humedad y presión medidos en este instante en el archivo `[archivo]`. Si este no existe en el directorio actual, lo crea. Si ya existía, comenzará a escribir en la última línea del archivo. En el LCD se imprimirá un aviso de que el archivo `[archivo]` ha sido escrito.
* `start [minutos] [archivo]`: Escribe la fecha actual y los parámetros de temperatura, humedad y presión medidos durante `[minutos]` minutos en el archivo `[archivo]`. Si este no existe en el directorio actual, lo crea. Si ya existía, comenzará a escribir en la última línea del archivo. La escritura la hace cada minuto. Mostrará en el LCD, cambiando cada 20 segundos, la T, P y H que se están midiendo cada minuto. Al finalizar, en el LCD se imprimirá un aviso de que el archivo `[archivo]` ha sido escrito. Durante el tiempo en el que se realice la lectura, especificado por el parámetro `[minutos]`, cualquier comando que llegue será ignorado.

**⚠️ ADVERTENCIA: Para que los comandos de print y start funcionen correctamente, deberás cambiar los campos de ruta al archivo por una ruta válida en tu Raspberry.**
```
//ruta donde se encuentra el fichero
char ruta[100]= "/mi/ruta/";
```

Para crear el ejecutable, utiliza el siguiente comando en la terminal:

```
gcc -o ejecutable udp_server.c ../lib/bme280.c ../lib/lcd.c ../lib/blink.c -lwiringPi
```

Una vez inicializado el servidor, cada vez que se reciba un mensaje, la luz led parpadeará. Si el LED parpadea, pero no se imprime nada en el LCD, querrá decir que el comando escrito es incorrecto.

**💡Establecer la conexión del UDP client con el UDP server**
Para establecer la conexión en la app que sirve como UDP client, hay que especificar la red en la que está conectado el servidor y su puerto.
El puerto del server es el 5005, que se especifica al comienzo del archivo [udp_server.c](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.c):
```
#define SERVER_PORT 5005
```

### Inicializar el UDP Server cuando arranque el sistema

Para que el UDP Server se inicie automáticamente al encender la Raspberry Pi, hay que crear un archivo de servicio. Al [archivo de servicio](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.service) proporcionado en este proyecto hay que cambiarle el campo `ExecStart` con el directorio en el que se haya creado el ejecutable.

```
ExecStart = /ruta/al/ejecutable
```

Este fichero hay que trasladarlo a la carpeta _system_ dentro del directorio _systemd_, donde se encuentran el resto de servicios.

Para habilitar el servicio en el arranque:
```
sudo systemctl enable udp_server.service
```

Se reinicia el sistema y al arrancar se puede comprobar el estado del servicio con:

```
sudo systemctl status udp_server.service
```

## Autoras ✒️

* Irune F.
* Edurne P.
