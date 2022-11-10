#ifndef POTENTIOMETER_HPP_
#define POTENTIOMETER_HPP_

#include <sstream>

#define POT_SENSITIVITY 5
#define SELECT_PIN_A 35
#define SELECT_PIN_B 34
#define SELECT_PIN_C 33
#define MULTIPLEXER_PIN_1 A19
#define MULTIPLEXER_PIN_2 A18
#define MULTIPLEXER_PIN_3 A17

class Potentiometer
{
protected:
  unsigned int index = 0;
  int reading = 0;
  int prev_reading = 0;
  int raw_reading = 0;
  int bit1;
  int bit2;
  int bit3;

  bool locked = false;
  bool get_has_changed(unsigned int value);
  void print_changes();

public:
  Potentiometer(unsigned int index);
  virtual void read();
  int get_reading();
};

#endif /* POTENTIOMETER_HPP_ */