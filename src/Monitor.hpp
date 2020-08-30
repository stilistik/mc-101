#ifndef MONITOR_HPP_
#define MONITOR_HPP_

#include "Arduino.h"
#include <string>
#include <vector>
#include <map>

class Monitor
{
private:
  uint lastPrinted = 0;
  uint interval = 1000;

public:
  Monitor(uint interval);
  void print(std::string str);
  void print(std::vector<int>& vec);
  void print(std::map<int, int>& map);
};

#endif /* MONITOR_HPP_ */