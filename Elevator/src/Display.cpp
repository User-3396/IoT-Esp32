#include <Display.h>
#include <Adafruit_ILI9341.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

// #define TFT_DC 2 // Data/Command (define se os dados são comandos ou texto/imagem).
// #define TFT_CS 15 // Chip Select (seleciona o display para comunicação).
// #define TFT_CS -1 // -1 se não houver pino CS
// #define TFT_BLK 5  // Pino Backlight

// Declarando variavel driver do display e configurando pinos:

Display::Display(const int data, const int chipSel)//, const int PIN_BLK)
  : PIN_DC(data), PIN_CS(chipSel){}

Adafruit_ILI9341 tft;

// Escrever texto na tela
void Display::setText (int size, char* text){
    tft.setTextSize(size);
    if (size <= 3) tft.setTextColor(0xFE70, 0x31A6); 
    else if (size <= 5){tft.setTextColor(0xFDC0, 0x31A6);}
    else{tft.setTextColor(ILI9341_WHITE);}
    tft.print(text);
}


// Inicializador 
void Display::begin (){
    tft =Adafruit_ILI9341(PIN_CS, PIN_DC);
    tft.begin();
    tft.setCursor(10, 10);
    setText (5, "ST7789\n\n");
    setText (3, "test ok.");
    
}

// void Display::loop (){}

/*
SCL deve ser ligado no pino correspondente ao Clock SPI (Ex: GPIO 18 no ESP32).
SDA deve ser ligado no pino correspondente ao MOSI SPI (Ex: GPIO 23 no ESP32).
BLK pode ser ligado diretamente no pino 3.3V se você não quiser controlar o brilho via código.

Cores Invertidas (Se acontecer): Telas IPS ST7789 frequentemente apresentam cores trocadas (ex: o azul fica amarelo). 
Se isso ocorrer no seu teste, adicione a linha tft.invertDisplay(true); 
logo após o tft.init();

*/