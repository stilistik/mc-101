#ifndef MIDICONTROL_HPP_
#define MIDICONTROL_HPP_

#include <memory>
#include "Potentiometer.hpp"

class MidiControl
{
private:
  std::unique_ptr<Potentiometer> pot;
  unsigned int channel;
  unsigned int value = 0;
  unsigned int remoteValue = 0;

public:
  MidiControl(unsigned int channel);
  virtual void update();
};

#endif /* MIDICONTROL_HPP_ */