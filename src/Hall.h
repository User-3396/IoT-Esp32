#ifndef HALL_H
#define HALL_H

class Hall {
  private:
    //MQTTClient mqtt;         // cliente MQTT específico do Hall
    const char* _mqttClient;         
    int _FLOOR;             // andar do hall
    int _floorCabin;              // andar da cabine
    bool _cabinState;

  public:
    Hall(int andar);//, const int botaoPin, const int ledPin);
    void begin();
    void loop();
    void getMessage (char* topic, byte* payload, unsigned int length);
    //const int getButton ();
    const int call ();
    // Getters:
    bool getCabinState ();
    int getFloorCabin ();
    // Setters:
    void setFloorCabin (int andar);
    void setCabinState (bool newState);
};

#endif
