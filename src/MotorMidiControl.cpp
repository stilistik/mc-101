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
    if (diff < -MOTOR_MIDI_TOLERANCE)
    {
      pot.forward();
    }
    else if (diff > MOTOR_MIDI_TOLERANCE)
    {
      pot.rewind();
    }
    else
    {
      pot.stop();

      ctr++;
      if (ctr >= ADUJSTMENT_TARGET_CYCLES)
      {
        // the memasured value must be within tolerance for a number of cycles
        // before we stop adjusting and start sending midi again
        adjusting = false;
        ctr = 0;
      }
    }
  }
  else
  {
    MidiControl::update();
  }
}

void MotorMidiControl::on_channel_change(int channel)
{
  adjusting = false;
  if (channel == ctrl_channel)
  {
    adjusting = true;
  }
}

void MotorMidiControl::set_remote_value(unsigned int value)
{
  remote_midi_value = value;
  adjusting = true;
}