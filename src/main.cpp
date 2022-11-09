#include <Arduino.h>
#include "Potentiometer.hpp"
#include "MotorPotentiometer.hpp"
#include "MasterController.hpp"
#include "Monitor.hpp"
#include <vector>

Monitor monitor = Monitor(50);
std::vector<Potentiometer> pots;

void setup()
{
  MasterController master = MasterController();

  pinMode(SELECT_PIN_A, OUTPUT);
  pinMode(SELECT_PIN_B, OUTPUT);
  pinMode(SELECT_PIN_C, OUTPUT);

  pots.push_back(Potentiometer(0));
  pots.push_back(Potentiometer(1));
  pots.push_back(Potentiometer(2));
  pots.push_back(Potentiometer(3));
  pots.push_back(Potentiometer(4));
  pots.push_back(Potentiometer(5));
  pots.push_back(Potentiometer(6));
  pots.push_back(Potentiometer(7));
  pots.push_back(Potentiometer(8));
  pots.push_back(Potentiometer(9));
}

void loop()
{
  std::stringstream ss;
  for (auto pot : pots)
  {
    pot.read();
    ss << pot.reading << " ";
  }

  monitor.print(ss);
}