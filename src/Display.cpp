#include "Display.hpp"
#include "Arduino.h"

void Display::show(int number)
{
  int digit1 = (int)(number / 10);
  int digit2 = (int)(number % 10);

  digitalWrite(23, HIGH);

  // first digit
  digitalWrite(COMMON_CATHODE_1, LOW);
  digitalWrite(COMMON_CATHODE_2, HIGH);
  for (int i = 0; i < 7; i++)
  {
    int bit = bitRead(numbers[digit1], i);
    digitalWrite(segs[i], bit);
  }
  delay(1);

  // second digit
  digitalWrite(COMMON_CATHODE_1, HIGH);
  digitalWrite(COMMON_CATHODE_2, LOW);
  for (int i = 0; i < 7; i++)
  {
    int bit = bitRead(numbers[digit2], i);
    digitalWrite(segs[i], bit);
  }
  delay(1);
}