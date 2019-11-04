#ifndef CHANNELMANAGER_HPP_
#define CHANNELMANAGER_HPP_

#include "Display.hpp"
#include "Bounce2.h"

class ChannelManager
{
private:
  Display display;

  const int button_pin_1 = 22;
  const int button_pin_2 = 23;

  Bounce ch_plus_button = Bounce(button_pin_1, 10);
  Bounce ch_minus_button = Bounce(button_pin_2, 10);

  const int maxChannel = 12;
  int currentChannel = 0;

public:
  ChannelManager();
  int update();
};

#endif /* CHANNELMANAGER_HPP_ */