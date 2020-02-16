#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <Arduboy2.h>

#define FPS 60

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

extern Arduboy2Base ab;
extern Sprites sprites;

struct Pos {
  uint16_t x;
  uint16_t y;
};

enum MarbleType {
  White,
  Wings,
  Cloud,
  Spike,
  Waves,
  Home,
  None,
};

#define MARBLETYPES 6

#endif