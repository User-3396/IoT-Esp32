#include <Arduino.h>
#include <../Sensor.cpp>

//> Definição dos pinos de controle: --------------------------

#define PIN_BTN_CALL 5 // Pino do botao de chamada
#define PIN_LED_A    2 // Pino LED auxiliar
#define PIN_LED1     4 // Pino LED left 1
#define PIN_LED2     4 // Pino LED left 2
#define PIN_LED3     4 // Pino LED left 3

Sensor ldr; // Instanciando classe do Sensor

int loopDebounce =300;

// > Função para ligar LED de proximidade ----------------------------------
void setFloorLed (int origin, int last, int current){
  
}

void setup (){
    Serial.begin(115200);

    //Serial.println("Inicializando Display ST7789 no ESP32...");
    
    Serial.println("Success Starting");
    
    Serial.print("Starting LDR... ");
    ldr.start();

    // Configurando pinos:
    // pinMode(PIN_BTN_CALL, INPUT_PULLUP); // botão de chamada
    // pinMode(PIN_LED_A, OUTPUT);         // led auxiliar
    // pinMode(PIN_LED1, OUTPUT);         // led de chegada (left 1)r
    // pinMode(PIN_LED2, OUTPUT);        // led de chegada (left 2)
    // pinMode(PIN_LED3, OUTPUT);       // led de chegada (left 3)

}

void loop (){

  ldr.update(); // atualizando funcioinalidades do hall

  delay(loopDebounce); // debounce simples
}

