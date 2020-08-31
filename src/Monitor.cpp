#include "Monitor.hpp"
#include "Arduino.h"

Monitor::Monitor(uint interval)
{
  this->interval = interval;

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  uint start = millis();
  uint now = millis();

  // try for 5 seconds to connect to the serial port
  while (!Serial && (now - start < serialConnectTimeout))
  {
    now = millis();
    uint delta = now - start;

    // blink the led during serial monitor connection
    if (delta % 1000 > 500)
    {
      digitalWrite(ledPin, HIGH);
    }
    else
    {
      digitalWrite(ledPin, LOW);
    }
  }
  Serial.println("Serial connected.");
}

void Monitor::print(int number)
{
  uint now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(number);
    this->lastUpdated = now;
  }
}

void Monitor::print(const char *str)
{
  uint now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(str);
    this->lastUpdated = now;
  }
}

void Monitor::print(std::string str)
{
  uint now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(str.c_str());
    this->lastUpdated = now;
  }
}

void Monitor::print(std::vector<int> &vec)
{
  uint now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    if (vec.size() == 0)
      return;
    for (uint i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
    this->lastUpdated = now;
  }
}

void Monitor::print(std::map<int, int> &map)
{
  uint now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    if (map.size() == 0)
      return;

    std::map<int, int>::iterator it;
    for (it = map.begin(); it != map.end(); ++it)
    {
      Serial.print(it->first);
      Serial.print(":");
      Serial.print(it->second);
      Serial.print(" ");
    }
    Serial.println("");
    this->lastUpdated = now;
  }
}