#include "MotorManager.hpp"

MotorManager::MotorManager(ChannelManager *channelManager, MidiManager *midiManager, Monitor *monitor)
{
  this->channelManager = channelManager;
  this->midiManager = midiManager;
  this->monitor = monitor;

  // activate motor pins
  pinMode(motorEnablePin, OUTPUT);
  for (int ctr = 0; ctr < MOTOR_POTENTIOMETERS; ctr++)
  {
    pinMode(motorForwardPins[ctr], OUTPUT);
    pinMode(motorRewindPins[ctr], OUTPUT);
  }
}

void MotorManager::update()
{
  for (int ctr = 0; ctr < MOTOR_POTENTIOMETERS; ++ctr)
  {
    int ch = this->getMidiChannelFromPotIndex(ctr);

    int midiValue = midiManager->getMidiValue(ch);
    int remoteValue = midiManager->getRemoteValue(ch);
    bool isSync = midiManager->isSynchronized(ch);

    if ((midiValue < remoteValue + tolerance) && (midiValue > remoteValue - tolerance))
    {
      digitalWrite(motorForwardPins[ctr], LOW);
      digitalWrite(motorRewindPins[ctr], LOW);
    }

    if (!isSync)
    {
      if (midiValue - tolerance > remoteValue)
      {
        digitalWrite(motorEnablePin, HIGH);
        digitalWrite(motorForwardPins[ctr], HIGH);
        digitalWrite(motorRewindPins[ctr], LOW);
      }
      else if (midiValue + tolerance < remoteValue)
      {
        digitalWrite(motorEnablePin, HIGH);
        digitalWrite(motorForwardPins[ctr], LOW);
        digitalWrite(motorRewindPins[ctr], HIGH);
      }
    }
  }
}

int MotorManager::getMidiChannelFromPotIndex(int potIndex)
{
  int channel = channelManager->getCurrentChannel();
  return STATIC_POTENTIOMETERS + channel * CHANNEL_POTENTIOMETERS + potIndex;
}