#include <Arduino.h>
#include "ChannelManager.hpp"
#include "InputManager.hpp"
#include "MidiManager.hpp"
#include "Monitor.hpp"

ChannelManager *channelManager;
InputManager *inputManager;
MidiManager *midiManager;
Monitor *monitor;

void setup()
{
  monitor = new Monitor(200);
  channelManager = new ChannelManager();
  inputManager = new InputManager();
  midiManager = new MidiManager();
}

void loop()
{
  channelManager->update();
  inputManager->update();
  midiManager->update();
  monitor->print("hello");
}