#include <Arduino.h>
#include "ChannelManager.hpp"
#include "InputManager.hpp"
#include "MidiManager.hpp"
#include "Monitor.hpp"

const int CHANNEL_COUNT = 1;
const int POT_COUNT = 16;
const int MIDI_CONTROL_COUNT = CHANNEL_COUNT * POT_COUNT;

ChannelManager *channelManager;
InputManager *inputManager;
MidiManager *midiManager;
Monitor *monitor;

void setup()
{
  monitor = new Monitor(200);
  channelManager = new ChannelManager(CHANNEL_COUNT, monitor);
  inputManager = new InputManager(MIDI_CONTROL_COUNT, monitor);
  midiManager = new MidiManager(MIDI_CONTROL_COUNT, channelManager, inputManager, monitor);
}

void loop()
{
  channelManager->update();
  inputManager->update();
  midiManager->update();
}