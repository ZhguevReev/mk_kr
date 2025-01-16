#include <Arduino.h>
const uint8_t   pinSensor = A3; 
const uint16_t  varVolume = 800;
const uint32_t  tmrSignal = 300; 
const uint32_t  tmrPause  = 500;
      uint32_t  tmrSeparator;
      uint8_t   varLetter;
      uint8_t   lenLetter; 
      bool      flgSignal; 
      bool      flgLetter;
      char      chrMorze[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5',  '6',  '7',  '8',  '9',  '0',  '.',  ';',  ',',  ':',  '?',  '!',  '-',  ' ', '\n', '\r'};
      uint8_t   lenMorze[] = {  2,   4,   4,   3,   1,   4,   3,   4,   2,   4,   3,   4,   2,   2,   3,   4,   4,   3,   3,   1,   3,   4,   3,   4,   4,   4,   5,   5,   5,   5,   5,    5,    5,    5,    5,    5,    6,    6,    6,    6,    6,    6,    6,    5,    5,    5};
      uint8_t   varMorze[] = {0x1, 0x8, 0xA, 0x4, 0x0, 0x2, 0x6, 0x0, 0x0, 0x7, 0x5, 0x4, 0x3, 0x2, 0x7, 0x6, 0xD, 0x2, 0x0, 0x1, 0x1, 0x1, 0x3, 0x9, 0xB, 0xC, 0xF, 0x7, 0x3, 0x1, 0x0, 0x10, 0x18, 0x1C, 0x1E, 0x1F,  0x0, 0x2A, 0x15, 0x38, 0x0C, 0x33, 0x21, 0x11, 0x15, 0x0A};
void setup(){ 
    flgLetter=varLetter=lenLetter=0;
    Serial.begin(9600);
    Serial.println("Детектор азбуки Морзе"); 
    Serial.println("====================="); 
void loop(){ 
    if(analogRead(pinSensor) > varVolume){ 
        flgSignal=true; 
        lenLetter++; 
        while(analogRead(pinSensor) > varVolume){delay(10);} 
        varLetter<<=1; varLetter|=tmrSeparator<millis();
    }else{ 
        tmrSeparator = millis()+tmrPause; 
        while(analogRead(pinSensor) < varVolume && tmrSeparator>millis()){delay(10);} 
        if(tmrSeparator<millis()){flgLetter=flgSignal; flgSignal=false;}
    }

    if(flgLetter){ 
        for(uint8_t i=0; i<46; i++){
        if(varLetter==varMorze[i] && lenLetter==lenMorze[i]){ 
            Serial.print(chrMorze[i]); 
        }}  flgLetter=varLetter=lenLetter=0; 
    } 
}                            
