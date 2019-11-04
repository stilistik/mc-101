#include <Arduino.h>
#include "ChannelManager.hpp"
#include "Monitor.hpp"

ChannelManager *chmgr;
Monitor *monitor;

void setup()
{
  chmgr = new ChannelManager();
  monitor = new Monitor(200);
}

void loop()
{
  chmgr->update();
  monitor->print("monitor");
}