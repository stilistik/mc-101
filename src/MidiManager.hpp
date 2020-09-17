#ifndef MIDIMANAGER_HPP_
#define MIDIMANAGER_HPP_

#include <vector>
#include "Arduino.h"
#include "InputManager.hpp"
#include "ChannelManager.hpp"
#include "Monitor.hpp"

class MasterController;

class MidiManager
{
private:
  MasterController *master;

  const int ledPin = 21;
  const int tolerance = 2;
  const int midiControlCount = STATIC_POTENTIOMETERS + CHANNELS * CHANNEL_POTENTIOMETERS;
  const unsigned long syncDuration = 1000; // ms

  unsigned long timer = 0;
  std::vector<int> midiValues = std::vector<int>(midiControlCount);
  std::vector<int> remoteValues = std::vector<int>(midiControlCount);
  std::vector<bool> sync = std::vector<bool>(midiControlCount);

  void handleMidiControlChange(byte channel, byte control, byte value);
  int getMidiChannelFromPotIndex(int potIndex);
  static void staticControlChangeHandler(byte channel, byte control, byte value);
  void sendMidi();
  void updateSync();
  bool isCurrentChannelSynchronizing();

public:
  MidiManager(MasterController *master);
  void update();
  int getMidiValue(int midiChannel);
  int getRemoteValue(int midiChannel);
  bool isSynchronized(int midiChannel);

  void onChannelChange(int newChannel);
};

#endif /* MIDIMANAGER_HPP_ */