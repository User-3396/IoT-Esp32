#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTClient {
    private:
        WiFiClient _espClient;
        const char* _client_id;
        PubSubClient _client;
        const char* _ssid;
        const char* _password;
        const char* _server;
        const int _port;

    public:
        MQTTClient(const char* client_id);

    void begin();
    void loop();
    void setupWifi();
    void checkWifiConnection();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    void subscribe(const char* topic);
    void publish(const char* topic, const char* payload);
};

#endif
