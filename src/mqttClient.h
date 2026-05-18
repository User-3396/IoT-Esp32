#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTClient {
    private:
        WiFiClient espClient;
        PubSubClient client;
        const char* ssid;
        const char* password;
        const char* mqtt_server;
        int mqtt_port;
        const char* client_id;

    public:
        MQTTClient(
            const char* ssid, const char* password,
            const char* mqtt_server, int mqtt_port,
            const char* client_id);

    void begin();
    void loop();
    void reconnect();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
    void subscribe(const char* topic);
    void publish(const char* topic, const char* payload);
};

#endif
