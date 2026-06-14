// #include <Arduino.h>
#include "Sensor.h"
//> Definição dos pinos de controle: --------------------------

#define PIN_BTN_CALL 5 // Pino do botao de chamada
#define PIN_LED_A    2 // Pino LED auxiliar
#define PIN_RELE     4 // Pino LED left 1


void Sensor::start (){
  
  // Configurando pinos:
  // pinMode(PIN_BTN_CALL, INPUT_PULLUP); // botão de chamada
  pinMode(PIN_LED_A, OUTPUT);         // led auxiliar
  pinMode(PIN_RELE, OUTPUT);         // led auxiliar
  
  Serial.println("success.");
};

void Sensor::update (){

}

// > Função para ligar LED de proximidade ----------------------------------
void Sensor::setLed (bool x){
  digitalWrite(PIN_LED_A, x ? HIGH : LOW);
}

// > Função para alternar energia Rele ----------------------------------
void Sensor::setToggleRele (bool x){
  digitalWrite(PIN_RELE, x ? HIGH : LOW);
}