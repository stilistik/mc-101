#include "Arduino.h"
#include "MasterController.hpp"
#include "ChannelManager.hpp"

int ChannelManager::update()
{
  // channel plus button
  ch_plus_button.update();
  if (ch_plus_button.risingEdge())
  {
    current_channel++;
    if (current_channel >= CHANNELS)
    {
      current_channel = 0;
    }
  }

  // channel minus button
  ch_minus_button.update();
  if (ch_minus_button.risingEdge())
  {
    current_channel--;
    if (current_channel < 0)
    {
      current_channel = CHANNELS - 1;
    }
  }

  display.show(current_channel);
  return 0;
};

int ChannelManager::get_current_channel()
{
  return current_channel;
}