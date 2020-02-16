#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "entities/marble.h"

namespace Game {
  void init();
  void challenge();
};

namespace Launcher {
  extern uint8_t aim;
  extern uint8_t currentMarble;
  extern uint8_t nextMarble;
};

#endif