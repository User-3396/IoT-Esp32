#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

// #include <WiFi.h>
#include <PubSubClient.h>

class MQTTClient {
    private:
        //WiFiClient _espClient;
        const char* _client_id;
        PubSubClient _client;
        const char* _ssid;
        const char* _password;
        const char* _server;
        const int _port;

    public:
        MQTTClient();

    void begin(const char* client_id);
    void loop();
    void setupWifi();
    void MQTTConnectionCheckup();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    void publish(const char* payload1, const char* payload2);
    const char* getID ();
};

#endif
