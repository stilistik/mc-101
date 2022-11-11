#include "MotorMidiControl.hpp"
#include "Monitor.hpp"

MotorMidiControl::MotorMidiControl(ChannelManager &ch_mgr, Potentiometer &pot, unsigned int cch, unsigned int mch) : MidiControl::MidiControl(ch_mgr, pot, cch, mch) {}

void MotorMidiControl::update()
{
  MidiControl::update();
}