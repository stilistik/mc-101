#include "MidiManager.hpp"
#include "InputManager.hpp"
#include "ChannelManager.hpp"
#include "Monitor.hpp"
#include "Arduino.h"

MidiManager *instance;
MidiManager::MidiManager(ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor)
{
  // store this instance as the handler instance
  instance = this;

  // init
  this->channelManager = channelManager;
  this->inputManager = inputManager;
  this->monitor = monitor;

  // set the midi control change handler
  usbMIDI.setHandleControlChange(MidiManager::staticControlChangeHandler);
}

void MidiManager::handleMidiControlChange(byte channel, byte control, byte value)
{
  // store the value in the parameter array
  midiValues[control] = value;
}

void MidiManager::update()
{
  std::map<int, int> changes = inputManager->getChangedPotValues();
  monitor->print(changes);

  if (changes.size() == 0)
    return;

  std::map<int, int>::iterator it;
  for (it = changes.begin(); it != changes.end(); ++it)
  {
    // compute midi value
    int index = it->first;
    int midiValue = map(it->second, 0, 1023, 0, 127);
    
    // store midi value
    midiValues[index] = midiValue;

    // send midi value to daw
    usbMIDI.sendControlChange(index, midiValue, 1);
  }
}

void MidiManager::staticControlChangeHandler(byte channel, byte control, byte value)
{
  instance->handleMidiControlChange(channel, control, value);
}

std::vector<int> &MidiManager::getMidiValues()
{
  return midiValues;
}