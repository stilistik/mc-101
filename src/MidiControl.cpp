#include "Arduino.h"
#include "MidiControl.hpp"
#include "Monitor.hpp"

MidiControl::MidiControl(Potentiometer &pot, unsigned int mch) : pot(pot), midi_channel(mch) {}
MidiControl::MidiControl(Potentiometer &pot, unsigned int cch, unsigned int mch) : pot(pot), ctrl_channel(cch), midi_channel(mch) {}

void MidiControl::update()
{
  prev_midi_value = midi_value;

  pot.read();

  unsigned int raw_midi_value = convert_reading_to_midi(pot.get_reading());
  if (get_has_changed(raw_midi_value))
  {
    midi_value = raw_midi_value;
    send_control_change();
  }
}

void MidiControl::print_changes()
{
  std::stringstream ss;
  ss << "CC " << midi_channel << " | Value: " << midi_value << " | Prev: " << prev_midi_value;
  monitor.print(ss);
}

void MidiControl::send_control_change()
{
  usbMIDI.sendControlChange(midi_channel, midi_value, 1);
}

bool MidiControl::get_has_changed(unsigned int value)
{
  return abs(prev_midi_value - value) > 0;
}

unsigned int MidiControl::convert_reading_to_midi(unsigned int reading)
{
  return map(reading, 0, 1023, 0, 127);
}

unsigned int MidiControl::get_midi_value()
{
  return midi_value;
}