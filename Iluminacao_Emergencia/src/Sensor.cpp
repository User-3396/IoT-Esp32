// #include <Arduino.h>
#include "Sensor.h"
//> Definição dos pinos de controle: --------------------------

#define PIN_BTN_CALL 5 // Pino do botao de chamada
#define PIN_LED_A    2 // Pino LED auxiliar
#define PIN_RELE     4 // Pino LED left 1


void Sensor::start (){
  Serial.println("Inicializando o sensor...");
  
  // Configurando pinos:
  // pinMode(PIN_BTN_CALL, INPUT_PULLUP); // botão de chamada
  pinMode(PIN_LED_A, OUTPUT);         // led auxiliar
  pinMode(PIN_RELE, OUTPUT);         // led auxiliar
  // pinMode(PIN_LED1, OUTPUT);         // led de chegada (left 1)r
  // pinMode(PIN_LED2, OUTPUT);        // led de chegada (left 2)
  // pinMode(PIN_LED3, OUTPUT);       // led de chegada (left 3)
  
};

void Sensor::update (){

}

// > Função para ligar LED de proximidade ----------------------------------
void Sensor::setLed (){
  
}

// > Função para alternar energia Rele ----------------------------------
void Sensor::setToggleRele (bool x){
  digitalWrite(PIN_RELE, x ? HIGH : LOW);
}