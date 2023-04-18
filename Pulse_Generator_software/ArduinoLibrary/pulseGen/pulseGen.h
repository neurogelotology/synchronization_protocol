/*
    pulseGen.h - Library for pulse generator.
    Created by Shimpei Ishiyama, 2020.
*/
#ifndef pulseGen_h
#define pulseGen_h

#include "Arduino.h"


class Channel {
  private:
    int outpin;
    int trgpin;
    int stoppin;
    int state;
    unsigned long prevPulseTime;
    unsigned int pulseCount;
    unsigned int continuePulsing;
    int ch;
    unsigned long prevSwitchTime;
    unsigned long chatTime;


    int getOutpin(int ch);
    int getTrgpin(int ch);
    int setState();

///////////////////////////////////////////////////////////////////////////////////////////////

    int pulseState();
    int toggleState();
    int togglePulseState();
    int asinputState();

///////////////////////////////////////////////////////////////////////////////////////////////

  public:
    unsigned int pulseWidth;
    unsigned int interval;
    unsigned int nPulse; // 0 for unlimited
    String mode; // pulse; toggle; asinput

    // constructor
    Channel(int ch);

    void setPulseParam(unsigned int _pulseWidth,
                       unsigned int _interval,
                       unsigned int _nPulse);

    void setTogglePulseParam(unsigned int _pulseWidth,
                             unsigned int _interval);

    void interrupt();

};

#endif
