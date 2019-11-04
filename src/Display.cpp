#include "Display.hpp"
#include "Arduino.h"

Display::Display()
{
  pinMode(common_cathode_1, OUTPUT);
  pinMode(common_cathode_2, OUTPUT);
  pinMode(segment_a, OUTPUT);
  pinMode(segment_b, OUTPUT);
  pinMode(segment_c, OUTPUT);
  pinMode(segment_d, OUTPUT);
  pinMode(segment_e, OUTPUT);
  pinMode(segment_f, OUTPUT);
  pinMode(segment_g, OUTPUT);  
}

void Display::show(int number)
{
  int digit1 = (int)(number / 10);
  int digit2 = (int)(number % 10);

  digitalWrite(23, HIGH);

  // first digit
  digitalWrite(common_cathode_1, LOW);
  digitalWrite(common_cathode_2, HIGH);
  for (int i = 0; i < 7; i++)
  {
    int bit = bitRead(numbers[digit1], i);
    digitalWrite(segs[i], bit);
  }
  delay(1);

  // second digit
  digitalWrite(common_cathode_1, HIGH);
  digitalWrite(common_cathode_2, LOW);
  for (int i = 0; i < 7; i++)
  {
    int bit = bitRead(numbers[digit2], i);
    digitalWrite(segs[i], bit);
  }
  delay(1);
}