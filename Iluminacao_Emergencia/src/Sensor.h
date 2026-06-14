#ifndef SENSOR_H
#define SENSOR_H
#include <PubSubClient.h> 

class Sensor {
  private:
    //MQTTClient mqtt;        // cliente MQTT específico do Hall
    const char* _mqttClient; // cliente de conexão MQTT
    int _FLOOR;             // andar do hall
    bool _state;           // estado do hall (true: esperando interação; false: escutando informações da cabine)
    
  public:
    //Sensor;
    void start();
    void update();

    void getMessage (char* topic, byte* payload, unsigned int length);
    //const int getButton ();
    const int call ();
    
    // Getters:
    int getFloor ();
    
    // Setters:
    void setLed (bool x);
    void setToggleRele (bool x);
};

#endif