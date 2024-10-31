Contenedor de Reciclaje Inteligente

Este proyecto es un contenedor de reciclaje inteligente que utiliza un sensor ultrasónico y un microcontrolador NodeMCU ESP8266 para monitorear el nivel de llenado del contenedor.
Cuando el contenedor alcanza el 75% de su capacidad, envía una alerta de WhatsApp para que pueda vaciarse antes de llenarse por completo.

 Tabla de Contenidos
1. [Descripción del Proyecto](#descripción-del-proyecto)
2. [Componentes Utilizados](#componentes-utilizados)
3. [Diagrama de Conexión](#diagrama-de-conexión)
4. [Código](#código)
5. [Configuración](#configuración)
6. [Instalación de Librerías](#instalación-de-librerías)


Descripción del Proyecto

Este contenedor de reciclaje inteligente monitorea el nivel de llenado en tiempo real. A través de un sensor ultrasónico,
mide la distancia entre la tapa y los residuos dentro del contenedor. Si la distancia es inferior al 25% de su capacidad total
(es decir, cuando el contenedor está al 75% de su capacidad), envía un mensaje de WhatsApp a un número predefinido para notificar que es momento de vaciarlo.

Objetivo

Optimizar el manejo de residuos y asegurarse de que el contenedor sea vaciado oportunamente, evitando que se llene por completo.

 Componentes Utilizados

- NodeMCU ESP8266**: Microcontrolador WiFi para la conexión a internet.
- Sensor ultrasónico HC-SR04**: Para medir la distancia y calcular el nivel de llenado.
- Fuente de alimentación (5V)**: Para alimentar el NodeMCU y el sensor.
- Conexiones y cables**.

Diagrama de Conexión

- TRIG del HC-SR04 al pin D1 del NodeMCU.
- ECHO del HC-SR04 al pin D2 del NodeMCU.
- VCC y GND del HC-SR04 a 5V y GND del NodeMCU, respectivamente.



Código

El código para este proyecto se encuentra en el archivo `recycling_bin.ino`.

Configuración

1. Configura el archivo de código `recycling_bin.ino` con los siguientes datos:
   - Nombre de la red Wi-Fi: `aukanantu_2.4G`
   - Contraseña de la red Wi-Fi: `Francisco27`
   - SID de la cuenta de Twilio: `AC73d796744de34018a1f3d7a3639eec4e`
   - Token de autenticación de Twilio: `747aca2ae259315c3b1fdaa1b7fec845`
   - Número de teléfono de Twilio: `whatsapp:+14155238886`
   - Número de teléfono receptor: `whatsapp:+56986731126`



Instalación de Librerías


1. ESP8266WiFi: Para conectar el NodeMCU a una red Wi-Fi.
2. WiFiClientSecure: Para realizar la conexión HTTPS con Twilio.
3. Base64: Para codificar las credenciales de autenticación en el formato que Twilio requiere.



