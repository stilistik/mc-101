#ifndef POTENTIOMETER_HPP_
#define POTENTIOMETER_HPP_

#include <sstream>

#define POT_SENSITIVITY 8
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
  unsigned int sensitivity;
  int bit1;
  int bit2;
  int bit3;

  int reading = 0;
  int prev_reading = 0;

  bool locked = false;
  bool get_has_changed(int value);
  void print_changes();
  int read_raw();

public:
  Potentiometer(unsigned int index);
  virtual void read();
  int get_reading();
  unsigned int get_index();
};

#endif /* POTENTIOMETER_HPP_ */