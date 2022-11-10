#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "Arduino.h"

// ***** 7-segment display *****
//   ---------    ---------
//   |   B   |    |   B   |
//  C|       |A  C|       |A
//   |---E---|    |---E---|
//  G|       |D  G|       |D
//   |   F   |    |   F   |
//   ---------    ---------
#define COMMON_CATHODE_1 24
#define COMMON_CATHODE_2 25
#define SEGMENT_A 26
#define SEGMENT_B 27
#define SEGMENT_C 28
#define SEGMENT_D 29
#define SEGMENT_E 30
#define SEGMENT_F 31
#define SEGMENT_G 32

class Display
{
private:
  const int segs[7] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G};
  const byte numbers[10] = {0b1101111, 0b0001001, 0b1110011, 0b0111011, 0b0011101, 0b0111110, 0b1111110, 0b0001011, 0b1111111, 0b0111111};

public:
  void show(int number);
};

#endif /* DISPLAY_HPP_ */