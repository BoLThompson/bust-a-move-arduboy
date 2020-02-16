#ifndef ENTITIES_H
#define ENTITIES_H

#include "global.h"

#define ENTITY_MAX 20

struct Entity {
  void (*funcptr)(uint8_t index);  //a pointer to a public goddamned function being run by the global instance, argument index is the slot that this entity occupies
};

extern struct Entity* entities[ENTITY_MAX];

namespace Entities {
  void step();
  void init();
  uint8_t createMarble(Pos, uint8_t, MarbleType);
};

#endif