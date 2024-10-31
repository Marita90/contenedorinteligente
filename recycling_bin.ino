#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Configuración de red Wi-Fi
const char* ssid = "aukanantu_2.4G";
const char* password = "Francisco27";

// Configuración de Twilio
const char* twilio_host = "api.twilio.com";
const int twilio_port = 443;
const char* account_sid = "TU_ACCOUNT_SID"; // Reemplaza con tu SID de cuenta Twilio
const char* auth_token = "TU_AUTH_TOKEN";   // Reemplaza con tu token de autenticación Twilio
const char* from_number = "whatsapp:+14155238886"; // Número proporcionado por Twilio
const char* to_number = "whatsapp:+56986731126";

// Configuración de sensor ultrasónico
#define TRIGGER_PIN D1
#define ECHO_PIN D2
const int max_distance = 100; // En centímetros
const int threshold_distance = max_distance * 0.25; // 25% de capacidad libre

WiFiClientSecure client;

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
}

long getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = (duration * 0.034) / 2;
  return distance;
}

void sendWhatsAppMessage() {
  if (client.connect(twilio_host, twilio_port)) {
    String message = "Contenedor al 75% de su capacidad, ¡es momento de vaciarlo!";
    
    String postData = "To=" + String(to_number) + "&From=" + String(from_number) + "&Body=" + message;
    client.printf("POST /2010-04-01/Accounts/%s/Messages.json HTTP/1.1\r\n", account_sid);
    client.printf("Host: %s\r\n", twilio_host);
    client.printf("Authorization: Basic %s\r\n", base64::encode(String(account_sid) + ":" + auth_token).c_str());
    client.printf("Content-Type: application/x-www-form-urlencoded\r\n");
    client.printf("Content-Length: %d\r\n\r\n", postData.length());
    client.print(postData);
    Serial.println("Mensaje de alerta enviado");
  }
  client.stop();
}

void loop() {
  long distance = getDistance();
  Serial.print("Distancia medida: ");
  Serial.println(distance);
  
  if (distance < threshold_distance) {
    sendWhatsAppMessage();
    delay(3600000); // Esperar 1 hora antes de volver a medir
  }

  delay(10000); // Medición cada 10 segundos
}
