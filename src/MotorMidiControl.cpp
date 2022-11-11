#include "MotorMidiControl.hpp"
#include "Monitor.hpp"

MotorMidiControl::MotorMidiControl(ChannelManager &ch_mgr, MotorPotentiometer &pot, unsigned int cch, unsigned int mch) : MidiControl::MidiControl(ch_mgr, pot, cch, mch), pot(pot) {}

void MotorMidiControl::update()
{
  if (!should_update())
    return;

  pot.read();
  unsigned int raw_midi_value = convert_reading_to_midi(pot.get_reading());

  if (adjusting)
  {
    int diff = remote_midi_value - raw_midi_value;
    if (diff < 1)
    {
      pot.forward();
    }
    else if (diff > 1)
    {
      pot.rewind();
    }
    else
    {
      pot.stop();
      adjusting = false;
    }
  }
  else
  {
    MidiControl::update();
  }
}