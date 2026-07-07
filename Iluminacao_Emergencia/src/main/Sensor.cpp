#include <Arduino.h>
#include <ArduinoJson.h>   // pra enviar/receber mensagens em JSON
#include "Sensor.h"
#include "MQTTClient.cpp"
#include "MQTTClient.h"

MQTTClient client;
DynamicJsonDocument doc1(256);
DynamicJsonDocument doc2(256);

// > Função para alternar energia Rele ----------------------------------
void Sensor::setToggleRele (int x){
  digitalWrite(_RELE_PIN, (x == 1) ? HIGH : LOW);
}

// > Recepção de mensagem MQTT ----------------------
void Sensor::callback (const char* topic, byte* payload, unsigned int length){
  DynamicJsonDocument doc(256);
  DeserializationError error =deserializeJson(doc, payload, length);

  if (!error){
    // if (strcmp(topic, "rpiot/grupo3/corredor/esp32/emergencia") == 0){
      setToggleRele(doc["emergencia"]);
    // }
  }
  else {
    Serial.print("Callback: Erro JSON: ");
    Serial.println(error.c_str());
  }
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
  // Lê o valor analógico do sensor (0 a 4095)
  // Converte o valor do ADC para Voltagem (0.0V a 3.3V)
  // float ldrVolts = (analogRead(_LDR_PIN) * 3.3) / 4095.0;
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
