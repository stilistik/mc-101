#include "Arduino.h"
#include "Potentiometer.hpp"
#include <sstream>
#include "Monitor.hpp"

Potentiometer::Potentiometer(unsigned int index)
{
  this->index = index;

  monitor.print(index);

  // convert pot index to bits
  bit1 = bitRead((index % 8), 0);
  bit2 = bitRead((index % 8), 1);
  bit3 = bitRead((index % 8), 2);
}

void Potentiometer::read()
{
  prevReading = reading;

  // set multiplexer select
  digitalWrite(SELECT_PIN_A, bit1);
  digitalWrite(SELECT_PIN_B, bit2);
  digitalWrite(SELECT_PIN_C, bit3);

  auto read_pin = index < 8 ? MULTIPLEXER_PIN_1 : MULTIPLEXER_PIN_2;

  reading = analogRead(read_pin);
}

int Potentiometer::getReading()
{
  return reading;
}

int Potentiometer::getPreviousReading()
{
  return prevReading;
}

int Potentiometer::getDifference()
{
  return reading - prevReading;
}

std::stringstream &operator<<(std::stringstream &ss, const Potentiometer &pot)
{
  ss << "Pot index:" << pot.index << " reading: " << pot.reading << " prevReading: " << pot.prevReading;
  return ss;
}