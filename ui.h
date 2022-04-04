#ifndef ui_h
#define ui_h


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "voice.h"

/** UI Class
* @brief User interface, menus and visualisation
* @author Matt Ayres
* @date March 2022
*/



class ui
{
  public:


  void init();
  void menuSelect();

  float vAmount;
  float roomSize;

  voice vc;
  

  
  private:

  void drawGraphics(int x, int y, int bitmap_N);
  void osc1();
  void osc2();
  void poly();
  void fil();
  void ampDisp();
  void lfo();
  void env();
  void fx();

  int aa;
  int ad;
  float as;
  int ar;
  int va;
  int rs;
  int circ;
  int circ2;
  int circ1r;
  int circ2r;
  int cutoff;
  float res;
  int osc1y0;
  int osc2y0;
  float osc1sqr;
  float osc1saw;
  float osc1sin;
  float osc1env;
  float osc2sqr;
  float osc2saw;
  float osc2sin;
  float osc2env;
  float rate;
  float lfoAmount;
  
  
};

#endif
