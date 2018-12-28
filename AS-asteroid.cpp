/*                                                     *
 * file: AS-asteroid.cpp                               *
 * author: Erik Hennig                                 *
 * date: 27.12.2018                                    *
 * abstract: represents an asteroid                    */

#include "AS-asteroid.h"

#include <SDL2/SDL_opengl.h>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "AS-map.h"

Asteroid::Asteroid(double posx, double posy, double speedx, double speedy, int mass)
	:  _positionx ( posx ),
	   _positiony ( posy ),
	   _speedx ( speedx ),
	   _speedy ( speedy ),
	   _mass ( mass )
{
}

Asteroid::~Asteroid()
{
}

const Shape& Asteroid::getShape() const
{
  return _shape;
}

void Asteroid::render() const
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(_positionx, _positiony, 0);
  // glRotatef(_rotation * 180 / M_PI, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.1);
    std::for_each(std::begin(_corners), std::end(_corners),
		    [](const Point& p) {
		      glVertex3f(p.x, p.y, 1);
		    });
  glEnd();
}

void Asteroid::process(double tp)
{
  const double delta_x = _speedx * tp;
  const double delta_y = _speedy * tp;

  _positionx += delta_x;
  _positiony += delta_y;

  _shape.move(delta_x, delta_y);
}

Asteroid Asteroid::generate(int mass)
{
  double posx, posy;
  const double speed = MAX_SPEED * ((double) (std::rand() % 98) / 100 + 0.03);
  // cone with width of 120 degree
  const double angle_cone = std::rand() % 121;
  double angle = 0;
  switch (std::rand() % 4)
  {
    case 0: // spawn on top
	posx = (AS_MAP_LEFT - 3) + std::rand() % (AS_MAP_WIDTH + 6);
	posy = AS_MAP_TOP + 10;
	// angle in interval (-30;-150) degrees
	angle = -(30 + angle_cone) * M_PI / 180;
      break;
    case 1: // spawn on bottom
	posx = (AS_MAP_LEFT - 3) + std::rand() % (AS_MAP_WIDTH + 6);
	posy = AS_MAP_BOTTOM - 10;
	// angle in interval (30;150) degrees
	angle = (30 + angle_cone) * M_PI / 180;
      break;
    case 2: // spawn on left
	posx = AS_MAP_LEFT - 10;
	posy = (AS_MAP_BOTTOM - 2) + std::rand() % (AS_MAP_HEIGHT + 6);
	// angle in interval (-60;60) degrees
	angle = (-60 + angle_cone) * M_PI / 180;
      break;
    case 3: // spawn on right
	posx = AS_MAP_RIGHT + 10;
	posy = (AS_MAP_BOTTOM - 2) + std::rand() % (AS_MAP_HEIGHT + 6);
	// angle in interval (-150;150) degrees and bring it back in (-pi;pi)
	angle = -(150 + angle_cone) * M_PI / 180;
	angle = std::remainder(angle, 2*M_PI);
      break;
  }
  const double speedx = std::cos(angle) * speed;
  const double speedy = std::sin(angle) * speed;

  Asteroid a(posx,posy,speedx,speedy,mass);
  const int corners = std::rand() % 6 + 4;
  for (double angle = 0; angle < 2*M_PI; angle += 2*M_PI / corners)
  {
    //Change the radius for every vertex
    const double radius = 1 + (double) std::rand() / RAND_MAX * 3;
    
    a._corners.emplace_back(std::cos(angle) * radius, std::sin(angle) * radius);
  }
  a._shape.setCorners(a._corners);
  return a;
}
