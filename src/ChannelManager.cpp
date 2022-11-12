#include "Arduino.h"
#include "Monitor.hpp"
#include "ChannelManager.hpp"

void ChannelManager::update()
{
  // channel plus button
  ch_plus_button.update();
  if (ch_plus_button.risingEdge())
  {
    set_channel(current_channel + 1);
  }

  // channel minus button
  ch_minus_button.update();
  if (ch_minus_button.risingEdge())
  {
    set_channel(current_channel - 1);
  }

  display.show(current_channel);
};

void ChannelManager::set_channel(int channel)
{
  current_channel = constrain(channel, 0, CHANNELS);
  for (auto l : listeners)
  {
    l->on_channel_change(current_channel);
  }
}

int ChannelManager::get_current_channel()
{
  return current_channel;
}

void ChannelManager::register_listener(ChannelChangeListener *listener)
{
  listeners.push_back(listener);
}

void ChannelManager::set_is_changing(bool value, unsigned int channel)
{
  std::map<int, bool>::iterator itr;

  itr = adjusting_motors.find(channel);
  if (itr != adjusting_motors.end())
  {
    itr->second = value;
  }
  else
  {
    adjusting_motors.insert({channel, value});
  }
}

bool ChannelManager::get_is_changing()
{
  for (auto entry : adjusting_motors)
  {
    if (entry.second)
    {
      return true;
    }
  }
  return false;
}