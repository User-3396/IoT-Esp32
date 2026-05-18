#include "Hall.h"
#include <mqttClient.h>

MQTTClient mqtt("ProjetoMInDS", "Doi39x-Wa!", "192.168.1.114", 1883, "HallESP32");

Hall::Hall(const char* client_id, const int andar)//, const int botaoPin, const int ledPin)
  : mqttClient(client_id), FLOOR(andar){}//, PIN_BTN_CALL(botaoPin), PIN_LED_STATUS(ledPin) {}


//const int Hall::getButton (){return PIN_BTN_CALL;}
void Hall::setStatus (char* newState){status =newState;}

void Hall::begin (){
  //pinMode(PIN_BTN_CALL, INPUT_PULLUP);
  //pinMode(PIN_LED_STATUS, OUTPUT);
  
  mqtt.begin(); // inicialização da classe
  mqtt.subscribe("grupo5/elevador/andar_atual"); // inscrição para receber o andar em que a cabine está
  mqtt.subscribe("grupo5/elevador/chegada"); // inscrição para saber se a cabine chegou

  mqtt.setCallback([this](char* topic, byte* payload, unsigned int length) {
    this->getMessage(topic, payload, length);
  });

  mqtt.subscribe("elevador/hall");   // escuta mensagens do elevador
}

void Hall::loop (){
  mqtt.reconnect();
  mqtt.loop();

}

const int Hall::call (){
  mqtt.publish("elevador/chamada_andar", ""+FLOOR);  // envia pedido de chamada
}

// Atualizar na variavel do Hall o andar em que está a cabine
void Hall::setFloorCabin (int newFloor){floorCabin =newFloor;}

// Função ativada/excutada ao receber uma publicação:
void Hall::getMessage(char* topic, byte* payload, unsigned int length) {
  String msg;

  // Conversão do payload/publicação para String:
  for (int i = 0; i < length; i++){
    msg += (char)payload[i];
  }

  // Quando recebe publicação do andar:
  if (topic == "grupo5/elevador/andar_atual"){
    // conversão do numero textual para inteiro:
    setFloorCabin (msg.toInt()); 
  }
  // Quando recebe publicação de a cabine estar no andar do hall:
  else if (topic == "grupo5/elevador/chegada"){
    if (msg == "SIM"){setStatus("SIM");}
    else{setStatus("NAO");}
  }

}

int Hall::getFloorCabin (int andar){return floorCabin;}