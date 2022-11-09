#include "Arduino.h"
#include <stdlib.h>
#include <map>
#include "MasterController.hpp"
#include "InputManager.hpp"

InputManager::InputManager(MasterController *master)
{
  this->master = master;

  this->potValues = std::vector<int>(totalPots, 0);
  this->prevPotValues = std::vector<int>(totalPots, 0);

  // multiplexer
  pinMode(select_pin_A, OUTPUT);
  pinMode(select_pin_B, OUTPUT);
  pinMode(select_pin_C, OUTPUT);
};

void InputManager::update()
{
  for (unsigned int ctr = 0; ctr < potValues.size(); ++ctr)
  {
    // convert ctr to bit
    bit1 = bitRead((ctr % 8), 0);
    bit2 = bitRead((ctr % 8), 1);
    bit3 = bitRead((ctr % 8), 2);

    // set multiplexer select
    digitalWrite(select_pin_A, bit1);
    digitalWrite(select_pin_B, bit2);
    digitalWrite(select_pin_C, bit3);

    int potIndex = this->getPotIndexFromCounter(ctr);

    // choose multiplexer to read from based on pot ID
    if (ctr < 5)
    {
      int readValue = analogRead(multiplexer_pin_1);
      potValues[potIndex] = this->mapSliderValue(readValue);
    }
    else if (ctr < 8)
    {
      // read from first multiplexer
      potValues[potIndex] = analogRead(multiplexer_pin_1);
    }
    else
    {
      // read from second multiplexer
      potValues[potIndex] = analogRead(multiplexer_pin_2);
    }
  }
}

std::vector<int> &InputManager::getPotValues()
{
  return potValues;
}

std::map<int, int> InputManager::getChangedPotValues()
{
  std::map<int, int> changes;
  for (unsigned int ctr = 0; ctr < potValues.size(); ++ctr)
  {
    if (abs(potValues[ctr] - prevPotValues[ctr]) > sensitivity)
    {
      changes.insert({ctr, potValues[ctr]});
      prevPotValues[ctr] = potValues[ctr];
    }
  }
  return changes;
}

int InputManager::mapSliderValue(int value)
{
  int mappedValue = map(value, this->sliderCalibration[0], this->sliderCalibration[1], 0, 1023);

  // clamp to range 0, 1023
  if (mappedValue < 0)
    mappedValue = 0;
  if (mappedValue > 1023)
    mappedValue = 1023;

  return mappedValue;
}

int InputManager::getPotIndexFromCounter(int ctr)
{
  return this->potIndices[ctr];
}
