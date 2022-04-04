#ifndef voice_h
#define voice_h

#include <Audio.h>
#include <Wire.h>
#include <SerialFlash.h>

/** Voice Class
* @brief Synthesis and main audio engine
* @author Matt Ayres
* @date March 2022
*/


class voice
{
  public:

   /** Constructor */
  //  voice();
    
    /** Destructor */
  //  ~voice();

    void init();
    void audioEngine();
    void amp_env();
    void passNote(byte note);
    void ampOff();
    void updateAmpAttack(int ampAttack);
    void updateAmpDecay(int ampDecay);
    void updateAmpSustain(float ampSustain);
    void updateAmpRelease(int ampRelease);
    void updateVerb(float verbAmount, float roomSize);
    void updateFil(int cutoff, float res);
    void updateLfo(float rate, float lfoAmount);
    void updateOsc1(float osc1sqr,float osc1saw,float osc1sin,float osc1Lpan,float osc1Rpan,float osc1env);
    void updateOsc2(float osc2sqr,float osc2saw,float osc2sin,float osc2Lpan,float osc2Rpan,float osc2env);
    void updateModEnv(int modAttack, int modDecay, float modSustain, int modRelease, int modEnvAmount);
    void updatePmod(float osc1tune, float osc2tune);
    int osc1_freq;
    int osc2_freq;
    float MtoF[128];

    
  private:

    
  
};

#endif
