#ifndef CHANNELMANAGER_HPP_
#define CHANNELMANAGER_HPP_

#include "Display.hpp"
#include "Bounce2.h"

#define CHANNELS 10

class MasterController;

class ChannelManager
{
private:
  MasterController *master;
  Display display;
  

  int currentChannel = 0;

  const int button_pin_1 = 22;
  const int button_pin_2 = 23;

  Bounce ch_plus_button = Bounce(button_pin_1, 10);
  Bounce ch_minus_button = Bounce(button_pin_2, 10);

public:
  ChannelManager(MasterController *master);
  int update();
  int getCurrentChannel();
};

#endif /* CHANNELMANAGER_HPP_ */