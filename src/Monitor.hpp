#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include "Arduino.h"
#include <string>

class Monitor
{
private:
  uint lastPrinted = 0;
  uint interval = 1000;

public:
  Monitor(uint interval);
  void print(std::string str);
};

#endif /* MONITOR_HPP_ */