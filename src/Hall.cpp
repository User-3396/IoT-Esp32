#include "Hall.h"
#include <mqttClient.h>
#include <ArduinoJson.h>

#define MSG_SIZE 1024

const char* clientName ="Hall";

// Variaveis para serilialização de mensagens/publicações
DynamicJsonDocument doc(MSG_SIZE);
DynamicJsonDocument doc_send(MSG_SIZE);

// Declaração da classe MQTT
MQTTClient mqtt(clientName);

// Construtor
Hall::Hall(int andar){
  _FLOOR = andar; // recebendo parâmetro do andar em que estiver o hall
  _state =true;  // true para estado de escuta do botão de chamada
  _cabinFloor =0;
  _cabinState =false;
  _cabinDoor =0; 
}

//const int Hall::getButton (){return PIN_BTN_CALL;}
//void Hall::setCabinState (bool newState){_cabinState =newState;}
  
// Inicializando:
void Hall::begin (){
  _mqttClient =clientName;
  mqtt.begin(); // inicialização e conexão da classe MQTT
  mqtt.setCallback([this](char* topic, byte* payload, unsigned int length) {
    // Chamada interna: delega para getMessage()
    this->getMessage(topic, payload, length);
  });

}

void Hall::loop (){
  mqtt.loop();
}

// Função para publicar chamada à cabine:
const int Hall::call (){
  doc_send.clear();
  doc_send["origin"] = _mqttClient;
  doc_send["destination"] = "Cabin-001";
  doc_send["andarDestino"] = _FLOOR;
  
  char buffer[MSG_SIZE];
  serializeJson(doc_send, buffer);
  mqtt.publish (buffer);  // envia pedido de chamada
  // Possivel alteração no método publish de origem, a aplicar o parâmetro 'plength'

}

// Atualizar na variavel do Hall o andar em que está a cabine
//void Hall::setFloorCabin (int newFloor){_floorCabin =newFloor;}

// Função ativada/excutada ao receber uma publicação:
void Hall::getMessage (char* topic, byte* payload, unsigned int length){
  DeserializationError error =deserializeJson(doc, payload, length);

  if (!error){
    //if (strcmp(topic, "grupo5/elevador/estado") == 0){
    _cabinFloor =doc["andar_atual"];
    _cabinDoor  =doc["porta_status"];
    _cabinState =doc["elevador_chegada"];
    // String type = doc["type"].as<String>();
    
  }
  else Serial.println("Erro ao deserializar o Json.");

  // conversão do numero textual para inteiro:
  //setFloorCabin (msg.toInt());
  
}

// Getters: 
int Hall::getFloor (){return _FLOOR;}
bool Hall::getState (){return _state;}
int Hall::getCabinFloor (){return _cabinFloor;}
bool Hall::getCabinState (){return _cabinState;}
int Hall::getLastFloorCabin (){return _cabinLastFloor;}

// Setter:
void Hall::setLastFloorCabin (int andar){_cabinLastFloor =andar;}
