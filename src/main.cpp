#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <mqttClient.h>

//> Definição dos pinos de controle: --------------------------

// #define TFT_DC    2   // Pino Data/Command
// #define TFT_RST   4   // Pino Reset

#define PIN_HALL_BTN 5 // Botao de chamada
#define TFT_DC 2 // Data/Command (define se os dados são comandos ou texto/imagem).
#define TFT_CS 15 // Chip Select (seleciona o display para comunicação).
// #define TFT_CS -1 // -1 se não houver pino CS
#define TFT_BL 5  // Pino Backlight

/* Para ST7789: -----------------------------------------------
// Inicializa o display sem usar o pino CS (-1):
//Adafruit_ST7789 tft = Adafruit_ST7789(-1, TFT_DC, TFT_RST);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RST, TFT_CS);
*/

MQTTClient mqtt("HallESP32");
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//int myFunction(int, int);

void setup (){
  // int result = myFunction(2, 3);
  Serial.begin(115200);
  Serial.println("Inicializando Display ST7789 no ESP32...");
  
  pinMode(PIN_HALL_BTN, INPUT_PULLUP); 
  pinMode(4, OUTPUT);
  //digitalWrite(4, HIGH);

  tft.begin();
  tft.setCursor(10, 10);
  tft.setTextColor(0xFDC0, 0x31A6);
  tft.setTextSize(5);
  tft.println("ILI9341\n");

  tft.setTextSize(3);
  tft.setTextColor(0xFE70, 0x31A6);
  tft.print("Test Ok");

  mqtt.begin();
  mqtt.setCallback(getMessage);
  mqtt.subscribe("grupo5/el3vador/andar_atual");
  mqtt.subscribe("grupo5/el3vador/chegada");
}

void loop (){
  
  //if (digitalRead(PIN_HALL_BTN) == LOW){
    //digitalWrite(4, HIGH);
  //}
  
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