#ifndef MOTORMIDICONTROL_HPP_
#define MOTORMIDICONTROL_HPP_

#include "MidiControl.hpp"
#include "MotorPotentiometer.hpp"

class MotorMidiControl : public MidiControl
{
protected:
  MotorPotentiometer &pot;
  bool adjusting = true;

public:
  MotorMidiControl(ChannelManager &ch_mgr, MotorPotentiometer &pot, unsigned int cch, unsigned int mch);
  void update() override;
};

#endif /* MOTORMIDICONTROL_HPP_ */