#### Requisitos Previos

Antes de empezar, asegúrate de tener instalados los siguientes programas:



Python 3.9 o superior: ¡Muy importante! Durante la instalación, asegúrate de marcar la casilla que dice "Add Python to PATH" en la primera pantalla.



Arduino IDE: Con el gestor de tarjetas ESP32 ya instalado.



#### Fase 1: Configuración del Servidor (Tu PC)

##### 1\. Preparar Libre Hardware Monitor (LHM)

LHM es el programa que leerá los sensores físicos de tu computadora.



Descarga y abre Libre Hardware Monitor.



Haz clic derecho sobre el programa y selecciona "Ejecutar como administrador" (necesario para leer las temperaturas correctamente).



Ve a la carpeta important de este repositorio y revisa las capturas de pantalla para configurarlo. Asegúrate de activar la opción "Remote Web Server" en el puerto 8085.



##### 2\. Instalar las dependencias de Python

Tu PC necesita algunas librerías para poder procesar y enviar los datos. Abre tu terminal (PowerShell o CMD) y copia y pega el siguiente comando:


<pre>
###### pip install flask psutil requests
</pre>


(Nota: Si el comando anterior te da error, intenta usar py -m pip install flask psutil requests).



#### Fase 2: Hardware y Conexiones

##### 3\. Conectar la Pantalla OLED al ESP32-C3

Utiliza cables jumper para conectar tu pantalla OLED al microcontrolador. Sigue el diagrama visual que se encuentra en la imagen en README.md



Asegúrate de que los pines SDA y SCL coincidan exactamente con el diagrama.



#### Fase 3: Programación del ESP32

##### 4\. Instalar las librerías en Arduino IDE

Abre Arduino IDE, ve a Programa > Incluir Librería > Administrar Bibliotecas... e instala las siguientes librerías exactas (puedes ver la imagen librerias\_Arduiono.png como referencia):


<pre>
Adafruit GFX Library



Adafruit SSD1306



ArduinoJson (Asegúrate de que sea la versión 7 o superior)



WiFiManager (Por tzapu)

</pre>


#### 5\. Ejecutar el Servidor Python

Con Libre Hardware Monitor abierto en segundo plano, es hora de encender nuestro puente de datos. Abre tu terminal en la carpeta donde descargaste los archivos del proyecto y ejecuta el script con este comando:


<pre>
##### python monitor.py
</pre>





#### 6\. Subir el código



Abre el archivo .ino de este proyecto en tu Arduino IDE.



Conecta tu ESP32-C3 por USB.



Recuerda cambiar las siguientes líneas del código con su respectivos datos:
</pre>

const char\* ssid = "YOUR\_WIFI";

const char\* password = "YOUR\_WIFI\_PASSWORD";

String serverName = "http://YOUR\_LOCAL\_MACHINE\_IP:5000/stats"; 
</pre>



Selecciona la placa y el puerto correcto, y presiona Subir.

