#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
  private:       
    const int PIN_DC;  // pino do botão de chamada
    const int PIN_CS;  // pino do LED indicador da cabine no local
    //const int PIN_BLK;  // pino do LED indicador da cabine no local
    
  public:
    Display(const int data, const int chipSel);//, const int PIN_BLK);
    void begin();
    // void loop();
    
    // Getters:

    // Setters:
    void setText (int size, char* text);
};

#endif
