#ifndef Plip_h
#define Plip_h
 
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif
 
class Plip {
  public:
    Plip(int pin, int period = 2000);
    void send(long code, int repeats = 3);

 
  private:
    int _pin;
    int _pulse;
    int _oneSpace1;
    int _oneSpace2;
    int _zeroSpace;
    
    inline void sendOne();
    inline void sendZero();
	  void sendDigit(byte num);
    void pulseSequence(const int* sequence, int length);

};
 
#endif