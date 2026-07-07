// #include <Arduino.h>
#include "Sensor.h"
#include "MQTTClient.h"
#include <ArduinoJson.h>   // pra enviar/receber mensagens em JSON

MQTTClient client;
DynamicJsonDocument doc1(256);
DynamicJsonDocument doc2(256);

// > Função para alternar energia de LED ----------------------------------
// void Sensor::setLed (bool x){
//   digitalWrite(PIN_LED_A, x ? HIGH : LOW);
// }

// > Função para alternar energia Rele ----------------------------------
void Sensor::setToggleRele (bool x){
  digitalWrite(_RELE_PIN, x ? HIGH : LOW);
}

// > Recepção de mensagem MQTT ----------------------
void Sensor::callback (char* topic, byte* payload, unsigned int length){
  DynamicJsonDocument doc(256);
  if (deserializeJson(doc, payload, length) == DeserializationError::Ok) {
    // if (strcmp(topic, "grupo5/sensor/led") == 0){
    //   bool estado = doc["led"];
    //   setLed(estado);
    // }
    // else if (strcmp(topic, "grupo5/sensor/rele") == 0){
    //   bool estado = doc["rele"];
    //   setToggleRele(estado);
    // }
  }
  else Serial.println("Erro JSON.");
}

// Função de inicialização: --------------------------
void Sensor::start (const char* clientID, const uint8_t* pins ,const uint8_t* modes, int size){
  client.begin("corredor-001");
  Serial.println("  - connection success.");
  
  // Configurando pinos pre-definidos em main.cpp:
  // for (int i =0; i < size; i++) pinMode(pins[i], modes[i]);
  pinMode(pins[0], modes[0]);
  pinMode(pins[1], modes[1]);
  _LDR_PIN =pins[0];
  _RELE_PIN =pins[1];

  Serial.println("  - configuration success.");
}

// Função de atualização ------------------------------
void Sensor::update (){
  client.loop();

  // Montando JSON para luminosidade:
  doc1.clear();
  doc1["clientMqttID"] =client.getID ();
  doc1["type"] ="SE";
  doc1["luminosidade"] =analogRead(_LDR_PIN);
  char buffer1[128];
  serializeJson(doc1, buffer1);

  // Montando JSON para emergencia:
  doc2.clear();
  doc2["clientMqttID"] =client.getID ();
  doc2["type"] ="SE";
  doc2["emergencia"] =digitalRead(_RELE_PIN) == HIGH ? 1 : 0;
  char buffer2[128];
  serializeJson(doc2, buffer2);

  // Publicando:
  client.publish(buffer1, buffer2);
}
