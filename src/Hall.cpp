#include "Hall.h"
#include <mqttClient.h>
#include <ArduinoJson.h>

#define MSG_SIZE 1024


DynamicJsonDocument doc(MSG_SIZE);
DynamicJsonDocument doc_send(MSG_SIZE);

MQTTClient mqtt("Hall-001");

Hall::Hall(const int andar) : FLOOR(andar){}

//const int Hall::getButton (){return PIN_BTN_CALL;}
void Hall::setCabinState (char* newState){cabinState =newState;}

// Inicializando:
void Hall::begin (){
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
  doc_send["andarDestino"] = FLOOR;
  char buffer[MSG_SIZE];
  serializeJson(doc_send, buffer);
  mqtt.publish (buffer);  // envia pedido de chamada
  // Possivel alteração no método publish de origem, a aplicar o parâmetro 'plength'
}

// Setters: 

// Atualizar na variavel do Hall o andar em que está a cabine
void Hall::setFloorCabin (int newFloor){floorCabin =newFloor;}

// Função ativada/excutada ao receber uma publicação:
void Hall::getMessage (char* topic, byte* payload, unsigned int length){
  DeserializationError error =deserializeJson(doc, payload, length);

  if (!error){
int andar =doc[]
  }

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
    if (msg == "SIM"){setCabinState("SIM");}
    else{setCabinState("NAO");}
  }


  //Apenas mostra a mensagem recebida, sem processar. Também transforma o payload em string para facilitar a leitura.
  // String message;
  // Serial.print("MQTT Recv: ");
  // for (int i = 0; i < length; i++){
  // message += (char)payload[i];
  // }
  // Serial.println(message);

  //Deserializa e processa a mensagem recebida
  // doc.clear();
  // deserializeJson(doc, message);
  
  // if (strcmp(topic, sub_topic) == 0){
  //     int andarDestino = doc["andarDestino"];
  //     Serial.print("Andar destino recebido: ");
  //     Serial.println(andarDestino);

  //     if (andarDestino >= 0 && andarDestino <= ULTIMO_ANDAR){
  //         elevador.setAndarDestino(andarDestino);
  //     }
  // }

}




// Getters: 
int Hall::getFloorCabin (int andar){return floorCabin;}
char* Hall::getCabinState(){return cabinState;}