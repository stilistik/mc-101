#include <Arduino.h>
#include "Potentiometer.hpp"
#include "MotorPotentiometer.hpp"
#include "MidiControl.hpp"
#include "Monitor.hpp"
#include <vector>

std::vector<MotorPotentiometer> sliders = {
    MotorPotentiometer(0, 12, 1014),
    MotorPotentiometer(1, 10, 1013),
    MotorPotentiometer(2, 12, 1014),
    MotorPotentiometer(3, 13, 1015),
    MotorPotentiometer(4, 10, 1014),
};

std::vector<Potentiometer> pots = {
    Potentiometer(5),
    Potentiometer(6),
    Potentiometer(7),
    Potentiometer(8),
    Potentiometer(9),
};

Potentiometer m_pot_1 = Potentiometer(10);
Potentiometer m_pot_2 = Potentiometer(11);
Potentiometer m_pot_3 = Potentiometer(12);
Potentiometer m_pot_4 = Potentiometer(13);
Potentiometer m_pot_5 = Potentiometer(14);
Potentiometer m_pot_6 = Potentiometer(15);

std::vector<MidiControl> masterControls = {
    MidiControl(m_pot_1, 1),
    MidiControl(m_pot_2, 2),
    MidiControl(m_pot_3, 3),
    MidiControl(m_pot_4, 4),
    MidiControl(m_pot_5, 5),
    MidiControl(m_pot_6, 6),
};

void setup()
{
  pinMode(SELECT_PIN_A, OUTPUT);
  pinMode(SELECT_PIN_B, OUTPUT);
  pinMode(SELECT_PIN_C, OUTPUT);
}

void loop()
{
  for (auto &ctrl : masterControls)
  {
    ctrl.update();
  }
}