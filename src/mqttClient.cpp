#include <WiFi.h>
#include <PubSubClient.h>
#include <mqttClient.h>
#include <main.cpp>

WiFiClient wifi;
PubSubClient mqttClient;

//Wifi login
const char* ssid ="ProjetoMInDS";
const char* password ="Doi39x-Wa!";

// Broker MQTT
const char* mqttServer ="192.168.1.114";
const int mqttPort =1883; //"HallESP32"
const char* pubTopic ="grupo5/hall/chamada_andar"; // tópico de saída/publicação
const char* subTopic = "grupo5/elevador/andar_atual"; // tópico de entrada/assinatura
const char* subTopic2 = "grupo5/elevador/chegada"; // tópico de entrada/assinatura


// Classe padrao MQTTClient para ambos os clientes (Cabine e Hall):
MQTTClient::MQTTClient(const char* client_id)
    : _ssid(ssid), 
    _password(password), 
    _server(mqttServer), 
    _port(mqttPort), 
    _client_id(client_id), 
    _client(wifi) {}


// Função de inicialização
void MQTTClient::begin (){
    Serial.println("Inicializando MQTTClient...");
    setupWifi (); // configurando conexão wifi
    _client.subscribe(subTopic); // inscrição para receber o andar em que a cabine está
    _client.subscribe(subTopic2); // inscrição para saber se a cabine chegou
}

void MQTTClient::loop (){
    MQTTConnectionCheckup();
    _client.loop(); //processar as mensagens recebidas
}


void MQTTClient::setupWifi (){
    WiFi.begin(ssid, password);
    
    Serial.println("Conectando ao wifi");
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
    while (!_client.connected()){
        Serial.println("Cliente MQTT desconectado.");

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
void MQTTClient::publish (const char* payload){
    _client.publish(pubTopic, payload);
}





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