#include "MasterController.hpp"

MasterController::MasterController()
{
  monitor = std::make_unique<Monitor>(50);
  channelManager = std::make_unique<ChannelManager>(this);
  inputManager = std::make_unique<InputManager>(this);
  midiManager = std::make_unique<MidiManager>(this);
  // motorManager = std::make_unique<MotorManager>(this);
}

void MasterController::update()
{
  channelManager->update();
  inputManager->update();
  midiManager->update();
}