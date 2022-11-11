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