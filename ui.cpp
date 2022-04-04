#include "ui.h"


//Custom Icon Bitmaps
const unsigned char bitmap_Saw [] PROGMEM = {
  // 'Saw, 16x16px
  0xff, 0xff, 0xfe, 0x7f, 0xfc, 0x7f, 0xf8, 0x7f, 0xf3, 0x7f, 0xe7, 0x7f, 0xcf, 0x7f, 0x1f, 0x7e, 
  0x7f, 0x78, 0xff, 0x7b, 0xff, 0x77, 0xff, 0x67, 0xff, 0x0f, 0xff, 0x1f, 0xff, 0x3f, 0xff, 0xff
};

// 'Sqr', 16x16px
 const unsigned char bitmap_Sqr [] PROGMEM = {
  0xe0, 0x7f, 0xee, 0x7f, 0xee, 0x7f, 0xee, 0x7f, 0xee, 0x7f, 0xee, 0x7f, 0x0e, 0x78, 0xfe, 0x73, 
  0xfe, 0x73, 0xfe, 0x73, 0xfe, 0x73, 0xfe, 0x73, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'Sine', 16x16px
 const unsigned char bitmap_Sin [] PROGMEM = {
  0xe3, 0xff, 0xc1, 0xff, 0xcd, 0xff, 0xdc, 0xff, 0xdc, 0xff, 0x9e, 0xff, 0x1e, 0xff, 0x3e, 0xfc, 
  0x3e, 0x78, 0xfe, 0x79, 0xfe, 0x7b, 0xff, 0x7b, 0xff, 0x73, 0xff, 0x37, 0xff, 0x07, 0xff, 0x8f
};

 const int bitmap_allArray_LEN = 3;
 const unsigned char* bitmap_allArray[3] = {
  bitmap_Saw,
  bitmap_Sqr,
  bitmap_Sin
};

//Bitmap end 

    //Variable decleration
    
    //Control 
    int shift = (int)digitalRead(24);
    int edit  = (int)digitalRead(25);
    int right;
    int left;
    int menu;
  
    //Reverb 
    float vAmount;
    float roomSize;


    //ADSR Graph Co-ordianate 
    int x1 = 20;
    int x2 = 25;
    int x3 = 70;
    int yi = 27;

    //ADSR display 
    int aa;
    int ad;
    float as;
    int ar;

    //MOD display
    int ma;
    int md;
    float ms;
    int mr;
    int modAttack;
    int modDecay;
    int modSustain;
    int modRelease;

    //Filter
    int circ1r;
    int circ2r;
    int cutoff;
    float res;

    //LFO
    float rate;
    float lfoAmount;
    int lfoy0;
    int tf;

    //OSC
    float osc1sqr;
    float osc1saw;
    float osc1sin;
    float osc1Lpan;
    float osc1Rpan;
    float osc1env;
    int osc1y0;
    int osc2y0;
    float osc2sqr;
    float osc2saw;
    float osc2sin;
    float osc2Lpan;
    float osc2Rpan;
    float osc2env;
    
    //Detune
    float osc1tune;
    float osc2tune;
    int ct1;
    int ct2;

    Adafruit_PCD8544 display = Adafruit_PCD8544(32, 28, 36, 38, 35);
    
void ui::init(){

    //ADSR display variables
    aa = 100;
    ad = 20;
    as = 0.8;
    ar = 300;
    
    //Mod 
    ma = 20;
    md = 10;
    ms = 0;
    mr = 30;
    modAttack = 20;
    modDecay = 10;
    modSustain = 0;
    modRelease = 30;
    tf = 0;
    
    //Filter
    circ1r = 10;
    circ2r = 0;
    cutoff = 20000;
    res = 0;
    
    //LFO
    rate = 0.1;
    lfoAmount= 0;
    lfoy0 = 24;

    //OSC
    osc1sqr = 0;
    osc1saw = 1;
    osc1sin = 0;
    osc1Lpan = 0.5;
    osc1Rpan = 0.5;
    osc1env = 0;
    osc1y0 = 24;
    osc2y0 = 24;
    osc1tune = 0;
    osc2tune = 0;
    ct1 = 42;
    ct2 = 42;

    menu = 0; //starting screen no. 
    
  //Initialize Display
      display.begin();
      display.setContrast(57);
  // Clear
      display.clearDisplay();
  // Loadscreen
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(0,0);
      display.println("TEENSYNTH V1.1");
      display.println();
      display.print("for");
      display.setCursor(0,30);
      display.setTextColor(WHITE, BLACK);
      display.println("MODAL");
      display.setCursor(0,40);
      display.setTextColor(BLACK);
      display.println("Electronics");
      display.display(); 
      delay(1500);
      display.clearDisplay();
}

void ui::drawGraphics(int x,int y, int bitmap_N){
  
  display.drawBitmap(x, y, bitmap_allArray[bitmap_N], 16, 16, BLACK);
  
}


void ui::osc1(){

  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);

      if(edit==false){
        
          osc1sqr = map(analogRead(31),0,512,0,100) * 0.01;
          osc1saw = map(analogRead(31),256,768,0,100) * 0.01;
          osc1sin = map(analogRead(31),512,1023,0,100) * 0.01;
          osc1Lpan =  map(analogRead(33),0,1023,100,0) * 0.01;
          osc1Rpan =  map(analogRead(33),0,1023,0,100) * 0.01;
          osc1env = map(analogRead(34),0,1023,0,100) * 0.01;
          osc1y0 = map(analogRead(31),0,1023,10,38);
          vc.updateOsc1(osc1sqr,osc1saw,osc1sin,osc1Lpan,osc1Rpan,osc1env);
      
      }
  

  else{}

  display.clearDisplay();
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("OSC1");
  
  //OSC ICONS
  drawGraphics(0, 0, 1);
  drawGraphics(0, 16, 0);
  drawGraphics(0, 32, 2);

  int y1 = osc1y0 - 5;
  int y2 = osc1y0 + 5;

  int x1 = 55;
  
  x1 = 55 + map(analogRead(33),0,1023,-13,13);
  
  display.fillTriangle(16,osc1y0,21,y1,21,y2,1); //Pointer Control

  display.setCursor(42,40); //PAN UI
  display.setTextColor(BLACK);
  display.print("L_c_R");
  display.fillRect(x1,35,3,5,1);
  display.setCursor(35,20);
  int pitchEnv = osc1env * 100;
  display.print("Env=");
  display.print(pitchEnv);
  display.print("%");
  display.display(); 

}
void ui::osc2(){

  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);

  if(edit==false){
  osc2sqr = map(analogRead(31),0,512,0,100) * 0.01;
  osc2saw = map(analogRead(31),256,768,0,100) * 0.01;
  osc2sin = map(analogRead(31),512,1023,0,100) * 0.01;
  osc2Rpan = map(analogRead(33),0,1023,0,100) * 0.01;
  osc2Lpan = map(analogRead(33),0,1023,100,0) * 0.01;
  osc2env = map(analogRead(34),0,1023,0,100) * 0.01;
  osc2y0 = map(analogRead(31),0,1023,10,38);
  vc.updateOsc2(osc2sqr,osc2saw,osc2sin,osc2Lpan,osc2Rpan,osc2env);
  }
  
  else{}

  display.clearDisplay();
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("OSC2");
  
  //OSC ICONS
  drawGraphics(0, 0, 1);
  drawGraphics(0, 16, 0);
  drawGraphics(0, 32, 2);

  int y1 = osc2y0 - 5;
  int y2 = osc2y0 + 5;
  int x1 = 55;
  
  x1 = 55 + map(analogRead(33),0,1023,-13,13);
  
  display.fillTriangle(16,osc2y0,21,y1,21,y2,1); //Pointer Control
  display.setCursor(42,40); //PAN UI
  display.setTextColor(BLACK);
  display.print("L_c_R");
  display.fillRect(x1,35,3,5,1);
  display.setCursor(35,20);
  int pitchEnv2 = osc2env * 100;
  display.print("Env=");
  display.print(pitchEnv2);
  display.print("%");
  display.display(); 
 
}

void ui::poly(){
  
  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);
  
  display.clearDisplay();
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("MOD");
  display.setCursor(0,0);
  display.print("OSC Detune");
  
  if(edit==false){ 
    
    osc1tune = map(analogRead(31),0,1023, 0, 20)*0.01;
    osc2tune = map(analogRead(31),0,1023,0, -20)*0.01;
    vc.updatePmod(osc1tune, osc2tune);

   }

     else{}
     
   osc1tune *= 100;
   osc2tune *= 100;
   ct1 = 42 + osc1tune;
   ct2 = 42 + osc2tune;
   display.drawCircle(ct1,24, 10,1);
   display.drawCircle(ct2,24, 10,1);
   display.display();
  
}

void ui::fil(){

  
  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);
  display.clearDisplay();
   display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("FIL1");
  
      if(edit==false){ 
        circ1r = map(analogRead(31),0,1023,10,0);
        circ2r = map(analogRead(33),0,1023,0,7);
        cutoff = map(analogRead(31),0,1023,20000,40);
        res = map(analogRead(33),0,1023,0,120) * 0.01;
        vc.updateFil(cutoff, res);
      }

        else{}

   display.drawCircle(17,10,10,1); // Outer Circle
   display.fillCircle(17,10,circ1r,1); // Circle Fill
   display.drawCircle(52,15,5,1); // Outer Circle
   display.fillCircle(52,15,circ2r,1); // Circle Fill
   display.setCursor(0,35);
   display.setTextColor(BLACK);
   display.print("CUTOFF  RES");
   display.setCursor(0,25);
   display.print(cutoff);
   display.print("Hz");
   display.setCursor(46,25);
   display.print(res);
   display.display();
  
}

void ui::ampDisp(){

  display.clearDisplay();
  int y1 = yi;

  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);

  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.print("A=");
  display.print(aa);
  display.print("ms");
  display.setCursor(0,10);
  display.print("D=");
  display.print(ad); 
  display.print("ms");
  display.setCursor(42,10);
  display.print("S=");
  display.print(as);
  
  display.setCursor(0,20);
  display.print("R=");
  display.print(ar);
  display.print("ms"); 
  
  display.drawLine(0,48,x1,30,1); //Attack
  display.drawLine(x1,30,x2,y1,1); //Decay
  display.drawLine(x2,y1,55,y1,1); //Sustain
  display.drawLine(55,y1,x3,48,1); //Release
 
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("AMP1");
  display.display();
  
 
          if(edit==false){ //Check for edit key press enabling secondary parameter editing
            
              if(shift==false){
                 x2 = x1 + 1 + map(analogRead(31),0,1023,0,24);
                  ad = map(analogRead(31),0,1023,0,1000);
                 vc.updateAmpDecay(ad);
                }
                else {
                   x1 = 5 + map(analogRead(31),0,1023,0,20); //primary parameter editing
                    aa = map(analogRead(31),0,1023,0,4000);
                   vc.updateAmpAttack(aa);
                   
                      }
          
                      
             x3 = 55 + map(analogRead(34),0,1023,0,20); //Release time x co-ord
              ar = map(analogRead(34),0,1023,15,5000);
             vc.updateAmpRelease(ar);
             
             y1 = 48 - map(analogRead(33),0,1023,0,18);; //Sustain level y co-ord
          
              as = map(analogRead(33),0,1023,0,100);
             as = as*0.01;
             vc.updateAmpSustain(as);
             yi = y1;
             
          }
          
          else{} 
   
}

void ui::lfo(){

  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);
      
        if(edit==false){
          
            rate = 0.1 * map(analogRead(33),0,1023,0,100);
            lfoAmount =  map(analogRead(34),0,1023,0,100) * 0.01;
            vc.updateLfo(rate,lfoAmount);
            
        }
        
      
        else{}
  
  display.clearDisplay();
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("LFO1");
  display.setTextColor(BLACK);
  display.setCursor(24,10);
  display.print("RATE=");
  display.print(rate,1);
  display.print("Hz");
  display.setCursor(24,20);
  display.print("toFIL=");
  int lfoAmountDisp = lfoAmount*100;
  display.print(lfoAmountDisp);
  display.print("%");
  
  //OSC ICONS
  drawGraphics(0, 0, 1);
  drawGraphics(0, 16, 0);
  drawGraphics(0, 32, 2);

  lfoy0 = map(analogRead(31),0,1023,10,38);
  int y1 =  lfoy0 - 5;
  int y2 =  lfoy0 + 5;
  
  display.fillTriangle(16,lfoy0,21,y1,21,y2,1); //Pointer
  display.display();
  
}

void ui::env(){
  
  display.clearDisplay();
  int y1 = yi;

 shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25); 

 
      if(edit==false){ //Check for edit key press enabling secondary parameter editing
        
            if(shift==false){
              
                      x2 = x1 + 1 + map(analogRead(31),0,1023,0,24);
                      md = map(analogRead(31),0,1023,0,1000);
                      tf = map(analogRead(33),0,1023,0,99);
                      vc.updateModEnv(ma,md,ms,mr,tf);
               
               
              }
              else {
                
                      x1 = 5 + map(analogRead(31),0,1023,0,20); //primary parameter editing
                      ma = map(analogRead(31),0,1023,0,4000);
                      y1 = 48 - map(analogRead(33),0,1023,0,18);; //Sustain level y co-ord
                      yi = y1;
                      ms = map(analogRead(33),0,1023,0,100);
                      ms = as*0.01;
                      vc.updateModEnv(ma,md,ms,mr,tf);
                 
                  }

            
          x3 = 55 + map(analogRead(34),0,1023,0,20); //Release time x co-ord
          mr = map(analogRead(34),0,1023,15,5000);
          vc.updateModEnv(ma,md,ms,mr,tf);
      }
      else{} 
      
  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("ENV1"); 
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.print("A=");
  display.print(ma);
  display.print("ms");
  display.setCursor(0,10);
  display.print("D=");
  display.print(md); 
  display.print("ms");
  display.setCursor(42,10);
  display.print("S=-");
  display.print(ms);
  display.setCursor(0,20);
  display.print("R=");
  display.print(mr);
  display.print("ms"); 
  display.print("M=");
  display.print(tf);
  display.print("%");
  
  display.drawLine(0,48,x1,30,1); //Attack
  display.drawLine(x1,30,x2,y1,1); //Decay
  display.drawLine(x2,y1,55,y1,1); //Sustain
  display.drawLine(55,y1,x3,48,1); //Release
  
  display.display();
  
}



void ui::fx(){
  
  display.clearDisplay();

  shift = (int)digitalRead(24);
  edit  = (int)digitalRead(25);
  
 
        if(edit==false){ //Check for edit key press enabling secondary parameter editing
               vAmount =  map(analogRead(31),0,1023,0,100) * 0.01;
               roomSize = map(analogRead(33),0,1023,0,30);
        }
        
        else{}

  display.setCursor(60,0);
  display.setTextColor(WHITE, BLACK);
  display.print("fx1");
  display.setCursor(0,0);
  display.setTextColor(BLACK);
  display.println("Reverb");
  int va = vAmount*100;
  display.print(va);
  display.println("%");
  display.println("time");
  int rs = roomSize;
  display.print(rs);
  rs *= 5;
  display.println("s");

  int circ = map(rs,0,100,2,15);
  int circ2 = map(va,0,100,2,circ);
  display.drawCircle(50,25,circ,1);
  display.fillCircle(50,25,circ2,1);
  vc.updateVerb(vAmount,roomSize);
  
  display.display();
  
  }

void ui::menuSelect(){
      
     right = (int)digitalRead(27);
     left = (int)digitalRead(26);

     
     if(right==false){
          menu++;
          delay(40); //swap for debouncing
     }
     else if(left==false){
          menu--;
          delay(40); //swap for debouncing
     }
     
       
       if(menu<0){
        
            menu=7;            
       }
       
       else if(menu>7){
        
            menu=0;   
      }

     switch(menu)
      {
        case 0:
          osc1();
          break;

          case 1:
          osc2();
          break;

          case 2:
          poly();
          break;

          case 3:
          fil();
          break;

          case 4:
          ampDisp();
          break;

          case 5:
          env();
          break;

          case 6:
          lfo();
          break;

          case 7:
          fx();
          break;
          
     }
     return;
     
}
