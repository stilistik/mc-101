#ifndef MOTORMIDICONTROL_HPP_
#define MOTORMIDICONTROL_HPP_

#include "MidiControl.hpp"

class MotorMidiControl : public MidiControl
{
protected:
public:
  MotorMidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int cch, unsigned int mch);
  void update() override;
};

#endif /* MOTORMIDICONTROL_HPP_ */