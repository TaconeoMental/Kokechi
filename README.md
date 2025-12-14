# WiFi Keylogger

<img width="60%" src="/assets/schematic.png" />

# Instalación
El código está escrito en torno al framework PlatformIO, que maneja todas las dependencias y herramientas particulares para cada controlador automáticamente. Pueden encontrar su documentación, junto con instrucciones para instalarlo [acá](https://docs.platformio.org/en/latest/core/installation/index.html).


Es importante flashear el firmware de cada placa por separado antes de armar el circuito completo por la configuración que hay para la alimentación de cada componente.
## Teensy 4.0
El Teensy hace uso de un puerto nativo que tiene (medio escondido) que le permite actuar como host USB, lo que permite conectar un teclado en este caso. Por otro lado, también hace uso de su puerto serial principal (TX0 y RX0, conocido también como su puerto micro USB) para emular un dispositivo HID al ser conectado a un computador. Por lo anterior, recomiendo tener muy en cuenta que es dificil ingeniárselas para abrir un monitor serial y tener feedback para la depuración del código. En mi caso, hice toda la depuración antes de emular el dispositivo HID.

Para flashearlo basta con correr el siguiente comando en la raíz del proyecto:
 ```bash
 $ pio run -e teensy --target upload
 ```
 
 ## ESP32
 Este componente es más simple y por su uso es posible usar uno de sus puertos seriales para depurar código a través de la consola. Se escogió este microcontrolador particularmente por la cantidad de puertos seriales físicos que tiene adicioneles al principal.
 
 Para flashear el firmware normalmente, cambiar la siguiente línea en el archivo *src/esp32/include/mini_log_conf.h*
 ```cpp
 #define LOGGER_VERBOSITY_LEVEL LoggerVLevelTrace
 ```
 por la siguiente:
  ```cpp
 #define LOGGER_VERBOSITY_LEVEL LoggerVLevelOff
 ```
 Posteriormente correr el siguiente comando en la raíz del proyecto:
 ```bash
 $ pio run -e esp --target upload
 ```
 
 Si se requiere depurar de alguna forma a través de un monitor serial, no se debe cambiar el macro anterior y se debe correr el siguiente comando:
  ```bash
 $ pio run -e esp --target upload && pio device monitor -e esp --filter esp32_exception_decoder -b 115200 
 ```
