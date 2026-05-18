#include "Hall.h"
#include <mqttClient.h>

MQTTClient mqtt("HallESP32");

Hall::Hall(const char* client_id, const int andar, const int botaoPin, const int ledPin)
  : mqtt(client_id), FLOOR(andar), PIN_BTN_CALL(botaoPin), PIN_LED_STATUS(ledPin) {}


const int Hall::getButton(){return PIN_BTN_CALL;}
void Hall::setStatus (char* newState){status =newState;}

void Hall::begin (){
  pinMode(PIN_BTN_CALL, INPUT_PULLUP);
  pinMode(PIN_LED_STATUS, OUTPUT);
  
  mqtt.begin(); // inicialização da classe
  mqtt.subscribe("grupo5/elevador/andar_atual"); // inscrição para receber o andar em que a cabine está
  mqtt.subscribe("grupo5/elevador/chegada"); // inscrição para saber se a cabine chegou

  mqtt.setCallback([this](char* topic, byte* payload, unsigned int length) {
    this->getMessage(topic, payload, length);
  });

  mqtt.subscribe("elevador/hall");   // escuta mensagens do elevador
}

void Hall::loop() {
  mqtt.reconnect();
  mqtt.loop();

  // se botão pressionado, publica chamada
  if (digitalRead(PIN_BTN_CALL) == LOW) {
    mqtt.publish("elevador/chamada", "1");  // envia pedido de chamada
    delay(500); // debounce simples
  }
}

void Hall::getMessage(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  // Quando recebe publicação do andar:
  if (topic == "grupo5/elevador/andar_atual"){
    int currentFloor = msg.toInt(); // conversão do numero textual para inteiro.
    // if (currentFloor == 1){
    //   digitalWrite(ledStatus, HIGH);   // acende LED indicando elevador chegando
    // } else{
    //   digitalWrite(ledStatus, LOW);
    // }
  }
  // Quando recebe publicação de a cabine estar no andar do hall:
  else if (topic == "grupo5/elevador/chegada"){
    if (msg == "SIM"){setStatus("SIM");}
    else{setStatus("NAO");}
  }
}

