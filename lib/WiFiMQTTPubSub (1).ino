#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define trigPin 18
#define echoPin 19
#define relePin 5

#define MSG_SIZE 1024
#define STATION_ID "STT001"

const char* ssid = "ProjetoMInDS";
const char* password = "Doi39x-Wa!";

// JSON
DynamicJsonDocument mqttMsg(MSG_SIZE);

// Broker MQTT
const char* mqtt_server = "192.168.1.114";
const int mqtt_port = 1883;
const char* mqtt_topic = "rpiot/curso/alerta";

WiFiClient espClient;
PubSubClient mqttClient(espClient);
JsonDocument doc;

/*--------------------------------------------------------------------------*/
void initializeJson() {
  /* message pattern for MQTT communication */
  mqttMsg.clear();
  mqttMsg["stationId"] = STATION_ID;
}

/*--------------------------------------------------------------------------*/
//
/*--------------------------------------------------------------------------*/
bool serializeAndSend(const char *topic) {
  char sendBuffer[MSG_SIZE];

  serializeJson(mqttMsg, sendBuffer);
  Serial.println("MQTT msg :");
  Serial.println(sendBuffer);

  return mqttClient.publish(topic, sendBuffer, strlen(sendBuffer));

}

// Callback: executado ao receber mensagem no tópico inscrito
void callback(char* topic, byte* payload, unsigned int length) {
  int alarme = 0;
  String message;
  Serial.print("MQTT Recv: ");
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  deserializeJson(doc, message);
  alarme = doc["alerta"];

  Serial.println("Alarme:");
  Serial.println(alarme);
  if (alarme) {
    digitalWrite(relePin, LOW);
  } else {
    digitalWrite(relePin, HIGH);
  }
}

void setup_wifi() {
  delay(10);
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi conectado com IP: " + WiFi.localIP().toString());
}

void verify_wifi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi desconectado! Tentando reconectar...");
    setup_wifi();  // reconecta usando mesma função do setup
    return; // espera conectar antes de seguir
  }
}

// conecta no MQTT e se inscreve para escuta de mensagens em tópico
void reconnect_mqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (mqttClient.connect("ESP32Client")) {
        Serial.println("Conectado");
        // se inscreve no tópico para escutar mensagens
        mqttClient.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" tentando novamente em 5s...");
      delay(5000);
    }
  }
}

float distance_measure() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance == 0 || distance > 400) {
    return -1.0; // Sem leitura válida
  }
  
  return distance;
}

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relePin, OUTPUT);
  
  digitalWrite(relePin, HIGH); // Inicialmente desligado

  setup_wifi();
  mqttClient.setServer(mqtt_server, mqtt_port);
  // receber mensagem no tópico inscrito
  mqttClient.setCallback(callback);
}

void loop() {
  char msg[50];
  int alerta = 0;

  verify_wifi();
  
  if (!mqttClient.connected()) {
    reconnect_mqtt();
  }
  mqttClient.loop();

  float distance = distance_measure();
  // Publicar no MQTT
  if (distance < 15) {
      alerta = 1;
  } else {
      alerta = 0;        
  }

  initializeJson();
  mqttMsg["alerta"] = alerta;
  if (serializeAndSend(mqtt_topic))
      Serial.println("MQTT: publish success!");
  else
      Serial.println("MQTT: publish error!");

  delay(1000);
}
