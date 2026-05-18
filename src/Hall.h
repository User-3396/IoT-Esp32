#ifndef HALL_H
#define HALL_H

// #include <Arduino.h>
#include "mqttClient.h"   // usa sua classe MQTTClient

class Hall {
  private:
    //MQTTClient mqtt;         // cliente MQTT específico do Hall
    const char* mqttClient;         
    //const int PIN_BTN_CALL;    // pino do botão de chamada
    //const int PIN_LED_STATUS;  // pino do LED indicador da cabine no local
    const int FLOOR;             // andar do hall
    int floorCabin;              // andar da cabine
    char* status;

  public:
    Hall(const char* client_id, const int andar);//, const int botaoPin, const int ledPin);
    void begin();
    void loop();
    void getMessage (char* topic, byte* payload, unsigned int length);
    //const int getButton ();
    const int call ();
    void setStatus (char* newState);
    int getFloorCabin (int andar);
    void setFloorCabin (int andar);
};

#endif
