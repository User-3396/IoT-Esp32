#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Display.cpp>
#include <Hall.cpp>
//> Definição dos pinos de controle: --------------------------

// Pinos Display:
#define TFT_SDA 23      // Pino Reset
#define TFT_SCK 18     // Pino de Sincronização
#define TFT_RST  4    // Pino Reset
#define TFT_DC   2   // Pino Data/Command
#define TFT_CS  -1  // Pino Chip Selector

// Pinos Hall:
#define PIN_BTN_CALL 5 // Pino do botao de chamada
#define PIN_LED_A    2 // Pino LED auxiliar
#define PIN_LED1     4 // Pino LED left 1
#define PIN_LED2     4 // Pino LED left 2
#define PIN_LED3     4 // Pino LED left 3

Hall hall(3); // Instanciando classe do Hall (nome_cliente_mqtt, andar)
//Display lcd (TFT_DC, TFT_CS);// Instanciando classe do Display
/* Para ST7789: -----------------------------------------------
// Inicializa o display sem usar o pino CS (-1):
//Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);
*/

//int debounce =300;

void setup (){
  Serial.begin(115200);
  
  //Serial.println("Inicializando Display ST7789 no ESP32...");
  //lcd.begin();
  Serial.println("Inicializando serviço Hall...");
  hall.begin();

  // Configurando pinos:
  pinMode(PIN_BTN_CALL, INPUT_PULLUP); // botão de chamada
  pinMode(PIN_LED_A, OUTPUT);         // led auxiliar
  pinMode(PIN_LED1, OUTPUT);         // led de chegada (left 1)r
  pinMode(PIN_LED2, OUTPUT);        // led de chegada (left 2)
  pinMode(PIN_LED3, OUTPUT);       // led de chegada (left 3)
  
  
}

void loop (){

  hall.loop(); // atualizando funcioinalidades do hall
  
  //tft.setText(hall.getFloorCabin());
  
  if (hall.getState ()){
    // (Quando o hall está esperando interação no botão de chamada)
    
    if (digitalRead(PIN_BTN_CALL) == LOW){
      // (Quando o botao do hall é pressionado)
      
      hall.call(); // executando publicação de andar do hall
      // tft.setText("Chamando cabine...");
      digitalWrite(PIN_LED_A, HIGH); // sinal led de cabine em demanda do chamado
      
    }
  }
  else{
    // (Quando o hall está esperando a cabine)

    setFloorLed (hall.getFloor (), hall.getLastFloorCabin (), hall.getCabinFloor ());

    if (hall.getCabinState ()){
      //(Quando a cabine chegou/está no andar)
      
      //tft.setText("Chegou!", hall.getFloorCabin ());
      
      if (hall.getCabinDoor ()){
        //(Quando a cabine está com a porta aberta, no andar)

        digitalWrite(PIN_LED_A, !digitalRead(PIN_LED_A)); // piscar sinal de porta aberta
        
        delay(600); // time do LED auxiliar
        return; // alteração de fluxo
      }
    }
  }

  hall.setLastFloorCabin (hall.getCabinFloor ()); // atualizando auxiliar
  
  delay(300); // debounce simples
}

// > Função para ligar LED de proximidade ----------------------------------
void setFloorLed (int origin, int last, int current){
  int dis =abs(origin -last); // distancia do andar anterior da cabine
  
  digitalWrite(ledAndar (dis), LOW); // apaga LED de distância anterior
  
  dis =abs(origin -current); // distancia do andar atual da cabine

  if (dis != 0) digitalWrite(ledAndar (dis <= 3 ? dis : 3), HIGH); // acende led de distância da cabine

}

// > Função para retornar o pino de led correspondente ao distanciamento de andar
int ledAndar (int x){
  switch (x){
    case 1: return PIN_LED1;
    case 2: return PIN_LED2;
    case 3: return PIN_LED3;
    default: return -1; // Retorna -1 se o resultado for inválido
  }
}