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
    * Android:[] ()
    * Apple: [Network Debugger: TCP/UDP] (https://apps.apple.com/es/app/network-debugger-tcp-udp/id1562086552)


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

### Ejemplo

### Código

### Inicializar el UDP Server cuando arranque del sistema

Para que el UDP Service se inicie automáticamente al encender la Raspberry Pi, hay que crear un archivo de servicio. Al [archivo de servicio](https://github.com/IruneyEdurne/proyecto/tree/main/codigo/udp_server.service) proporcionado en este proyecto hay que cambiarle el campo _ExecStart_ con el directorio en el que se haya creado el ejecutable.

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
