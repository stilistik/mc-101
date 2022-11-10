#include <Arduino.h>
#include "Potentiometer.hpp"
#include "MotorPotentiometer.hpp"
#include "MidiControl.hpp"
#include "Monitor.hpp"
#include <vector>

ChannelManager ch_mgr = ChannelManager();

MotorPotentiometer slider_pot_1 = MotorPotentiometer(0, 12, 1014);
MotorPotentiometer slider_pot_2 = MotorPotentiometer(1, 10, 1013);
MotorPotentiometer slider_pot_3 = MotorPotentiometer(2, 12, 1014);
MotorPotentiometer slider_pot_4 = MotorPotentiometer(3, 13, 1015);
MotorPotentiometer slider_pot_5 = MotorPotentiometer(4, 10, 1014);

Potentiometer rotary_pot_1 = Potentiometer(5);
Potentiometer rotary_pot_2 = Potentiometer(6);
Potentiometer rotary_pot_3 = Potentiometer(7);
Potentiometer rotary_pot_4 = Potentiometer(8);
Potentiometer rotary_pot_5 = Potentiometer(9);

Potentiometer master_pot_1 = Potentiometer(10);
Potentiometer master_pot_2 = Potentiometer(11);
Potentiometer master_pot_3 = Potentiometer(12);
Potentiometer master_pot_4 = Potentiometer(13);
Potentiometer master_pot_5 = Potentiometer(14);
Potentiometer master_pot_6 = Potentiometer(15);

std::vector<MidiControl> midi_controls;

void setup()
{
  pinMode(SELECT_PIN_A, OUTPUT);
  pinMode(SELECT_PIN_B, OUTPUT);
  pinMode(SELECT_PIN_C, OUTPUT);

  pinMode(BUTTON_PIN_1, INPUT_PULLDOWN);
  pinMode(BUTTON_PIN_2, INPUT_PULLDOWN);

  pinMode(COMMON_CATHODE_1, OUTPUT);
  pinMode(COMMON_CATHODE_2, OUTPUT);
  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);

  midi_controls.push_back(MidiControl(ch_mgr, master_pot_1, 1));
  midi_controls.push_back(MidiControl(ch_mgr, master_pot_2, 2));
  midi_controls.push_back(MidiControl(ch_mgr, master_pot_3, 3));
  midi_controls.push_back(MidiControl(ch_mgr, master_pot_4, 4));
  midi_controls.push_back(MidiControl(ch_mgr, master_pot_5, 5));
  midi_controls.push_back(MidiControl(ch_mgr, master_pot_6, 6));

  for (int c = 0; c < 10; ++c)
  {
    midi_controls.push_back(MidiControl(ch_mgr, slider_pot_1, c, 7 + c * 10 + 0));
    midi_controls.push_back(MidiControl(ch_mgr, slider_pot_2, c, 7 + c * 10 + 1));
    midi_controls.push_back(MidiControl(ch_mgr, slider_pot_3, c, 7 + c * 10 + 2));
    midi_controls.push_back(MidiControl(ch_mgr, slider_pot_4, c, 7 + c * 10 + 3));
    midi_controls.push_back(MidiControl(ch_mgr, slider_pot_5, c, 7 + c * 10 + 4));
    midi_controls.push_back(MidiControl(ch_mgr, rotary_pot_1, c, 7 + c * 10 + 5));
    midi_controls.push_back(MidiControl(ch_mgr, rotary_pot_2, c, 7 + c * 10 + 6));
    midi_controls.push_back(MidiControl(ch_mgr, rotary_pot_3, c, 7 + c * 10 + 7));
    midi_controls.push_back(MidiControl(ch_mgr, rotary_pot_4, c, 7 + c * 10 + 8));
    midi_controls.push_back(MidiControl(ch_mgr, rotary_pot_5, c, 7 + c * 10 + 9));
  }
}

void loop()
{
  ch_mgr.update();
  for (auto &ctrl : midi_controls)
  {
    ctrl.update();
  }
}