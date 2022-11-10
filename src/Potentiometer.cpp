#include "Arduino.h"
#include "Potentiometer.hpp"
#include "Monitor.hpp"

Potentiometer::Potentiometer(unsigned int i)
{
  index = i;
  reading = 0;
  prev_reading = 0;

  // convert pot index to bits
  bit1 = bitRead((index % 8), 0);
  bit2 = bitRead((index % 8), 1);
  bit3 = bitRead((index % 8), 2);
}

void Potentiometer::read()
{
  prev_reading = reading;

  // set multiplexer select
  digitalWrite(SELECT_PIN_A, bit1);
  digitalWrite(SELECT_PIN_B, bit2);
  digitalWrite(SELECT_PIN_C, bit3);

  auto read_pin = index < 8 ? MULTIPLEXER_PIN_1 : MULTIPLEXER_PIN_2;

  unsigned int raw_reading = analogRead(read_pin);

  if (get_has_changed(raw_reading))
  {
    reading = raw_reading;
  }
}

bool Potentiometer::get_has_changed(unsigned int value)
{
  return abs(prev_reading - value) > POT_SENSITIVITY;
}

int Potentiometer::get_reading()
{
  return reading;
}

void Potentiometer::print_changes()
{
  std::stringstream ss;
  ss << "Pot " << index << " | Value: " << reading << " | Prev: " << prev_reading;
  monitor.print(ss);
}