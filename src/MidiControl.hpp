#ifndef MIDICONTROL_HPP_
#define MIDICONTROL_HPP_

#include <memory>
#include "Potentiometer.hpp"

class MidiControl
{
private:
  Potentiometer &pot;
  unsigned int ctrl_channel;
  unsigned int midi_channel;
  unsigned int midi_value = 0;
  unsigned int prev_midi_value = 0;
  unsigned int remote_midi_value = 0;

  unsigned int convert_reading_to_midi(unsigned int reading);
  bool get_has_changed(unsigned int value);
  void print_changes();
  void send_control_change();

public:
  MidiControl(Potentiometer &pot, unsigned int mch);
  MidiControl(Potentiometer &pot, unsigned int cch, unsigned int mch);
  virtual void update();
  unsigned int get_midi_value();
};

#endif /* MIDICONTROL_HPP_ */