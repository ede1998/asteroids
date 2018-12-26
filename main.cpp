#include <SDL2/SDL.h>
#include <iostream>
#include "GL-Window.h"
#include "AS-spaceship.h"
#include <ctime>
#include <unistd.h>

#define AS_WIN_MAX_X 800
#define AS_WIN_MAX_Y 600
using std::cout;
using std::endl;

Spaceship *shipP;

uint32_t NOW;

void processMouseInput(bool mbleft, bool mbright, int x, int y);


int main(int argc,char ** argv)
{
 (void) argc;
 (void) argv;

  GL_window game_out = GL_window(800, 600, processMouseInput);
  game_out.create(AS_MAP_LEFT, AS_MAP_RIGHT, AS_MAP_BOTTOM, AS_MAP_TOP);
  game_out.setCaption("Asteroids");
  Spaceship ship(0,0,0.);
  shipP = &ship;
  NOW = SDL_GetTicks();
  while (1)
  {
    const uint32_t last = NOW;
    NOW = SDL_GetTicks();
    if (!game_out.check_msgs()) break;
    double ms = NOW - last;
    ms = 16;
    ship.calcNewPosition(ms);
    game_out.clear_window();
    ship.renderSpaceship();
    ship.renderProjectiles();
    game_out.refresh_window();
  }
  return 0;
}


void processMouseInput(bool mbleft, bool mbright, int x, int y)
{
  double n = (double) x / AS_WIN_MAX_X, m = (double) y / AS_WIN_MAX_Y;
  double posx = AS_MAP_LEFT + n * AS_MAP_WIDTH;
  double posy = AS_MAP_BOTTOM + (1-m) * AS_MAP_HEIGHT;
  shipP->rotate(posx,posy);
  if (mbleft)
    shipP->shoot();
  if (mbright)
    shipP->boost();
}
