#ifndef CHANNELMANAGER_HPP_
#define CHANNELMANAGER_HPP_

#include "Display.hpp"
#include "Bounce2.h"

#define CHANNELS 10
#define BUTTON_PIN_1 22
#define BUTTON_PIN_2 23

class MasterController;

class ChannelManager
{
private:
  Display display;
  int current_channel = 0;

  Bounce ch_plus_button = Bounce(BUTTON_PIN_1, 10);
  Bounce ch_minus_button = Bounce(BUTTON_PIN_2, 10);

public:
  void update();
  int get_current_channel();
};

#endif /* CHANNELMANAGER_HPP_ */