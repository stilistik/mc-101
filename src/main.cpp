#include <Arduino.h>
#include "MasterController.hpp"

MasterController *controller;

void setup()
{
  controller = new MasterController();
}

void loop()
{
  controller->update();
}