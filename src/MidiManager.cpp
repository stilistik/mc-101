#include "MidiManager.hpp"
#include "InputManager.hpp"
#include "ChannelManager.hpp"
#include "Monitor.hpp"
#include "Arduino.h"
#include <stdlib.h>

MidiManager *instance;
MidiManager::MidiManager(ChannelManager *channelManager, InputManager *inputManager, Monitor *monitor)
{
  // store this instance as the handler instance
  instance = this;

  // init
  this->channelManager = channelManager;
  this->inputManager = inputManager;
  this->monitor = monitor;

  // initialize value containers
  for (int ctr = 0; ctr < midiControlCount; ++ctr)
  {
    midiValues[ctr] = 0;
    remoteValues[ctr] = 0;
    sync[ctr] = false;
  }

  // set the midi control change handler
  usbMIDI.setHandleControlChange(MidiManager::staticControlChangeHandler);
}

void MidiManager::handleMidiControlChange(byte channel, byte control, byte value)
{
  // store the value in the parameter array
  remoteValues[control] = value;
}

void MidiManager::update()
{
  std::map<int, int> changes = inputManager->getChangedPotValues();
  // monitor->print(changes);

  if (changes.size() == 0)
  {
    return;
  }

  std::map<int, int>::iterator it;
  for (it = changes.begin(); it != changes.end(); ++it)
  {
    // compute midi value
    int potIndex = it->first;
    int midiValue = map(it->second, 0, 1023, 0, 127);

    // get the midi channel
    int midiChannel = this->getMidiChannelFromPotIndex(potIndex);

    // store midi value
    midiValues[midiChannel] = midiValue;
    int remoteValue = this->getRemoteValue(midiChannel);

    if (abs(midiValue - remoteValue) < 2)
    {
      sync[midiChannel] = true;
    }
    // send midi value to daw
    usbMIDI.sendControlChange(index, midiValue, 1);
  }
}

void MidiManager::staticControlChangeHandler(byte channel, byte control, byte value)
{
  instance->handleMidiControlChange(channel, control, value);
}

int MidiManager::getMidiChannelFromPotIndex(int potIndex)
{
  if (potIndex < STATIC_POTENTIOMETERS)
  {
    return potIndex;
  }
  else
  {
    int channel = channelManager->getCurrentChannel();
    return STATIC_POTENTIOMETERS + channel * CHANNEL_POTENTIOMETERS + (potIndex - STATIC_POTENTIOMETERS);
  }
}

int MidiManager::getMidiValue(int midiChannel)
{
  return midiValues[midiChannel];
}

int MidiManager::getRemoteValue(int midiChannel)
{
  return remoteValues[midiChannel];
}

bool MidiManager::isSynchronized(int midiChannel)
{
  return sync[midiChannel];
}