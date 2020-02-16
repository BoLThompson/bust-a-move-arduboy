#include "game.h"
#include "assets.h"

uint8_t Launcher::aim;
uint8_t Launcher::currentMarble;
uint8_t Launcher::nextMarble;
MarbleType Game::grid [GRIDWIDTH][GRIDHEIGHT];

namespace {
  const Pos firingPos = {
    5<<8,
    32<<8
  };
  const Pos previewPos = {
    5<<8,
    5<<8
  };
};

void Game::init() {
  Launcher::aim = 90;  //init launcher
  Launcher::nextMarble = Entities::createMarble(previewPos, Launcher::aim, random(MARBLETYPES));
  Launcher::currentMarble = Entities::createMarble(firingPos, Launcher::aim, random(MARBLETYPES));
  //init grid
  for (uint8_t gx = 0; gx < GRIDWIDTH; gx++) {
    for (uint8_t gy = 0; gy < GRIDHEIGHT; gy++) {
      Game::grid[gx][gy] = None;
    }
  }
  Game::grid[0][0] = Wings;
  Game::grid[5][5] = Home;
}

void Game::challenge() {
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  #define startX SCREEN_WIDTH-5
  #define startY 9

  uint8_t gx;
  uint8_t gy;

  for (gx = 0; gx < GRIDWIDTH; gx++) {
    for (gy = 0; gy < GRIDHEIGHT; gy++) {
      //grid is 6px by 8px, alternating shift 4px down
      if ((int) Game::grid[gx][gy] != None) 
        sprites.drawExternalMask((startX-(gx*6))-4, ((startY+(gy*8))-4)+(4*(gx&1)), marbles, marbleMask+2, Game::grid[gx][gy], 0);
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //adjust launcher
  if (ab.pressed(DOWN_BUTTON) && (Launcher::aim>10)) Launcher::aim--;
  else if (ab.pressed(UP_BUTTON) && (Launcher::aim<170)) Launcher::aim++;

  if (ab.justPressed(RIGHT_BUTTON)) {
    marbleFire(Launcher::currentMarble, Launcher::aim);
    Launcher::currentMarble = Launcher::nextMarble;
    marbleMove(Launcher::currentMarble, firingPos);
    Launcher::nextMarble = Entities::createMarble(previewPos, Launcher::aim, random(MARBLETYPES));
  }

  //draw the launcher
  #define LAUNCHER_LENGTH 16
  ab.drawLine(5,32,5+LAUNCHER_LENGTH*sin(Launcher::aim*PI/180),32+LAUNCHER_LENGTH*cos(Launcher::aim*PI/180),WHITE);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //do entity stuff
  Entities::step();
}