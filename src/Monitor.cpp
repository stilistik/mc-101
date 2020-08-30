#include "Monitor.hpp"

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

void Monitor::print(std::vector<int> &vec)
{
  uint now = millis();
  if (now - lastPrinted > interval)
  {
    for (uint i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
    lastPrinted = now;
  }
}

void Monitor::print(std::map<int, int> &map)
{
  uint now = millis();
  if (now - lastPrinted > interval)
  {
    std::map<int, int>::iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
      Serial.print(it->first);
      Serial.print(":");
      Serial.print(it->second);
      Serial.print(" ");
    }
    Serial.println("");
  }
}