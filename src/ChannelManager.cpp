#include "ChannelManager.hpp"
#include "Arduino.h"

ChannelManager::ChannelManager(int channelCount, Monitor *monitor)
{
  this->monitor = monitor;
  this->channelCount = channelCount;
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
    if (currentChannel >= this->channelCount)
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
      currentChannel = this->channelCount - 1;
    }
  }

  display.show(currentChannel);
  return 0;
};

int ChannelManager::getCurrentChannel()
{
  return currentChannel;
}