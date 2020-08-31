#ifndef MOTORMANAGER_HPP_
#define MOTORMANAGER_HPP_

#include "MidiManager.hpp"
#include "ChannelManager.hpp"
#include "Monitor.hpp"

#define MOTOR_POTENTIOMETERS 5

class MotorManager
{
private:
  Monitor *monitor;
  MidiManager *midiManager;
  ChannelManager *channelManager;

  const int motorEnablePin = 0;
  const int motorForwardPins[MOTOR_POTENTIOMETERS] = {1, 3, 5, 7, 9};
  const int motorRewindPins[MOTOR_POTENTIOMETERS] = {2, 4, 6, 8, 10};
  const int tolerance = 2;

  int getMidiChannelFromPotIndex(int potIndex);

public:
  MotorManager(ChannelManager *channelManager, MidiManager *midiManager, Monitor *monitor);
  void update();
};

#endif /* MOTORMANAGER_HPP_ */
