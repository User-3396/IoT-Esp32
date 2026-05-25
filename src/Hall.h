#ifndef HALL_H
#define HALL_H

class Hall {
  private:
    //MQTTClient mqtt;        // cliente MQTT específico do Hall
    const char* _mqttClient; // cliente de conexão MQTT
    int _FLOOR;             // andar do hall
    bool _state;           // estado do hall (true: esperando interação; false: escutando informações da cabine)
    int _cabinFloor;      // andar da cabine
    int _cabinLastFloor; // variavel auxiliar, do andar anterior em que a cabine esteve
    bool _cabinState;   // estado da cabine (true: chegou)
    int _cabinDoor;    // estado da porta da cabine (1: aberta; 0: fechada)

  public:
    Hall(int andar);//, const int botaoPin, const int ledPin);
    void begin();
    void loop();
    void getMessage (char* topic, byte* payload, unsigned int length);
    //const int getButton ();
    const int call ();
    
    // Getters:
    int getFloor ();
    bool getState ();
    bool getCabinState ();
    bool getCabinDoor ();
    int getCabinFloor ();
    int getLastFloorCabin ();
    
    // Setters:
    void setLastFloorCabin (int andar);
};

#endif