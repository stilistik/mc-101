#ifndef MASTERCONTROLLER_HPP_
#define MASTERCONTROLLER_HPP_

#include <memory>
#include "Monitor.hpp"
#include "ChannelManager.hpp"
#include "MidiManager.hpp"
#include "InputManager.hpp"
#include "MotorManager.hpp"

class MasterController
{
public:
  std::unique_ptr<Monitor> monitor;
  std::unique_ptr<ChannelManager> channelManager;
  std::unique_ptr<MidiManager> midiManager;
  std::unique_ptr<InputManager> inputManager;
  std::unique_ptr<MotorManager> motorManager;
  
  MasterController();
  void update();
};

#endif /* MASTERCONTROLLER_HPP_ */
