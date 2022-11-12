#include "MotorMidiControl.hpp"
#include "Monitor.hpp"

MotorMidiControl::MotorMidiControl(ChannelManager &ch_mgr, MotorPotentiometer &pot, unsigned int cch, unsigned int mch) : MidiControl::MidiControl(ch_mgr, pot, cch, mch), pot(pot) {}

void MotorMidiControl::update()
{
  if (!is_active_channel())
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
        set_adjusting(false);
        ctr = 0;
        tmp_target = raw_midi_value;
      }
    }
  }
  else
  {
    if (tmp_target == -1 || abs(tmp_target - raw_midi_value) > 2)
    {
      MidiControl::update();
      tmp_target = -1;
    }
  }
}

void MotorMidiControl::on_channel_change(int channel)
{
  if (channel == ctrl_channel)
  {
    set_adjusting(true);
  }
  else
  {
    set_adjusting(false);
  }
}

void MotorMidiControl::set_remote_value(unsigned int value)
{
  remote_midi_value = value;
  set_adjusting(true);
}

void MotorMidiControl::set_adjusting(bool value)
{
  adjusting = value;
  ch_mgr.set_is_changing(adjusting, midi_channel);
}