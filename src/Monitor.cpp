#include "Monitor.hpp"
#include "Arduino.h"

Monitor::Monitor(uint interval)
{
  this->interval = interval;
  Serial.begin(9600);
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

void Monitor::print(std::vector<int> &vec)
{
  uint now = millis();
  if (now - lastPrinted > interval)
  {
    for (int i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
    lastPrinted = now;
  }
}