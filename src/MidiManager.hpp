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

  const int tolerance = 2;
  const int midiControlCount = STATIC_POTENTIOMETERS + CHANNELS * CHANNEL_POTENTIOMETERS;

  std::vector<int> midiValues = std::vector<int>(midiControlCount);
  std::vector<int> remoteValues = std::vector<int>(midiControlCount);
  std::vector<bool> sync = std::vector<bool>(midiControlCount);

  void handleMidiControlChange(byte channel, byte control, byte value);
  int getMidiChannelFromPotIndex(int potIndex);
  static void staticControlChangeHandler(byte channel, byte control, byte value);

public:
  MidiManager(ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor);
  void update();
  int getMidiValue(int midiChannel);
  int getRemoteValue(int midiChannel);
  bool isSynchronized(int midiChannel);
};

#endif /* MIDIMANAGER_HPP_ */