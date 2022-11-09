#include <Arduino.h>
#include "Potentiometer.hpp"
#include "MotorPotentiometer.hpp"
#include "Monitor.hpp"
#include <vector>

std::vector<MotorPotentiometer> sliders;
std::vector<Potentiometer> pots;

void setup()
{

  pinMode(SELECT_PIN_A, OUTPUT);
  pinMode(SELECT_PIN_B, OUTPUT);
  pinMode(SELECT_PIN_C, OUTPUT);

  delay(2000);

  sliders.push_back(MotorPotentiometer(0, 12, 1014));
  sliders.push_back(MotorPotentiometer(1, 10, 1013));
  sliders.push_back(MotorPotentiometer(2, 12, 1014));
  sliders.push_back(MotorPotentiometer(3, 13, 1015));
  sliders.push_back(MotorPotentiometer(4, 10, 1014));

  pots.push_back(Potentiometer(5));
  pots.push_back(Potentiometer(6));
  pots.push_back(Potentiometer(7));
  pots.push_back(Potentiometer(8));
  pots.push_back(Potentiometer(9));
  pots.push_back(Potentiometer(10));
  pots.push_back(Potentiometer(11));
  pots.push_back(Potentiometer(12));
  pots.push_back(Potentiometer(13));
  pots.push_back(Potentiometer(14));
  pots.push_back(Potentiometer(15));
}

void loop()
{
  std::stringstream ss;
  for (auto pot : sliders)
  {
    pot.read();
    ss << pot.getReading() << " ";
  }

  for (auto pot : pots)
  {
    pot.read();
    ss << pot.getReading() << " ";
  }

  monitor.print(ss);
}