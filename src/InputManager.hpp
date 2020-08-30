#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#define MAX_CHANNEL_COUNT 10
#define POT_COUNT 16

#include <vector>
#include <map>
#include "Bounce2.h"
#include "Arduino.h"

class InputManager
{
private:
  const int multiplexer_pin_1 = A19;
  const int multiplexer_pin_2 = A18;
  const int multiplexer_pin_3 = A17;

  const int select_pin_A = 35;
  const int select_pin_B = 34;
  const int select_pin_C = 33;

  int bit1;
  int bit2;
  int bit3;

  std::vector<int> potValues = std::vector<int>(POT_COUNT, 0);     // the values of the physical potentiometer controls that are read every cycle
  std::vector<int> prevPotValues = std::vector<int>(POT_COUNT, 0); // the old potentiometer values for comparison

  // used to normalize slider pot value range to [0, 1023]
  std::map<std::string, int> sliderFromInterval = {{"min", 12}, {"max", 1012}};

  // used to intex the pots in a meaningful order
  std::vector<int> potIndices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 14, 13, 10, 15, 12, 11};

  int mapSliderValue(int value);
  int getPotIndexFromCounter(int ctr);

public:
  InputManager();
  void update();
  std::vector<int> &getPotValues();
};

#endif /* INPUTMANAGER_HPP_ */