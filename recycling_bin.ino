#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

// Configuración de red Wi-Fi
const char* ssid = "*******";   // Mi red wifi
const char* password = "*******";  // Contraseña de mi red

// Configuración de CallMeBot
const char* callmebot_api_url = "https://api.callmebot.com/whatsapp.php?";
const char* to_number = "+569********"; // Mi Whatsapp
const char* callmebot_api_key = "******"; // API Key de CallMeBot

// Configuración de sensor ultrasónico
#define TRIGGER_PIN D5  // Pines de conexión
#define ECHO_PIN D6
const float max_distance = 54.3; // Distancia máxima de medición en cm
const float threshold_distance = max_distance * 0.25; // 25% de la distancia máxima

WiFiClientSecure client;  // Cliente Wi-Fi seguro para HTTPS

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Conectar a Wi-Fi
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Deshabilitar verificación SSL (si el servidor no tiene un certificado SSL válido)
  client.setInsecure();
}

long getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = (duration * 0.0343) / 2;  // 0.0343 es la velocidad del sonido en cm/us
  return distance;
}

void sendWhatsAppMessage() {
  String message = "Contenedor al 75% de su capacidad, ¡es momento de vaciarlo!"; // Colocar mensaje que se enviara a whatsapp
  String encoded_message = "";  // Codificación de mensaje (por ejemplo, '%20' para espacio)
  
  // Codificar el mensaje para URL (espacios, caracteres especiales)
  for (unsigned int i = 0; i < message.length(); i++) {
    char c = message.charAt(i);
    if (c == ' ') encoded_message += "%20";
    else encoded_message += c;
  }

  String api_url = String(callmebot_api_url) + "phone=" + to_number + "&text=" + encoded_message + "&apikey=" + callmebot_api_key;

  Serial.println("URL Generada: " + api_url);

  HTTPClient http;
  http.begin(client, api_url);  // Usar client como primer argumento para la conexión HTTPS
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.println("Mensaje enviado correctamente: " + String(httpCode));
  } else {
    Serial.println("Error al enviar el mensaje: " + String(httpCode));
  }

  http.end();
}

void loop() {
  long distance = getDistance();
  Serial.print("Distancia medida: ");
  Serial.println(distance);
  
  // La alerta se envía cuando la distancia es menor al umbral, es decir, cuando el contenedor está más lleno
  if (distance < threshold_distance) {
    sendWhatsAppMessage();
    delay(3600000); // Esperar 1 hora antes de volver a medir
  }

  delay(10000); // Medición cada 10 segundos
}

