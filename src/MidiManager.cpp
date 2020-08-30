#include "MidiManager.hpp"

MidiManager *instance;
MidiManager::MidiManager(int midiControlCount, ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor)
{
  instance = this;
  this->channelManager = channelManager;
  this->inputManager = inputManager;
  this->monitor = monitor;
  midiValues = std::vector<int>(midiControlCount);
}

void MidiManager::handleMidiControlChange(byte channel, byte control, byte value)
{
  // store the value in the parameter array
  MidiManager::midiValues[control] = value;
}

void MidiManager::update()
{
  monitor->print("test");

  std::map<int, int> changes = inputManager->getChangedPotValues();
  monitor->print(changes);
}

void MidiManager::staticControlChangeHandler(byte channel, byte control, byte value)
{
  instance->handleMidiControlChange(channel, control, value);
}

std::vector<int> &MidiManager::getMidiValues()
{
  return midiValues;
}