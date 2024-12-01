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
bool Optomart::m_pwrcycle_byself = false;
bool Optomart::m_prompted = false;

Optomart::Optomart(const uint8_t risingE1 = 5, const uint8_t risingE2 = 5, const uint8_t risingE3 = 5)
 {
	m_risingE1 = risingE1;
	m_risingE2 = risingE2;
	m_risingE3 = risingE3;
	m_relay1 = new RelayModule(5, INVERT_RELAY);
	m_relay2 = new RelayModule(4, INVERT_RELAY);
	m_relay3 = new RelayModule(7, INVERT_RELAY);
	m_relay4 = new RelayModule(6, INVERT_RELAY); 
}

void Optomart::task() {
  int Vout = analogRead(A0) + analogRead(A1) + analogRead(A2);
  Serial.println(Vout);  
  if(Serial.available() && Serial.read())
  {
    Optomart::m_prompted = true;
  }
  if((Vout > m_risingE1 + m_risingE2 + m_risingE3) || Optomart::m_prompted)
  {
    Optomart::m_prompted = false;
    if (m_relay1->isOff()) {
      m_relay1->on();
      Optomart::m_pwrcycle_byself = true;
    }

    if (m_relay2->isOff()) {
      m_relay2->on();
    }

    if (m_relay3->isOff()) {
      m_relay3->on();
    }

    if (m_relay4->isOff()) {
      m_relay4->on();

    }

    delay(DELAY_TIME); // overloop regulation
  }
  else if(Vout <= 3 && Optomart::m_pwrcycle_byself)
  {
    if (m_relay1->isOn()) {
      Optomart::m_prompted = false;
      m_relay1->off();
    }

    if (m_relay2->isOn()) {
      m_relay2->off();
    }

    if (m_relay3->isOn()) {
      m_relay3->off();
    }

    if (m_relay4->isOn()) {
      m_relay4->off();
    }
  }

}