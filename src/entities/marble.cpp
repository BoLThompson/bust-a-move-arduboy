#include "entities/marble.h"
#include "assets.h"

#define MARBLESPEED 3

void marbleStep(uint8_t index) {
  Marble *me = (Marble *) entities[index]; //FIXME this seems dangerous

  if (!me->waiting) {
    me->pos.x+=(MARBLESPEED*sin(me->aim*PI/180))*256;
    me->pos.y+=(MARBLESPEED*cos(me->aim*PI/180))*256;

    if (((me->pos.y)>>8 <= 7)
    or ((me->pos.y)>>8 >= (64-7))) {
      me->pos.y = max(me->pos.y>>8,7)<<8;
      me->pos.y = min(me->pos.y>>8,(64-7))<<8;
      me->aim = (180-me->aim);
    }
  }

  sprites.drawExternalMask((me->pos.x>>8)-4, (me->pos.y>>8)-4, marbles, marbleMask+2, me->type, 0);

  // if ((me->dir&LEFT) != 0) {
  //   me->pos.x-=5;
  // }
  // else if ((me->dir&RIGHT) != 0) {
  //   me->pos.x+=5;
  // }

  // if ((me->dir&UP) != 0) {
  //   me->pos.y-=5;
  // }
  // else if ((me->dir&DOWN) != 0) {
  //   me->pos.y+=5;
  // }

  // if ((me->pos.x > Game::cameraX+SCREEN_WIDTH) 
  // || (me->pos.x < Game::cameraX)
  // || (me->pos.y < Game::cameraY)
  // || (me->pos.y > Game::cameraY+SCREEN_HEIGHT)) {
  //   entities[index] = NULL;
  //   delete me;
  // }
}

void marbleFire(uint8_t index, uint8_t aim) {
  Marble *me = (Marble *) entities[index];

  me->waiting = false;
  me->aim = aim;
}

void marbleMove(uint8_t index, Pos pos) {
  Marble *me = (Marble *) entities[index];

  me->pos = pos;
}