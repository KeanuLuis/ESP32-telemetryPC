# ESP32-telemetryPC
Un dashboard físico y minimalista en una pantalla OLED que muestra el rendimiento del hardware de la computadora en tiempo real  a través de la red local.
Al realizar tareas demandantes es vital monitorear el rendimiento del hardware. Sin embargo, los monitores por software tradicionales interrumpen el flujo de trabajo, consumen espacio valioso en los monitores principales o quedan ocultos detras de la pantalla completa.
---------------------------------------------------------------------------------------------------------------------

Este proyecto es un sistema de monitoreo de hardware independiente. Consta de un servidor ligero en Python que extrae la telemetria del sistema operativo y un cliente fisico basado en un microcontrolador ESP32-C3 mini que muestra los datos en una pantalla OLED.

--Componentes y Herramientas utilizadas--
-Hardware- ESP32-C3 mini|Pantalla OLED 128x64|-
-Backend/API- Python|Flask|psutil|LibreHardwareMonitor|-
-Firmware C++|Arduino IDE|ArduinoJson,Adafruit GFX|
-Sistema Operativo- Windows 10/11|-
--


Para la interfaz y la experiencia del usuari, apliqué los principios sólidos de interacción humano-computadora, la prioridad fue la visibilidad del estado dels sistema a un simple vistazo.
