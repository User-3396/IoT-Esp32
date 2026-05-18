#include <WiFi.h>
#include <PubSubClient.h>
#include <mqttClient.h>
#include <main.cpp>

MQTTClient::MQTTClient(const char* client_id)
    : ssid("..."), password("..."), mqtt_server("..."), mqtt_port(1883), client_id(client_id), client(espClient) {}

void MQTTClient::begin() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi conectado!");
    client.setServer(mqtt_server, mqtt_port);
}

void MQTTClient::reconnect(){
    while (!client.connected()){
        Serial.print("Conectando ao MQTT...");

        if (client.connect(client_id)){
            Serial.println("Conectado!");
        } 
        else{
            Serial.print("Falha, rc=");
            Serial.print(client.state());
            delay(5000);
        }
    }
}

void MQTTClient::setCallback (MQTT_CALLBACK_SIGNATURE){
    client.setCallback(callback);
}

void MQTTClient::subscribe (const char* topic){
    client.subscribe(topic);
}

void MQTTClient::publish (const char* topic, const char* payload){
    client.publish(topic, payload);
}

// Configurações MQTT
//const char* mqtt_server = "broker.hivemq.com";  // Pode usar HiveMQ público ou Mosquitto local
//const char* mqtt_topic_pub = "grupo5/hall/chamada_andar";
//const char* mqtt_topic_sub = "grupo5/elevador/andar_atual";
//const char* mqtt_topic_sub2 = "grupo5/elevador/chegada";

//WiFiClient espClient;
//PubSubClient client(espClient);

// Simulação de sensor
//int sensorPin = 34; // GPIO para leitura analógica (ex: temperatura)
//int ledPin = 2;     // LED para simular lâmpada

// Reconexao: 
/*void reconnect (){
    while (!client.connected()) {
        Serial.print("Conectando ao MQTT...");
        if (client.connect("ESP32Hall")) {
            Serial.println("Hall Conectado!");
            client.subscribe(mqtt_topic_sub); // Inscreve para receber comandos
        } else {
            Serial.print("Falha, rc=");
            Serial.print(client.state());
            Serial.println(" tentando novamente em 5s");
            delay(5000);
        }
    }
}

void callback (char* topic, byte* message, unsigned int length){
    //Serial.print("Mensagem recebida em tópico: ");
    //Serial.println(topic);
    String msg;

    for (int i =0; i < length; i++){
        msg +=(char)message[i];
    }
    Serial.println("Andar: " + msg);

    // Exemplo: comando para ligar/desligar luz
    // if (msg == "ON"){
    //     digitalWrite(ledPin, HIGH);
    // } else if (msg == "OFF") {
    //     digitalWrite(ledPin, LOW);
    // }
}

void setupMqtt (){
    // Conectando ao WiFi:
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi conectado!");

  // Configurando MQTT:
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

// Atualiza o estado da conexao:
void checkConnection (){
    if (!client.connected()) reconnect();
    

    // Publica temperatura simulada
    //int valorSensor = analogRead(sensorPin);
    //float temperatura = (valorSensor / 4095.0) * 100.0; // Simulação
    //String payload = String(temperatura);
    //client.publish(mqtt_topic_pub, payload.c_str());

    //Serial.println("Temperatura publicada: " + payload);
    delay(5000); // publica a cada 5s
}

// Loop de Escuta telemetrica:
void listening (){
    checkConnection ();
    client.loop();

}*/