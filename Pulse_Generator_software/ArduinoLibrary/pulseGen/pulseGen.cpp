#include "pulseGen.h"
#include "arduino.h"

// constructor
Channel::Channel(int ch)
{
      // private default
      stoppin = 16;
      state = LOW;
      prevPulseTime = 0;
      pulseCount = 0;
      continuePulsing = 0;
      prevSwitchTime = 0;
      chatTime = 500;
      pulseCount = nPulse + 1;
      outpin = getOutpin(ch);
      trgpin = getTrgpin(ch);
      pinMode(outpin,OUTPUT);
      pinMode(trgpin,INPUT);
      pinMode(stoppin,INPUT);
      digitalWrite(outpin,state);

      // public default
      pulseWidth = 50;
      interval = 500;
      nPulse = 0;
      mode = "pulse";
};


///////////////////////////////////////////////////////////////////////////////////////////////
// private

int Channel::getOutpin(int ch)
{
    // based on circuit wiring
    int outPinList[] = {34, 35, 36, 37, 38};
    return outPinList[ch-1];
};


int Channel::getTrgpin(int ch)
{
    // based on circuit wiring
    int trgPinList[] = {24, 25, 26, 27, 28};
    return trgPinList[ch-1];
};


int Channel::setState()
{
    if(mode=="pulse"){
          return pulseState();
    }else if(mode=="toggle"){
          return toggleState();
    }else if(mode=="asinput"){
          return asinputState();
    }else if(mode=="togglePulse"){
          return togglePulseState();
    };
};

///////////////////////////////////////////////////////////////////////////////////////////////
// state for each mode


int Channel::pulseState()
{
    if(digitalRead(stoppin)==HIGH)
    {// Emergency stop
      pulseCount = nPulse + 1;
    }

    if(digitalRead(trgpin)==HIGH
       && pulseCount >= nPulse)
    {// Triggered during rest
      pulseCount = 0;
      prevPulseTime = millis();
      return HIGH;
    }

    if(pulseCount >= nPulse)
    {// reaching nPulse
      return LOW;
    }

    if ((state==HIGH)
       && (millis()>=prevPulseTime + pulseWidth))
    {// pulse off
      pulseCount += 1;
      if(nPulse == 0)
      {// unlimited
        pulseCount = 0;
      }
      return LOW;
    }

    if((state==LOW)
       && (millis() >= prevPulseTime + interval))
    {// pulse on, reset timer
      prevPulseTime = millis();
      return HIGH;
    }

    return state;
};

int Channel::toggleState()
{
    if(digitalRead(stoppin)==HIGH)
    {// Emergency stop
      return LOW;
    }

    if(millis() < prevSwitchTime + chatTime)
    {// Chattering
      return state;
    }

    if(state==LOW && digitalRead(trgpin)==HIGH)
    {// toggle on
      prevSwitchTime = millis();
      return HIGH;
    }

    if(state==HIGH && digitalRead(trgpin)==HIGH)
    {// toggle off
      prevSwitchTime = millis();
      return LOW;
    }

    return state;
};

int Channel::togglePulseState()
{
    if(digitalRead(stoppin)==HIGH)
    {// Emergency stop
      continuePulsing = 0;
      return LOW;
    }

    if(millis() < prevSwitchTime + chatTime)
    {// Chattering
      return state;
    }

    if(digitalRead(trgpin)==HIGH
      && continuePulsing == 1){
        // Stop pulsing
        continuePulsing = 0;
        prevSwitchTime = millis();
        return LOW;
      }

    if(digitalRead(trgpin)==HIGH
      && continuePulsing == 0){
        // Start pulsing
        continuePulsing = 1;
        prevSwitchTime = millis();
        prevPulseTime = millis();
        return HIGH;
      }

    if ((state==HIGH)
       && (continuePulsing == 1)
       && (millis()>=prevPulseTime + pulseWidth))
    {// pulse off
      return LOW;
    }

    if((state==LOW)
       && (continuePulsing == 1)
       && (millis() >= prevPulseTime + interval))
    {// pulse on, reset timer
      prevPulseTime = millis();
      return HIGH;
    }

    return state;

};

int Channel::asinputState()
{
    if(digitalRead(stoppin)==HIGH)
    {// Emergency stop
      return LOW;
    }
    return digitalRead(trgpin);
};

///////////////////////////////////////////////////////////////////////////////////////////////
// public


void Channel::setPulseParam(unsigned int _pulseWidth,
                       unsigned int _interval,
                       unsigned int _nPulse){
      if(mode == "pulse"){
        pulseWidth = _pulseWidth;
        interval = _interval;
        nPulse = _nPulse;
        pulseCount = nPulse + 1;
      }
};

void Channel::setTogglePulseParam(unsigned int _pulseWidth,
                         unsigned int _interval){
    if(mode == "togglePulse"){
      pulseWidth = _pulseWidth;
      interval = _interval;
      continuePulsing = 0;
    }
};

void Channel::interrupt(){
    state = setState();
    digitalWrite(outpin,state);
};
