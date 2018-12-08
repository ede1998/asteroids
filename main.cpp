#include <SDL2/SDL.h>
#include <iostream>
#include "SDL_opengl.h"
#include "GL-Window.h"
#include "AS-spaceship.h"
#include <ctime>
#include <unistd.h>

#define AS_WIN_MAX_X 800
#define AS_WIN_MAX_Y 600
using std::cout;
using std::endl;

spaceship * ship;

void processMouseInput(bool mbleft, bool mbright, int x, int y);


int main(int argc,char ** argv)
{
 (void) argc;
 (void) argv;

  timespec currenttime;
  GL_window * game_out = new GL_window(800, 600, processMouseInput);
  game_out->create(AS_MAP_LEFT, AS_MAP_RIGHT, AS_MAP_BOTTOM, AS_MAP_TOP);
  game_out->setCaption("Asteroids");
  ship = new spaceship(0,0,0.);
  clock_gettime(CLOCK_MONOTONIC, &currenttime);
  while (1)
  {
    double ms = (double) currenttime.tv_nsec;
    clock_gettime(CLOCK_MONOTONIC, &currenttime);
    ms = ((double) currenttime.tv_nsec - ms) / 1000000;
    if (!game_out->check_msgs()) break;
    ms = 16;
    ship->calcNewPosition(ms);
    game_out->clear_window();
    ship->renderSpaceship();
    ship->renderProjectiles();
    game_out->refresh_window();
  }
  return 0;
}


void processMouseInput(bool mbleft, bool mbright, int x, int y)
{
  double n = (double) x / AS_WIN_MAX_X, m = (double) y / AS_WIN_MAX_Y;
  ship->rotate(n,m);
  std::cerr << "    " << mbleft << endl;
  if (mbleft)
    ship->shoot();
  if (mbright)
    ship->boost();
}
