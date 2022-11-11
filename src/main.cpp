#include <Arduino.h>
#include "Potentiometer.hpp"
#include "MotorPotentiometer.hpp"
#include "MidiControl.hpp"
#include "MotorMidiControl.hpp"
#include "Monitor.hpp"
#include <vector>
#include <map>

ChannelManager ch_mgr = ChannelManager();

std::vector<MotorPotentiometer> slider_pots;
std::vector<Potentiometer> rotary_pots;
std::vector<Potentiometer> master_pots;

std::map<unsigned int, MidiControl> midi_controls;
std::map<unsigned int, MotorMidiControl> motor_midi_controls;

void setup_teensy()
{
  // multiplexer
  pinMode(SELECT_PIN_A, OUTPUT);
  pinMode(SELECT_PIN_B, OUTPUT);
  pinMode(SELECT_PIN_C, OUTPUT);

  // channel buttons
  pinMode(BUTTON_PIN_1, INPUT_PULLDOWN);
  pinMode(BUTTON_PIN_2, INPUT_PULLDOWN);

  // display
  pinMode(COMMON_CATHODE_1, OUTPUT);
  pinMode(COMMON_CATHODE_2, OUTPUT);
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);

  // motors
  pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_FORWARD_PIN_1, OUTPUT);
  pinMode(MOTOR_REWIND_PIN_1, OUTPUT);
  pinMode(MOTOR_FORWARD_PIN_2, OUTPUT);
  pinMode(MOTOR_REWIND_PIN_2, OUTPUT);
  pinMode(MOTOR_FORWARD_PIN_3, OUTPUT);
  pinMode(MOTOR_REWIND_PIN_3, OUTPUT);
  pinMode(MOTOR_FORWARD_PIN_4, OUTPUT);
  pinMode(MOTOR_REWIND_PIN_4, OUTPUT);
  pinMode(MOTOR_FORWARD_PIN_5, OUTPUT);
  pinMode(MOTOR_REWIND_PIN_5, OUTPUT);
}

void setup_potentiometers()
{
  slider_pots.push_back(MotorPotentiometer(0, 12, 1014, MOTOR_FORWARD_PIN_1, MOTOR_REWIND_PIN_1));
  slider_pots.push_back(MotorPotentiometer(1, 10, 1013, MOTOR_FORWARD_PIN_2, MOTOR_REWIND_PIN_2));
  slider_pots.push_back(MotorPotentiometer(2, 12, 1014, MOTOR_FORWARD_PIN_3, MOTOR_REWIND_PIN_3));
  slider_pots.push_back(MotorPotentiometer(3, 13, 1015, MOTOR_FORWARD_PIN_4, MOTOR_REWIND_PIN_4));
  slider_pots.push_back(MotorPotentiometer(4, 10, 1014, MOTOR_FORWARD_PIN_5, MOTOR_REWIND_PIN_5));

  rotary_pots.push_back(Potentiometer(5));
  rotary_pots.push_back(Potentiometer(6));
  rotary_pots.push_back(Potentiometer(7));
  rotary_pots.push_back(Potentiometer(8));
  rotary_pots.push_back(Potentiometer(9));

  master_pots.push_back(Potentiometer(10));
  master_pots.push_back(Potentiometer(11));
  master_pots.push_back(Potentiometer(12));
  master_pots.push_back(Potentiometer(13));
  master_pots.push_back(Potentiometer(14));
  master_pots.push_back(Potentiometer(15));
}

void setup_midi_controls()
{
  for (unsigned int midi_channel = 0; midi_channel < master_pots.size(); ++midi_channel)
  {
    midi_controls.insert({midi_channel, MidiControl(ch_mgr, master_pots[midi_channel], midi_channel)});
  }

  for (unsigned int ctrl_ch = 0; ctrl_ch < CHANNELS; ++ctrl_ch)
  {
    for (unsigned int i = 0; i < slider_pots.size(); ++i)
    {
      unsigned int midi_channel = master_pots.size() + ctrl_ch * CHANNELS + i;
      motor_midi_controls.insert({midi_channel, MotorMidiControl(ch_mgr, slider_pots[i], ctrl_ch, midi_channel)});
      ch_mgr.register_listener(&motor_midi_controls.at(midi_channel));
    }

    for (unsigned int i = 0; i < rotary_pots.size(); ++i)
    {
      unsigned int midi_channel = master_pots.size() + ctrl_ch * CHANNELS + slider_pots.size() + i;
      midi_controls.insert({midi_channel, MidiControl(ch_mgr, rotary_pots[i], ctrl_ch, midi_channel)});
    }
  }
}

void on_control_change(byte channel, byte control, byte value)
{
  if (midi_controls.count(control) > 0)
  {
    midi_controls.at(control).set_remote_value(value);
  }

  if (motor_midi_controls.count(control) > 0)
  {
    motor_midi_controls.at(control).set_remote_value(value);
  }
}

void setup()
{
  setup_teensy();
  setup_potentiometers();
  setup_midi_controls();
  usbMIDI.setHandleControlChange(on_control_change);
}

void loop()
{
  while (usbMIDI.read())
  {
  }

  ch_mgr.update();
  for (auto &entry : midi_controls)
  {
    entry.second.update();
  }
  for (auto &entry : motor_midi_controls)
  {
    entry.second.update();
  }
}