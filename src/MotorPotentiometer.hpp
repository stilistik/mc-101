#ifndef MOTORPOTENTIOMETER_HPP_
#define MOTORPOTENTIOMETER_HPP_

#include "Potentiometer.hpp"

class MotorPotentiometer : public Potentiometer
{
private:
  unsigned int lowerBound;
  unsigned int upperBound;

public:
  MotorPotentiometer(unsigned int index, unsigned int boundsLow, unsigned int boundsHigh);
  void read() override;
};

#endif /* MOTORPOTENTIOMETER_HPP_ */