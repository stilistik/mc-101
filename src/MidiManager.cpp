#include "MidiManager.hpp"
#include "Arduino.h"
#include <stdlib.h>
#include <algorithm>
#include "MasterController.hpp"

// keep track of the midi manager instance to route events from static handlers
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

  // set led pinmode
  pinMode(ledPin, OUTPUT);

  // set the midi control change handler
  usbMIDI.setHandleControlChange(staticControlChangeHandler);
}

void MidiManager::handleMidiControlChange(byte channel, byte control, byte value)
{
  // store the value in the parameter array
  remoteValues[control] = value;
  sync[control] = false;
}

void MidiManager::update()
{
  // update the synchronized state
  this->updateSync();
  this->sendMidi();

  // // if we are not synchronizing, send midi changes
  // if (!isCurrentChannelSynchronizing())
  // {
  //   this->sendMidi();
  //   digitalWrite(ledPin, LOW);
  // }
  // else
  // {
  //   digitalWrite(ledPin, HIGH);
  // }

  while (usbMIDI.read())
  {
    ; // read all incoming midi messages
  }
}

void MidiManager::sendMidi()
{
  // we get the changes from the input manager, we are only interested in
  // interactions, i.e. pot values that changed since the last iteration
  std::map<int, int> changes = master->inputManager->getChangedPotValues();
  if (changes.size() == 0)
  {
    return;
  }

  std::map<int, int>::iterator it;
  for (it = changes.begin(); it != changes.end(); ++it)
  {
    // compute midi value
    int potIndex = it->first;

    // get the midi channel
    int midiChannel = this->getMidiChannelFromPotIndex(potIndex);
    int midiValue = midiValues[midiChannel];
    int remoteValue = remoteValues[midiChannel];

    if (abs(midiValue - remoteValue) >= midiTolerance)
    {
      // if the midi value is significantly different from the last observed
      // remote value, send midi value to DAW
      usbMIDI.sendControlChange(midiChannel, midiValue, 1);
    }
  }
}

void MidiManager::updateSync()
{
  std::vector<int> potValues = master->inputManager->getPotValues();
  for (unsigned int ctr = 0; ctr < potValues.size(); ++ctr)
  {
    // compute midi value
    int midiValue = map(potValues[ctr], 0, 1023, 0, 127);

    // get the midi channel
    int midiChannel = this->getMidiChannelFromPotIndex(ctr);

    // store midi value
    midiValues[midiChannel] = midiValue;
    int remoteValue = this->getRemoteValue(midiChannel);

    if (abs(midiValue - remoteValue) <= midiTolerance)
    {
      sync[midiChannel] = true;
    }
  }
}

void MidiManager::staticControlChangeHandler(byte channel, byte control, byte value)
{
  instance->handleMidiControlChange(channel, control, value);
}

bool MidiManager::isCurrentChannelSynchronizing()
{
  int channel = master->channelManager->getCurrentChannel();
  int start = STATIC_POTENTIOMETERS + channel * CHANNEL_POTENTIOMETERS;
  int end = STATIC_POTENTIOMETERS + channel * CHANNEL_POTENTIOMETERS + MOTOR_POTENTIOMETERS;
  for (int ctr = start; ctr < end; ++ctr)
  {
    if (!sync[ctr])
    {
      timer = millis();
      return true;
    }
  }

  unsigned long elapsed = millis() - timer;
  if (elapsed > syncDuration)
  {
    return false;
  }
  else
  {
    return true;
  }
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

std::vector<int> &MidiManager::getMidiValues()
{
  return midiValues;
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