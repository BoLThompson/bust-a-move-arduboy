#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "entities/marble.h"

#define GRIDWIDTH 20
#define GRIDHEIGHT 6

namespace Game {
  void init();
  void challenge();
  extern MarbleType grid [GRIDWIDTH][GRIDHEIGHT];
};

namespace Launcher {
  extern uint8_t aim;
  extern uint8_t currentMarble;
  extern uint8_t nextMarble;
};

#endif