#ifndef MIDIMANAGER_HPP_
#define MIDIMANAGER_HPP_

#include <vector>
#include "Arduino.h"
#include "InputManager.hpp"
#include "ChannelManager.hpp"
#include "Monitor.hpp"

class MidiManager
{
private:
  ChannelManager *channelManager;
  InputManager *inputManager;
  Monitor *monitor;

  const int midiControls = STATIC_POTENTIOMETERS + CHANNELS * CHANNEL_POTENTIOMETERS;
  std::vector<int> midiValues = std::vector<int>(midiControls);
  void handleMidiControlChange(byte channel, byte control, byte value);
  int getMidiChannelFromPotIndex(int potIndex);
  static void staticControlChangeHandler(byte channel, byte control, byte value);

public:
  MidiManager(ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor);
  void update();
  std::vector<int> &getMidiValues();
};

#endif /* MIDIMANAGER_HPP_ */