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

  std::vector<int> midiValues;
  void handleMidiControlChange(byte channel, byte control, byte value);

  static void staticControlChangeHandler(byte channel, byte control, byte value);

public:
  MidiManager(int midiControlCount, ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor);
  void update();
  std::vector<int> &getMidiValues();
};

#endif /* MIDIMANAGER_HPP_ */