#ifndef MIDICONTROL_HPP_
#define MIDICONTROL_HPP_

#include "Potentiometer.hpp"
#include "ChannelManager.hpp"

class MidiControl
{
protected:
  ChannelManager &ch_mgr;
  int ctrl_channel = -1;
  Potentiometer &pot;
  unsigned int midi_channel;
  unsigned int midi_value = 0;
  unsigned int prev_midi_value = 0;
  unsigned int remote_midi_value = 0;

  unsigned int
  convert_reading_to_midi(unsigned int reading);
  bool get_has_changed(unsigned int value);
  void print_changes();
  void send_control_change();
  bool should_update();
  bool pickup_remote_value(unsigned int value);

public:
  MidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int mch);
  MidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int cch, unsigned int mch);
  virtual void update();
  unsigned int get_midi_value();
  void set_remote_value(unsigned int remote_value);
};

#endif /* MIDICONTROL_HPP_ */