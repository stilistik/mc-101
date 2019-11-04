#include "ChannelManager.hpp"
#include "Arduino.h"

ChannelManager::ChannelManager()
{
  pinMode(button_pin_1, INPUT_PULLDOWN);
  pinMode(button_pin_2, INPUT_PULLDOWN);
};

int ChannelManager::update()
{
  // channel plus button
  ch_plus_button.update();
  if (ch_plus_button.risingEdge())
  {
    currentChannel++;
    if (currentChannel >= maxChannel)
    {
      currentChannel = 0;
    }
  }

  // channel minus button
  ch_minus_button.update();
  if (ch_minus_button.risingEdge())
  {
    currentChannel--;
    if (currentChannel < 0)
    {
      currentChannel = maxChannel - 1;
    }
  }

  display.show(currentChannel);
  return 0;
};