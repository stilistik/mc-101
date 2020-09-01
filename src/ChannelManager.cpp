#include "Arduino.h"
#include "MasterController.hpp"
#include "ChannelManager.hpp"

ChannelManager::ChannelManager(MasterController *master)
{
  this->master = master;
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
    if (currentChannel >= CHANNELS)
    {
      currentChannel = 0;
    }
    master->midiManager->onChannelChange(currentChannel);
  }

  // channel minus button
  ch_minus_button.update();
  if (ch_minus_button.risingEdge())
  {
    currentChannel--;
    if (currentChannel < 0)
    {
      currentChannel = CHANNELS - 1;
    }
    master->midiManager->onChannelChange(currentChannel);
  }

  display.show(currentChannel);
  return 0;
};

int ChannelManager::getCurrentChannel()
{
  return currentChannel;
}