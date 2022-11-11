#include "Arduino.h"
#include "MotorPotentiometer.hpp"
#include "Monitor.hpp"

MotorPotentiometer::MotorPotentiometer(unsigned int i, unsigned int lb, unsigned int ub, unsigned int fwd_pin, unsigned int rew_pin)
    : Potentiometer(i), lower_bound(lb), upper_bound(ub), forward_pin(fwd_pin), rewind_pin(rew_pin)
{
  sensitivity = MOTOR_POT_SENSITIVITY;
}

void MotorPotentiometer::read()
{
  int raw_reading = read_raw();
  int mapped_reading = constrain(map(raw_reading, lower_bound, upper_bound, 0, 1023), 0, 1023);

  if (get_has_changed(mapped_reading))
  {
    reading = mapped_reading;
  }
}

void MotorPotentiometer::forward()
{
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(forward_pin, LOW);
  digitalWrite(rewind_pin, HIGH);
}

void MotorPotentiometer::rewind()
{
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(forward_pin, HIGH);
  digitalWrite(rewind_pin, LOW);
}

void MotorPotentiometer::stop()
{
  digitalWrite(forward_pin, LOW);
  digitalWrite(rewind_pin, LOW);
}