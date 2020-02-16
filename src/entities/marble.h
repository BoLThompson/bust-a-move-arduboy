#ifndef MARBLE_H
#define MARBLE_H

#include "global.h"
#include "entities.h"

struct Marble: public Entity {
  Pos pos;
  uint8_t aim;
  MarbleType type;
  bool waiting;
};

void marbleStep(uint8_t index);
void marbleFire(uint8_t index, uint8_t aim);
void marbleMove(uint8_t index, Pos pos);

#endif