#ifndef MOTORMIDICONTROL_HPP_
#define MOTORMIDICONTROL_HPP_

#include "MidiControl.hpp"
#include "MotorPotentiometer.hpp"

#define MOTOR_MIDI_TOLERANCE 1
#define ADUJSTMENT_TARGET_CYCLES 50

class MotorMidiControl : public MidiControl
{
protected:
  MotorPotentiometer &pot;
  bool adjusting = true;
  unsigned int ctr = 0;
  int tmp_target = -1;

public:
  MotorMidiControl(ChannelManager &ch_mgr, MotorPotentiometer &pot, unsigned int cch, unsigned int mch);
  void update() override;
  void on_channel_change(int channel) override;
  void set_remote_value(unsigned int value) override;
};

#endif /* MOTORMIDICONTROL_HPP_ */