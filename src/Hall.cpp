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

Hall::Hall(int andar){
  _FLOOR = andar;
}

//const int Hall::getButton (){return PIN_BTN_CALL;}
void Hall::setCabinState (bool newState){_cabinState =newState;}
  
// Inicializando:
void Hall::begin (){
  _mqttClient =clientName;
  mqtt.begin(); // inicialização da classe e conexão MQTT

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

// Setters: 

// Atualizar na variavel do Hall o andar em que está a cabine
void Hall::setFloorCabin (int newFloor){_floorCabin =newFloor;}

// Função ativada/excutada ao receber uma publicação:
void Hall::getMessage (char* topic, byte* payload, unsigned int length){
  DeserializationError error =deserializeJson(doc, payload, length);

  if (!error){
    if (strcmp(topic, "grupo5/elevador/estado") == 0){
      // Quando recebe publicação do andar em que a cabine está:
      int andar =doc["andar_atual"];
      bool chegada =doc["elevador_chegada"];
      setFloorCabin (andar);
      setCabinState(chegada);
    }
  
    // else if (strcmp(topic, "grupo5/elevador/chegada") == 0){
      // Quando recebe publicação de a cabine estar no andar do hall:
      
      // }
      // else if (strcmp(topic, "grupo5/elevador/chegada") == 0){

    // }
    // conversão do numero textual para inteiro:
    //setFloorCabin (msg.toInt());
  }
  

}

// Getters: 
int Hall::getFloorCabin (){return _floorCabin;}
bool Hall::getCabinState (){return _cabinState;}