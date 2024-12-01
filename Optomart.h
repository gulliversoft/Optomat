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

#define DELAY_TIME  1000
#define INVERT_RELAY true
#include "RelayModule.h"

#ifndef OPTOMART_H
#define OPTOMART_H
class Optomart{
public:
	Optomart(const uint8_t risingE1 = 5, const uint8_t risingE2 = 5, const uint8_t risingE3 = 5);
	void task();
  static bool m_pwrcycle_byself;
  static bool m_prompted;
private:
 	RelayModule* m_relay1;
	RelayModule* m_relay2;
	RelayModule* m_relay3;
	RelayModule* m_relay4;
	uint8_t m_risingE1;
	uint8_t m_risingE2;
	uint8_t m_risingE3;
};
#endif

