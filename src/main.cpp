#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <display_ILI9341.cpp>
#include <Hall.cpp>
//> Definição dos pinos de controle: --------------------------

// Pinos Display:
#define TFT_DC    2   // Pino Data/Command
#define TFT_RST   4   // Pino Reset

// Pinos Hall:
#define PIN_LED 4 // Botao de chamada
#define PIN_BTN_CALL 5 // Botao de chamada

Hall hall("Hall-001", 3); // Instanciando classe do Hall (nome_cliente_mqtt, andar)
// Instanciando classe do Display
/* Para ST7789: -----------------------------------------------
// Inicializa o display sem usar o pino CS (-1):
//Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);
*/


void setup (){
  // int result = myFunction(2, 3);
  Serial.begin(115200);
  Serial.println("Inicializando Display ST7789 no ESP32...");
  
  hall.begin();
  pinMode(PIN_BTN_CALL, INPUT_PULLUP); 
  pinMode(4, OUTPUT);
  //digitalWrite(4, HIGH);

  

}

void loop (){
  hall.loop();
  //tft.setText(hall.getFloorCabin());
  
  // Quando o botao do hall é pressionado:
  if (digitalRead(PIN_BTN_CALL) == LOW){
    hall.call();
    delay(500); // debounce simples
    //digitalWrite(4, HIGH);
  }
  
  //delay(500);
  //digitalWrite(PIN_LED, LOW);
  
}


void getMessage (char* topic, byte* message, unsigned int length){
  String msg;

  for (int i = 0; i < length; i++) msg += (char)message[i];
  

}

void setMessage (char* topic, char* msg){
  mqtt.publish(topic, msg);
}