#include <Display.h>
#include <Adafruit_ILI9341.h>

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