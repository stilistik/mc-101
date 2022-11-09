#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include "Arduino.h"
#include "Potentiometer.hpp"
#include <string>
#include <vector>
#include <map>
#include <sstream>

class Monitor
{
private:
  unsigned int lastUpdated = 0;
  unsigned int interval = 1000;
  const int ledPin = 21;
  const unsigned int serialConnectTimeout = 3000;

public:
  Monitor(unsigned int interval);
  void print(int number);
  void print(const char *str);
  void print(std::string str);
  void print(std::vector<int> &vec);
  void print(std::vector<bool> &vec);
  void print(std::map<int, int> &map);
  void print(std::stringstream &ss);
  void print(const Potentiometer &pot);
};

#endif /* MONITOR_HPP_ */