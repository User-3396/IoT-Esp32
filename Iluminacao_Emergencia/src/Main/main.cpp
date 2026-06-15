#include <Arduino.h>
#include "../Sensor.cpp"

//> Definição dos pinos de controle: --------------------------

// #define PIN_BTN_CALL 5 // Pino do botao de chamada
#define PIN_LDR   2 // Pino AO do LDR (variação de luminosidade)
// #define PIN_LDR2  4 // Pino DO do LDR (simples)
#define PIN_RELE  4 // Pino IN do Rele

const uint8_t pins[]  ={PIN_LDR, PIN_RELE};
const uint8_t modes[] ={INPUT, OUTPUT};

Sensor ldr; // Instanciando classe do Sensor

int loopDebounce =300;

void setup (){
  Serial.begin(115200);
  Serial.println("Starting");
  
  Serial.print("Starting LDR: ");
  ldr.start("corredor-001", pins, modes, 2);

}

void loop (){
  ldr.update(); // atualizando funcionalidades do sensor

  delay(loopDebounce); // debounce simples
}

