#include <Arduino.h>
#include "ChannelManager.hpp"
#include "InputManager.hpp"
#include "MidiManager.hpp"
#include "MotorManager.hpp"
#include "Monitor.hpp"

ChannelManager *channelManager;
InputManager *inputManager;
MidiManager *midiManager;
MotorManager *motorManager;
Monitor *monitor;

void setup()
{
  monitor = new Monitor(50);
  channelManager = new ChannelManager(monitor);
  inputManager = new InputManager(monitor);
  midiManager = new MidiManager(channelManager, inputManager, monitor);
  motorManager = new MotorManager(monitor);
}

void loop()
{
  channelManager->update();
  inputManager->update();
  midiManager->update();
  motorManager->update();
}