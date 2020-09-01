#include "MidiManager.hpp"
#include "Arduino.h"
#include <stdlib.h>
#include "MasterController.hpp"

MidiManager *instance;
MidiManager::MidiManager(MasterController *master)
{
  // store this instance as the handler instance
  instance = this;

  // init
  this->master = master;

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
  sync[control] = false;
}

void MidiManager::update()
{
  std::vector<int> potValues =  master->inputManager->getPotValues();
  for (uint ctr = 0; ctr < potValues.size(); ++ctr)
  {
    // compute midi value
    int midiValue = map(potValues[ctr], 0, 1023, 0, 127);

    // get the midi channel
    int midiChannel = this->getMidiChannelFromPotIndex(ctr);

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
    int channel = master->channelManager->getCurrentChannel();
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

void MidiManager::onChannelChange(int channel)
{
  int minCh = STATIC_POTENTIOMETERS + channel * CHANNEL_POTENTIOMETERS;
  int maxCh = STATIC_POTENTIOMETERS + (channel + 1) * CHANNEL_POTENTIOMETERS;
  for (int ch = minCh; ch < maxCh; ++ch)
  {
    sync[ch] = false;
  }
}