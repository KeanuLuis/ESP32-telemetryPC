# ESP32-telemetryPC
Este proyecto es un sistema independiente de monitoreo de hardware. Consta de un servidor ligero (software de terceros) que suministra los datos, un script en Python que extrae la telemetría del sistema operativo y un cliente físico basado en un microcontrolador ESP32-C3 mini que visualiza la información en una pantalla OLED.

## Antes de empezar, asegúrate de tener instalados los siguientes programas:

Python 3.9 o superior: ¡Muy importante! Durante la instalación, asegúrate de marcar la casilla que dice "Add Python to PATH" en la primera pantalla.
Sitio para descargar [Python](https://www.python.org/downloads/).

IDE arduino [Arduino](https://www.arduino.cc/en/software/).

LibreHardwareMonitor[LHM](https://sourceforge.net/projects/librehardwaremonitor.mirror/).



### FASE 1 Configurar el servidor.
Desgargar este software es muy importe ya que este sera el encargado de suministrar los datos de nuestro equipo de computo (PC). 

Una ves que se haya descargado LHM, es necesario ejecutarlo con los permisos de administrador.
Asegúrate de marcar las siguientes opciones para que el programa se inicie junto con Windows y minimizado.
<img width="225" height="280" alt="image" src="https://github.com/user-attachments/assets/4c90ef85-6c41-49e7-8cf2-da9c53fcc2cf" />

En esa misma sección de opciones, asegúrate de seleccionar la pestaña  ***Remote Web Server y, ahí, la opción Run.*** 
La imagen siguiente ilustra lo deseado. 
<img width="300" height="305" alt="image" src="https://github.com/user-attachments/assets/3ccdf9bb-3475-48be-9539-1f350d1087d4" />
En seguida de Run esta Interface/Port ***asegurate que por predeteminado este el puerto 8085**
<img width="324" height="307" alt="image" src="https://github.com/user-attachments/assets/1384a55a-3fe3-4e4c-bfab-84653594c44a" />
<img width="255" height="24" alt="image" src="https://github.com/user-attachments/assets/a6e74e29-3e2a-4848-9d1b-49f3218ac963" />

***Es importante asegurarse que el pueto 8085 no este ocupado por alguna otra razon ya que es importante para el script que ese puerto este sin usarse***

Tu PC necesita algunas librerías para poder procesar y enviar los datos. Abre tu terminal (PowerShell o CMD) y copia y pega el siguiente comando:

`pip install flask psutil requests`

Nota: Si el comando anterior te da error, intenta usar 

`py -m pip install flask psutil requests`

### FASE 2 Hardware y conexiones.

***La siguiente imagen solo es un ejemplo ilustrativo de como deben de ser las conexiones y en que pines***
<img width="971" height="599" alt="diagrama" src="https://github.com/user-attachments/assets/cf70c265-ad59-4861-b1f2-01c48badfe34" />

Una vez realizado lo anterior es abrir el software de arduino y decargar la placa esp32-c3 mini, para ello dirigete hacia placas y busca esp32 by Espressif.
<img width="207" height="398" alt="image" src="https://github.com/user-attachments/assets/33a79a4d-4387-421d-84be-82aebf8bd60d" />

Lo que sigue es, descargada la placa solo es seleccionarla en la seccion de herramientas de la siguiente manera.
<img width="864" height="306" alt="image" src="https://github.com/user-attachments/assets/16830d47-8156-4118-a3f1-669bbc342b08" />


Y por ultimo las librerias, ve a Programa > Incluir Librería > Administrar Bibliotecas... e instala las siguientes librerías exactas

`Adafruit GFX Library`

<img width="220" height="308" alt="image" src="https://github.com/user-attachments/assets/42365a99-1803-4c3e-a15b-45da2ed2f78d" />

`Adafruit SSD1306`

<img width="212" height="314" alt="image" src="https://github.com/user-attachments/assets/bf0ee4b5-37a1-4e62-bb50-0c043a331999" />

`ArduinoJson` 

***Asegúrate de que sea la versión 7 o superior***
<img width="200" height="307" alt="image" src="https://github.com/user-attachments/assets/8be5f234-14a8-482e-b0f5-0590c74b5646" />

`WiFiManager`

<img width="208" height="321" alt="image" src="https://github.com/user-attachments/assets/d93d3485-c168-40a2-8a0b-e92ef3fc97d1" />

### FASE 3 Final.

Con Libre Hardware Monitor abierto en segundo plano, es hora de encender nuestro puente de datos. Abre tu terminal en la carpeta donde descargaste los archivos del proyecto y ejecuta el script con este comando:

`python monitor.py`

Abre el archivo .ino de este proyecto en tu Arduino IDE.

Conecta tu ESP32-C3 mini por USB.

Recuerda cambiar las siguientes líneas del código con su respectivos datos:

```C++
const char\* ssid = "YOUR\_WIFI";
const char\* password = "YOUR\_WIFI\_PASSWORD";
String serverName = "http://YOUR\_LOCAL\_MACHINE\_IP:5000/stats"; 
```
Y por ultimo sube tu código. 

para ver cual es la IPv4 es con el siguiente comando en CMD 

`ipconfig`

### Imagenes del resultado y funcionamiento. 

<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/5196973c-a89a-46fb-a0bf-acb3b86d9a65" />

<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/19827777-a522-4a90-9642-433f836d6122" />

<ins> Pantalla de Temperaturas </ins>
<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/27dc4a77-c3fd-424b-b57a-23ba878b4598" />

<ins> Pantalla de porcentaje </ins>
<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/aaccfbf2-74b2-4a58-9a9e-26d8df9958c0" />

<ins> Pantalla de Disco </ins>
<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/7c366e61-4a99-481a-9591-5d3ec0a0d48c" />

<ins> Pantalla de Tiempo de ejecución de PC </ins>
<img width="1536" height="1536" alt="image" src="https://github.com/user-attachments/assets/a3fdeca1-5ba8-4b79-b9ff-7d3e47827e62" />







