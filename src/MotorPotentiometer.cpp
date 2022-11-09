#include "Arduino.h"
#include "MotorPotentiometer.hpp"

MotorPotentiometer::MotorPotentiometer(unsigned int i, unsigned int lb, unsigned int ub) : Potentiometer(i)
{
  index = i;
  lowerBound = lb;
  upperBound = ub;
}

void MotorPotentiometer::read()
{
  Potentiometer::read();
  int mappedValue = constrain(map(reading, lowerBound, upperBound, 0, 1023), 0, 1023);
  reading = mappedValue;
}