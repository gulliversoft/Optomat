/*
  Optomart is a 3-way maintainable 4 power lines invert switch
  Turns off for the specified DELAY_TIME,
  then turns selfs back on.
  This happens either by the task reading all the 3 light sensors and act by result of level summation,
  or reading any char put by the serial connection command line
  or push of the emergency button
  
  Created by Martin Shishkov, November, 2024.
	Released into the public domain.
*/
#include "Optomart.h"
Optomart* optomart;

void setup() {
  Serial.begin(115200);
  optomart = new Optomart();
}
void loop() {
  optomart->task();
}