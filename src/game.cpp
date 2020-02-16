#include "game.h"
#include "assets.h"

uint8_t Launcher::aim;
uint8_t Launcher::currentMarble;
uint8_t Launcher::nextMarble;

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
}

void Game::challenge() {
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

  //uhhhhh cheat and change marble types
  // if (ab.justPressed(A_BUTTON) && ((int) Launcher::next < MARBLETYPES-1)) {
  //   Launcher::next = (MarbleType) ((int)Launcher::next)+1;
  // }
  // else if (ab.justPressed(B_BUTTON) && ((int) Launcher::next > 0)) {
  //   Launcher::next = (MarbleType) ((int)Launcher::next)-1;
  // }

  //draw the launcher
  #define LAUNCHER_LENGTH 16
  ab.drawLine(5,32,5+LAUNCHER_LENGTH*sin(Launcher::aim*PI/180),32+LAUNCHER_LENGTH*cos(Launcher::aim*PI/180),WHITE);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //do entity stuff
  Entities::step();
}