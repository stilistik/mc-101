#ifndef CHANNELMANAGER_HPP_
#define CHANNELMANAGER_HPP_

#include "Display.hpp"
#include "Bounce2.h"
#include "Monitor.hpp"

class ChannelManager
{
private:
  Display display;
  Monitor *monitor;

  int channelCount;
  int currentChannel = 0;

  const int button_pin_1 = 22;
  const int button_pin_2 = 23;

  Bounce ch_plus_button = Bounce(button_pin_1, 10);
  Bounce ch_minus_button = Bounce(button_pin_2, 10);

public:
  ChannelManager(int channelCount, Monitor *monitor);
  int update();
  int getCurrentChannel();
};

#endif /* CHANNELMANAGER_HPP_ */