#include "voice.h"

// VOICE 1

AudioSynthWaveformModulated waveformMod1;   //  Osc1
AudioSynthWaveformModulated waveformMod2;   //  Osc1
AudioSynthWaveformModulated waveformMod3;   //  Osc1
AudioSynthWaveformModulated waveformMod4;   //  Osc2
AudioSynthWaveformModulated waveformMod5;   //  Osc2
AudioSynthWaveformModulated waveformMod6;   //  Osc2
AudioSynthWaveform       waveform1;      // LFO1
AudioSynthWaveform       waveform2;      // LFO1
AudioSynthWaveform       waveform3;      // LFO1
AudioMixer4              mixer1;         //  Osc1 Waveform Mixer
AudioMixer4              mixer2;         //  Osc2 Waveform Mixer
AudioMixer4              mixer11;        // LFO1 Waveform Mixer
AudioEffectEnvelope      envelope3;      // Mod envelope
AudioSynthWaveformDc     dc1;            // Mod env Signal
AudioSynthWaveformDc     dc2;            // Pitch mod osc1
AudioSynthWaveformDc     dc3;            // Pitch mod osc2
AudioMixer4              mixer4;         //  R channel
AudioMixer4              mixer3;         //  L channel
AudioMixer4              mixer12;        // Mod Mixer
AudioFilterLadder        ladder1;        // L Filter
AudioFilterLadder        ladder2;        // R Filter
AudioEffectEnvelope      envelope1;      // L Amp env
AudioEffectEnvelope      envelope2;      // R Amp env
AudioMixer4              mixer5;         // L FX mix
AudioMixer4              mixer6;         // R FX mix 
AudioMixer4              mixer9;         // R Voice Mix
AudioMixer4              mixer10;        // R voice Mix
AudioMixer4              mixer8;         // L voice Mix
AudioMixer4              mixer7;         // R voice Mix
AudioMixer4              mixer13;       // Pitch Mod Osc1
AudioMixer4              mixer14;        //Pitch Mod Osc2
AudioEffectReverb        freeverb1;      // L Reverb
AudioEffectReverb        freeverb2;      // R Reverb
AudioAmplifier           amp1;          //L reverb amp
AudioAmplifier           amp2;        //R reverb amp
AudioOutputI2S           i2s1;           //Output

// Audio Connections
AudioConnection          patchCord1(waveformMod4, 0, mixer2, 0);
AudioConnection          patchCord2(waveformMod5, 0, mixer2, 1);
AudioConnection          patchCord3(waveformMod1, 0, mixer1, 0);
AudioConnection          patchCord4(waveformMod6, 0, mixer2, 2);
AudioConnection          patchCord5(waveformMod2, 0, mixer1, 1);
AudioConnection          patchCord6(waveformMod3, 0, mixer1, 2);
AudioConnection          patchCord7(waveform1, 0, mixer11, 0);
AudioConnection          patchCord8(waveform2, 0, mixer11, 1);
AudioConnection          patchCord9(waveform3, 0, mixer11, 2);
AudioConnection          patchCord10(mixer1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer1, 0, mixer4, 0);
AudioConnection          patchCord12(mixer2, 0, mixer3, 1);
AudioConnection          patchCord13(mixer2, 0, mixer4, 1);
AudioConnection          patchCord14(mixer11, 0, mixer12, 1);
AudioConnection          patchCord15(mixer13, 0, waveformMod1, 0);
AudioConnection          patchCord16(mixer13, 0, waveformMod2, 0);
AudioConnection          patchCord17(mixer14, 0, waveformMod4, 0);
AudioConnection          patchCord18(mixer14, 0, waveformMod5, 0);
AudioConnection          patchCord19(mixer14, 0, waveformMod6, 0);
AudioConnection          patchCord48(mixer13, 0, waveformMod3, 0);
AudioConnection          patchCord41(dc1, envelope3);
AudioConnection          patchCord20(envelope3, 0, mixer12, 0);
AudioConnection          patchCord21(mixer4, 0, ladder2, 0);
AudioConnection          patchCord22(mixer3, 0, ladder1, 0);
AudioConnection          patchCord23(mixer12, 0, ladder1, 1);
AudioConnection          patchCord24(mixer12, 0, ladder2, 1);
AudioConnection          patchCord25(ladder1, envelope1);
AudioConnection          patchCord26(ladder2, envelope2);
AudioConnection          patchCord27(envelope1, 0, mixer5, 1);
AudioConnection          patchCord28(envelope1, amp1);
AudioConnection          patchCord29(envelope2, 0, mixer6, 1);
AudioConnection          patchCord30(envelope2, amp2);

AudioConnection          patchCord33(mixer5, 0, mixer7, 0);
AudioConnection          patchCord34(mixer6, 0, mixer10, 3);
AudioConnection          patchCord35(mixer9, 0, i2s1, 1);
AudioConnection          patchCord36(mixer10, 0, mixer9, 3);
AudioConnection          patchCord37(mixer8, 0, i2s1, 0);
AudioConnection          patchCord38(mixer7, 0, mixer8, 0);
AudioConnection          patchCord39(freeverb1, 0, mixer5, 0);
AudioConnection          patchCord40(freeverb2, 0, mixer6, 0);
AudioConnection          patchCord42(envelope3, 0, mixer13, 0);
AudioConnection          patchCord43(mixer11, 0, mixer13, 1);
AudioConnection          patchCord44(mixer11, 0, mixer14, 1);
AudioConnection          patchCord45(envelope3, 0, mixer14,0);
AudioConnection          patchCord46(dc2, 0, mixer13, 2);
AudioConnection          patchCord47(dc3, 0, mixer14, 2);
AudioConnection          patchCord49(amp1, freeverb1);
AudioConnection          patchCord50(amp2, freeverb2);

AudioControlSGTL5000     sgtl5000_1;     
// Connection end

int attack1;
int decay1;
int sustain1;
int release1;

float osc1_freq;
float osc2_freq;


void voice::init(){

  // enable the audio shield
      sgtl5000_1.enable();
      sgtl5000_1.volume(0.5); 

    //Audio Engine Element Initialisation
    //Osc Init
    waveformMod1.begin(1,440,WAVEFORM_SQUARE);
    waveformMod2.begin(1,440,WAVEFORM_SAWTOOTH);
    waveformMod3.begin(1,440,WAVEFORM_SINE);
    waveformMod4.begin(1,440,WAVEFORM_SQUARE);
    waveformMod5.begin(1,440,WAVEFORM_SAWTOOTH);
    waveformMod6.begin(1,440,WAVEFORM_SINE);
    waveform1.begin(1,440,WAVEFORM_SQUARE);
    waveform2.begin(1,440,WAVEFORM_SAWTOOTH);
    waveform3.begin(1,440,WAVEFORM_SINE);
       
    //L/R Filter init
    ladder1.frequency(5000);
    ladder1.resonance(0.5);
    ladder2.frequency(10000);
    ladder2.resonance(0.5);
    ladder1.octaveControl(7);
    ladder1.octaveControl(7);
    
    //L amp envelope init
    envelope1.attack(100);
    envelope1.decay(20);
    envelope1.sustain(0.8);
    envelope1.release(300);
    
    //R amp envelope init
    envelope2.attack(100);
    envelope2.decay(20);
    envelope2.sustain(0.8);
    envelope2.release(300);
    
    //Mod envelope init
    envelope3.attack(100);
    envelope3.decay(20);
    envelope3.sustain(0);
    envelope3.release(300);
    dc1.amplitude(1);

    //Pitch mod init
    dc2.amplitude(1);
    dc3.amplitude(1);
    
    //Osc 1 Waveform Mix
    mixer1.gain(0,0.3);
    mixer1.gain(1,0.3);
    mixer1.gain(2,0.3);
    
    //Osc 2 Waveform Mix
    mixer2.gain(0,0.3);
    mixer2.gain(1,0.3);
    mixer2.gain(2,0.3);
    
    //L Mix
    mixer3.gain(0,0.5);
    mixer3.gain(1,0.5);
    
    //R Mix
    mixer4.gain(0,0.5);
    mixer4.gain(1,0.5);
    
    //L FX MIX
    mixer5.gain(0,0);
    mixer5.gain(1,1);
    
    //R FX Mix
    mixer6.gain(0,0.5);
    mixer6.gain(1,1);

    //voice mix
    mixer7.gain(0,1);
    mixer8.gain(0,1);
    mixer9.gain(3,1);
    mixer10.gain(3,1);
    
    //LFO Init
    mixer11.gain(0,0);
    mixer11.gain(1,0);
    mixer11.gain(2,1);
    
    //mod Mix 
    mixer12.gain(0,0);
    mixer12.gain(1,0);

    //Pitch Mod mix
    mixer13.gain(0,0);
    mixer13.gain(1,0);
    mixer13.gain(2,0);
    
    mixer14.gain(0,0);
    mixer14.gain(1,0);
    mixer14.gain(2,0);

    //Reverb attenuation to avoid distortion
    amp1.gain(0.49);
    amp2.gain(0.49);

    //FX
    freeverb1.reverbTime(2);
    freeverb2.reverbTime(2);
         
}

void voice::passNote(byte note){

//MIDI note to frequency conversion table
 float MtoF[128] = {8.18, 8.66, 9.18, 9.72, 10.3, 10.91, 11.56, 12.25, 12.98, 13.75,
                    14.57, 15.53, 16.45, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5,
                    25.96, 27.5, 29.14, 30.87, 32.70, 34.65, 36.71, 38.89, 41.2, 43.65, 
                    46.25, 49, 51.95, 55, 58.27, 61.74, 65.41, 69.3, 73.42, 77.78, 82.41, 
                    87.31, 92.5, 98, 103.83, 110, 116.54, 123.47, 130.81, 146.83, 155.56,
                    164.81, 174.61, 185, 196, 207.65, 220, 233.08, 246.94, 261.63, 277.18,
                    293.66, 311.13, 349.23, 369.99, 392, 415.3, 440, 466.16, 493.88, 523.25,
                    554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880, 
                    932.33, 987.77, 1046.5, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 
                    1479.98, 1661.22, 1760, 1864.66, 1975.53, 2093, 2217.46, 2349.32, 2489.02,
                    2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520, 3729.31, 3951.07, 4186.01,
                    4434.92, 4698.64, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 
                    7040, 7458.62, 7902.13, 8372.02, 8869.84, 9397.27, 9956.06,
                    10548.08, 11175.30, 11839.82, 12543.85, 13289.75}; 
                   
                       
int m = note; 
osc1_freq = MtoF[m];
osc2_freq = osc1_freq;
  
}

void voice::amp_env(){ //function for  triggering env

  envelope1.noteOn(); //env trigger
  envelope2.noteOn(); //env trigger
  envelope3.noteOn();

}

void voice::ampOff(){
  
  envelope1.noteOff();
  envelope2.noteOff();
  envelope3.noteOff();
  
}

void voice::audioEngine(){
  
  AudioNoInterrupts(); //Main Audio Loop
  
  waveformMod1.frequency(osc1_freq);
  waveformMod2.frequency(osc1_freq);
  waveformMod3.frequency(osc1_freq);
  waveformMod4.frequency(osc2_freq);
  waveformMod5.frequency(osc2_freq);
  waveformMod6.frequency(osc2_freq);
 
  AudioInterrupts();
   
}


void voice::updateAmpAttack(int ampAttack){ // Updates attack value of L/R Amp envelopes
  envelope1.attack(ampAttack);
  envelope2.attack(ampAttack);
}

void voice::updateAmpDecay(int ampDecay){ // Updates decay value of L/R Amp envelopes
  envelope1.decay(ampDecay);
  envelope2.decay(ampDecay);
}

void voice::updateAmpSustain(float ampSustain){ // Updates sustain value of L/R Amp envelopes
  envelope1.sustain(ampSustain);
  envelope2.sustain(ampSustain);
}

void voice::updateAmpRelease(int ampRelease){ // Updates release value of L/R Amp envelopes
  envelope1.release(ampRelease);
  envelope2.release(ampRelease);
}

void voice::updateModEnv(int modAttack, int modDecay, float modSustain, int modRelease, int modEnvAmount){
  envelope3.attack(modAttack);
  envelope3.decay(modDecay);
  envelope3.sustain(modSustain);
  envelope3.release(modRelease);
  mixer12.gain(0,modEnvAmount);
}

void voice::updateVerb(float verbAmount, float roomSize ){
   freeverb1.reverbTime(roomSize);
   freeverb2.reverbTime(roomSize);
   mixer5.gain(0,verbAmount);
   mixer6.gain(0,verbAmount);
     
}

void voice::updateFil(int cutoff, float res){
  ladder1.frequency(cutoff);
  ladder2.frequency(cutoff);
  ladder1.resonance(res);
  ladder2.resonance(res); 
}

void voice::updateLfo(float rate, float lfoAmount){
  waveform1.frequency(rate);
  waveform2.frequency(rate);
  waveform3.frequency(rate);
  mixer12.gain(1,lfoAmount);
}

void voice::updateOsc1(float osc1sqr,float osc1saw,float osc1sin,float osc1Lpan,float osc1Rpan,float osc1env){
  mixer1.gain(0,osc1sqr);
  mixer1.gain(1,osc1saw);
  mixer1.gain(2,osc1sin);
  mixer3.gain(0,osc1Lpan);
  mixer4.gain(0,osc1Rpan);
  mixer13.gain(0,osc1env);
}

void voice::updateOsc2(float osc2sqr,float osc2saw,float osc2sin,float osc2Lpan,float osc2Rpan,float osc2env){
  mixer2.gain(0,osc2sqr);
  mixer2.gain(1,osc2saw);
  mixer2.gain(2,osc2sin);
  mixer3.gain(1,osc2Lpan);
  mixer4.gain(1,osc2Rpan);
  mixer13.gain(0,osc2env);
}

void voice::updatePmod(float osc1tune, float osc2tune){

  mixer13.gain(2,osc1tune);
  mixer14.gain(2,osc2tune);
  
}
