#include <pulseGen.h>

Channel ch1(1);
Channel ch2(2);
Channel ch3(3);
Channel ch4(4);
Channel ch5(5);

void setup() {
ch1.mode = "togglePulse";
ch1.setTogglePulseParam(100,1000);

ch2.mode = "toggle";

ch3.mode = "asinput";


ch4.mode = "pulse";
ch4.setPulseParam(2,10,200); // pulseWidth, interval, nPulse

ch5.mode = "pulse";
ch5.setPulseParam(2000,1,1);

};

void loop() {
  ch1.interrupt();
  ch2.interrupt();
  ch3.interrupt();
  ch4.interrupt();
  ch5.interrupt();
 };
