#ifndef MOTORMIDICONTROL_HPP_
#define MOTORMIDICONTROL_HPP_

#include "MidiControl.hpp"
#include "MotorPotentiometer.hpp"

class MotorMidiControl : public MidiControl, public ChannelChangeListener
{
protected:
  MotorPotentiometer &pot;
  bool adjusting = true;
  unsigned int ctr = 0;

public:
  MotorMidiControl(ChannelManager &ch_mgr, MotorPotentiometer &pot, unsigned int cch, unsigned int mch);
  void update() override;
  void on_channel_change(int channel) override;
};

#endif /* MOTORMIDICONTROL_HPP_ */