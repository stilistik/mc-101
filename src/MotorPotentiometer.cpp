#include "Arduino.h"
#include "MotorPotentiometer.hpp"

MotorPotentiometer::MotorPotentiometer(unsigned int index) : Potentiometer(index)
{
  this->index = index;
}

void MotorPotentiometer::read()
{
  Potentiometer::read();
}