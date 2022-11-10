#include "Monitor.hpp"
#include "Arduino.h"

Monitor monitor = Monitor(50);

Monitor::Monitor(unsigned int interval)
{
  this->interval = interval;

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  unsigned int start = millis();
  unsigned int now = millis();

  // try for 5 seconds to connect to the serial port
  while (!Serial && (now - start < serialConnectTimeout))
  {
    now = millis();
    unsigned int delta = now - start;

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
  digitalWrite(ledPin, LOW);
}

void Monitor::print(int number)
{
  unsigned int now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(number);
    this->lastUpdated = now;
  }
}

void Monitor::print(const char *str)
{
  unsigned int now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(str);
    this->lastUpdated = now;
  }
}

void Monitor::print(std::string str)
{
  unsigned int now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    Serial.println(str.c_str());
    this->lastUpdated = now;
  }
}

void Monitor::print(std::vector<int> &vec)
{
  unsigned int now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    if (vec.size() == 0)
      return;
    for (unsigned int i = 0; i < vec.size(); ++i)
    {
      Serial.print(vec[i]);
      Serial.print(" ");
    }
    Serial.println("");
    this->lastUpdated = now;
  }
}

void Monitor::print(std::vector<bool> &vec)
{
  unsigned int now = millis();
  if (now - this->lastUpdated > this->interval)
  {
    if (vec.size() == 0)
      return;
    for (unsigned int i = 0; i < vec.size(); ++i)
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
  unsigned int now = millis();
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

void Monitor::print(std::stringstream &ss)
{
  print(ss.str());
}
