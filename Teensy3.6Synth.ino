#include <SPI.h>
#include <SerialFlash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Audio.h>
#include <Wire.h>
#include "ui.h"
#include "voice.h"

      //Class Objects
      voice vc; 
      ui ui;
      float pw;
      float mw;

void OnNoteOn(byte channel, byte note, byte velocity) {
  
    digitalWrite(13, HIGH); 
    vc.passNote(note);
    vc.amp_env();
    
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  
      digitalWrite(13, LOW);  
      vc.ampOff();
      
}

void PitchChange(byte channel, int pitch){
  
       pw = map(pitch,-127,127, 0,50) * 0.01;
      vc.updatePmod(pw,pw);
      
}

void MControlChange(byte channel, byte control, byte value){
  
   mw = map(value,0,127, 0,100) * 0.1;
  vc.updateLfo(mw,1);
  
}


      
void setup() {
  
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(9600);

  //Pin Assignment
  pinMode(32, OUTPUT); //SCLK
  pinMode(28, OUTPUT); //DIN
  pinMode(36, OUTPUT); //D/C
  pinMode(35, OUTPUT); //RST
  pinMode(38, OUTPUT); //CE
  pinMode(34, INPUT); //Pot 3
  pinMode(33, INPUT); //Pot 2
  pinMode(31, INPUT); //Pot 1
  pinMode(27, INPUT); //RIGHT
  pinMode(26, INPUT); //LEFT
  pinMode(25, INPUT); //EDIT
  pinMode(24, INPUT); //SHIFT
  pinMode(13, OUTPUT); //LED

  //Boot indicator
  digitalWrite(13, HIGH);
  delay(400);                 
  digitalWrite(13, LOW);

  //MIDI handling
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandlePitchChange(PitchChange);
  usbMIDI.setHandleControlChange(MControlChange);

  vc.init();
  ui.init();
  
  AudioMemory(40);

}

void loop() {

  ui.menuSelect();
  usbMIDI.read();
  vc.audioEngine();
  
}
