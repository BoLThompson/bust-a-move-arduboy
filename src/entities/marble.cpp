#include "entities/marble.h"
#include "assets.h"
#include "game.h"

namespace {
  #define MARBLESPEED 1
  #define FIELDTOP 7
  #define FIELDBOTTOM SCREEN_HEIGHT-FIELDTOP
  #define FIELDEND SCREEN_WIDTH-FIELDTOP-7
  void marbleDraw();
};

void roundToMarbleGrid(Pos& pos, MarbleType type){
  //calculate gridX
  //round the marble's x position to the nearest gx point
  pos.x = pos.x>>8; //no subpixels
  pos.x -=3;        //grid is offset 3 pixels horizontally

  pos.x += 3;       //half way adjustment
  
  pos.x /= 6;       //round off to multiples of 6
  uint8_t gx = pos.x;
  pos.x *= 6;

  pos.x+=3;         //offset

  pos.x = pos.x<<8;

  pos.y = pos.y>>8;
  if ((gx&1)==0) pos.y += 4;
  pos.y += 5; //grid is offset 5 pixels vertically
  pos.y -= 4;
  pos.y /= 8;
  uint8_t gy = pos.y;
  pos.y *= 8;
  if ((gx&1)==0) pos.y -= 4;
  pos.y += 5;         //grid offset
  pos.y = pos.y<<8;

  gx = 20-gx;
  gy-=1;

  Game::grid[gx][gy] = type;
}

void marbleDraw(Marble *me) {
  sprites.drawExternalMask((me->pos.x>>8)-4, (me->pos.y>>8)-4, marbles, marbleMask+2, me->type, 0);
}

void marbleWait(uint8_t index) {
  Marble *me = (Marble *) entities[index]; //FIXME this seems dangerous
  marbleDraw(me);
}

void marbleStep(uint8_t index) {
  Marble *me = (Marble *) entities[index]; //FIXME this seems dangerous

  me->pos.x+=(MARBLESPEED*sin(me->aim*PI/180))*256;
  me->pos.y+=(MARBLESPEED*cos(me->aim*PI/180))*256;

  if ((((me->pos.y)>>8) <= FIELDTOP)
  or (((me->pos.y)>>8) >= (FIELDBOTTOM))) {
    me->pos.y = max(me->pos.y>>8,FIELDTOP)<<8;
    me->pos.y = min(me->pos.y>>8,(FIELDBOTTOM))<<8;
    me->aim = (180-me->aim);
  }

  marbleDraw(me);

  if (ab.justPressed(B_BUTTON)) {
    roundToMarbleGrid(me->pos, me->type);
    // me->funcptr = marbleWait;
    entities[index] = NULL;
    delete me;
  }
}

void marbleFire(uint8_t index, uint8_t aim) {
  Marble *me = (Marble *) entities[index];

  me->funcptr = marbleStep;
  me->aim = aim;
}

void marbleMove(uint8_t index, Pos pos) {
  Marble *me = (Marble *) entities[index];

  me->pos = pos;
}