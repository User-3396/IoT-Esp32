#ifndef SENSOR_H
#define SENSOR_H
#include <PubSubClient.h> 

class Sensor {
  private:
    const MQTTClient* _mqtt; // cliente de conexão MQTT
    uint8_t _LDR_PIN;
    uint8_t _RELE_PIN;

  public:
    //Sensor();
    void attachMqtt (MQTTClient* client){_mqtt =client;}
    
    void start (const char* clientID, const uint8_t* pins, const uint8_t* modes, int size);
    void update ();

    void callback (char* topic, byte* payload, unsigned int length);
    
    // void setLed (bool x);
    void setToggleRele (bool x);
    
};

#endif