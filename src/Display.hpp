#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include "Arduino.h"

class Display
{
private:
  // ***** 7-segment display *****
  //   ---------    ---------
  //   |   B   |    |   B   |
  //  C|       |A  C|       |A
  //   |---E---|    |---E---|
  //  G|       |D  G|       |D
  //   |   F   |    |   F   |
  //   ---------    ---------

  const int common_cathode_1 = 24;
  const int common_cathode_2 = 25;
  const int segment_a = 26;
  const int segment_b = 27;
  const int segment_c = 28;
  const int segment_d = 29;
  const int segment_e = 30;
  const int segment_f = 31;
  const int segment_g = 32;

  const int segs[7] = {segment_a, segment_b, segment_c, segment_d, segment_e, segment_f, segment_g};
  const byte numbers[10] = {0b1101111, 0b0001001, 0b1110011, 0b0111011, 0b0011101, 0b0111110, 0b1111110, 0b0001011, 0b1111111, 0b0111111};

public:
  Display();
  void show(int number);
};

#endif /* DISPLAY_HPP_ */