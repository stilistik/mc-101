#ifndef MOTORPOTENTIOMETER_HPP_
#define MOTORPOTENTIOMETER_HPP_

#include "Potentiometer.hpp"

#define MOTOR_POT_SENSITIVITY 10
#define MOTOR_ENABLE_PIN 0
#define MOTOR_FORWARD_PIN_1 2
#define MOTOR_REWIND_PIN_1 1
#define MOTOR_FORWARD_PIN_2 4
#define MOTOR_REWIND_PIN_2 3
#define MOTOR_FORWARD_PIN_3 6
#define MOTOR_REWIND_PIN_3 5
#define MOTOR_FORWARD_PIN_4 8
#define MOTOR_REWIND_PIN_4 7
#define MOTOR_FORWARD_PIN_5 10
#define MOTOR_REWIND_PIN_5 9

class MotorPotentiometer : public Potentiometer
{
private:
  unsigned int lower_bound;
  unsigned int upper_bound;
  unsigned int forward_pin;
  unsigned int rewind_pin;

public:
  MotorPotentiometer(unsigned int index, unsigned int lb, unsigned int ub, unsigned int fwd_pin, unsigned int rew_pin);
  void read() override;
  void forward();
  void rewind();
  void stop();
};

#endif /* MOTORPOTENTIOMETER_HPP_ */