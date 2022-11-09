#include "MidiControl.hpp"

MidiControl::MidiControl(unsigned int ch)
{
  channel = ch;
}

void MidiControl::update()
{
  pot->read();
  
}