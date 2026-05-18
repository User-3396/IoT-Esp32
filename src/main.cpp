#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <display_ILI9341.cpp>
#include <Hall.cpp>
//> Definição dos pinos de controle: --------------------------

// #define TFT_DC    2   // Pino Data/Command
// #define TFT_RST   4   // Pino Reset

#define PIN_HALL_BTN 5 // Botao de chamada

Hall hall("HallClient", 3, 5, 4);

/* Para ST7789: -----------------------------------------------
// Inicializa o display sem usar o pino CS (-1):
//Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);
*/


//int myFunction(int, int);

void setup (){
  // int result = myFunction(2, 3);
  Serial.begin(115200);
  Serial.println("Inicializando Display ST7789 no ESP32...");
  
  pinMode(PIN_HALL_BTN, INPUT_PULLUP); 
  pinMode(4, OUTPUT);
  //digitalWrite(4, HIGH);

  

  }

void loop (){
  hall.loop();
  // Quando o botao do hall é pressionado:
  if (digitalRead(hall.getButton()) == LOW){
    //hall.mqtt.publish();

    //digitalWrite(4, HIGH);
  }
  
  //delay(500);
  //digitalWrite(PIN_LED, LOW);
  
  

}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }

void getMessage (char* topic, byte* message, unsigned int length){
  String msg;

  for (int i = 0; i < length; i++) msg += (char)message[i];
  

}

void setMessage (char* topic, char* msg){
  mqtt.publish(topic, msg);
}