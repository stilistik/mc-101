#ifndef MOTORPOTENTIOMETER_HPP_
#define MOTORPOTENTIOMETER_HPP_

#include "Display.hpp"
#include "Bounce2.h"
#include "Potentiometer.hpp"

class MotorPotentiometer : public Potentiometer
{
private:
public:
  MotorPotentiometer(unsigned int index);
  void read() override;
};

#endif /* MOTORPOTENTIOMETER_HPP_ */