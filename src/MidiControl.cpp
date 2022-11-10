#include "Arduino.h"
#include "MidiControl.hpp"
#include "Monitor.hpp"

MidiControl::MidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int mch)
    : pot(pot), midi_channel(mch) {}

MidiControl::MidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int ctrl_channel, unsigned int midi_channel)
    : ch_mgr(ch_mgr), ctrl_channel(ctrl_channel), pot(pot), midi_channel(midi_channel) {}

void MidiControl::update()
{
  if (!should_update())
    return;

  prev_midi_value = midi_value;

  pot.read();

  unsigned int raw_midi_value = convert_reading_to_midi(pot.get_reading());
  if (get_has_changed(raw_midi_value))
  {
    midi_value = raw_midi_value;
    print_changes();
    send_control_change();
  }
}

bool MidiControl::should_update()
{
  if (ctrl_channel == -1)
    return true;
  else
    return ch_mgr.get_current_channel() == ctrl_channel;
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