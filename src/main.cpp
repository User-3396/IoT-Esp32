#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Display.cpp>
#include <Hall.cpp>
//> Definição dos pinos de controle: --------------------------

// Pinos Display:
#define TFT_DC 2    // Pino Data/Command
#define TFT_CS 15    // Pino Reset
#define TFT_RST 18  // Pino Reset

// Pinos Hall:
#define PIN_LED 4      // LED
#define PIN_BTN_CALL 5 // Botao de chamada

Hall hall(3); // Instanciando classe do Hall (nome_cliente_mqtt, andar)
Display lcd (TFT_DC, TFT_CS);// Instanciando classe do Display
/* Para ST7789: -----------------------------------------------
// Inicializa o display sem usar o pino CS (-1):
//Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);
*/


void setup (){
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (wifiConnect () == 1){
    Serial.print(".");

  }

  Serial.println("Inicializando Display ST7789 no ESP32...");
  lcd.begin();
  Serial.println("Inicializando Display ST7789 no ESP32...");
  hall.begin();

  // Configurando pinos:
  pinMode(PIN_BTN_CALL, INPUT_PULLUP); 
  pinMode(PIN_LED, OUTPUT);
  //digitalWrite(4, HIGH);

  
}

void loop (){


  hall.loop();
  //tft.setText(hall.getFloorCabin());

  // Quando o botao do hall é pressionado:
  if (digitalRead(PIN_BTN_CALL) == LOW){
    hall.call();
    // tft.setText("Chamando cabine...");
    digitalWrite(PIN_LED, HIGH);
    delay(500); // debounce simples
    // tft.setText("Chamando cabine...");
    digitalWrite(PIN_LED, LOW);
  }
  
  //delay(500);
  
  // Atualizando estado da cabine: 
  if (hall.getCabinState () == "SIM"){
    //tft.setText("Chegou!");
  }
  
}

