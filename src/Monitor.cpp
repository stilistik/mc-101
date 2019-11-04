#include "Monitor.hpp"
#include "Arduino.h"

Monitor::Monitor(uint interval)
{
  this->interval = interval;
}

void Monitor::print(std::string str)
{
  uint now = millis();
  if (now - lastPrinted > interval)
  {
    Serial.println(str.c_str());
    lastPrinted = now;
  }
}