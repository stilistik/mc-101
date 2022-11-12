#ifndef CHANNELMANAGER_HPP_
#define CHANNELMANAGER_HPP_

#include "Display.hpp"
#include "Bounce2.h"
#include <vector>
#include <map>

#define CHANNELS 10
#define BUTTON_PIN_1 22
#define BUTTON_PIN_2 23

class ChannelChangeListener
{
public:
  virtual void on_channel_change(int ch) = 0;
};

class ChannelManager
{
private:
  Display display;
  int current_channel = 0;

  Bounce ch_plus_button = Bounce(BUTTON_PIN_1, 10);
  Bounce ch_minus_button = Bounce(BUTTON_PIN_2, 10);

  std::vector<ChannelChangeListener *> listeners;
  std::map<int, bool> adjusting_motors;

  void set_channel(int ch);

public:
  void update();
  int get_current_channel();
  void register_listener(ChannelChangeListener *l);
  bool get_is_changing();
  void set_is_changing(bool value, unsigned int pot_index);
};

#endif /* CHANNELMANAGER_HPP_ */