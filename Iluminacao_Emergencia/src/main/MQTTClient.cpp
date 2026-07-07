#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "MQTTClient.h"
#include <main.cpp>

WiFiClient wifi;
PubSubClient mqttClient;

//Wifi login
const char* ssid ="ProjetoMInDS";
const char* password ="Doi39x-Wa!";

// Broker MQTT
const char* mqttServer ="192.168.1.114";
const int mqttPort =1883; //"HallESP32"
const char* pubTopic1 ="rpiot/grupo003/corredor/esp32/luminosidade"; // tópico de saída/publicação
const char* pubTopic2 ="rpiot/grupo003/corredor/esp32/emergencia"; // tópico de saída/publicação
const char* subTopic ="rpiot/grupo003/corredor/esp32/emergencia"; // tópico de entrada/assinatura
// const char* subTopic2 = "grupo5/elevador/chegada"; // tópico de entrada/assinatura


// Classe padrao MQTTClient para ambos os clientes (Cabine e Hall):
MQTTClient::MQTTClient()
    : _ssid(ssid), 
    _password(password), 
    _server(mqttServer), 
    _port(mqttPort), 
    _client_id(""), 
    _client(wifi) {}


// Inicialização MQTT
void MQTTClient::begin (const char* id){
    _client_id =id; //strcpy(destino, origem);
    setupWifi (); // configurando conexão wifi
    _client.subscribe(subTopic); // inscrição para receber o comando do rele.
    // _client.subscribe(subTopic2); // 

}

void MQTTClient::loop (){
    MQTTConnectionCheckup ();
    _client.loop(); // processar/atualizar as mensagens recebidas
}

// Inicializando conexão com o wifi
void MQTTClient::setupWifi (){
    WiFi.begin(ssid, password);
    
    Serial.println("Conectando ao wifi");
    //while (wifiConnect () == 1){
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nWiFi conectado!");
    Serial.println("IP: " +WiFi.localIP().toString());
    _client.setServer(mqttServer, mqttPort);

}

// Função de reconexão do mqtt, caso houver queda:
void MQTTClient::MQTTConnectionCheckup (){
    
    if (!_client.connected()){Serial.println("Cliente MQTT desconectado.");}

    while (!_client.connected()){

        if (_client.connect(_client_id)){
            Serial.println("Conectado!");
        }
        else{
            Serial.print("Falha, rc=");
            Serial.print(_client.state());
            Serial.println(" tentando novamente em 5s"); delay(1000);
            Serial.print("."); delay(1000);
            Serial.print("."); delay(1000);
            Serial.print("."); delay(1000);
            Serial.print("."); delay(1000);
        }
    }
}

// 
void MQTTClient::setCallback (MQTT_CALLBACK_SIGNATURE){
    _client.setCallback(callback);
}

// Função para publicar num topico
void MQTTClient::publish (const char* payload1, const char* payload2){
    _client.publish(pubTopic1, payload1);
    _client.publish(pubTopic2, payload2);
}

const char* MQTTClient::getID (){return _client_id;}