/*                                              *
 * file: AS-spaceship.cpp                       *
 * author: Erik Hennig                          *
 * date: 25.12.2016                             *
 * abstract: implementation of spaceship class, *
 *          used for player controlled unit     */

#include "AS-spaceship.h"
#include "SDL_opengl.h"
#include <math.h>
#include <iostream>
#include <cmath>


#define time 10
spaceship::spaceship(double x, double y, double rot) : 
        _positionx ( x   ),
        _positiony ( y   ),
        _speedx    ( 0.  ),
        _speedy    ( 0.  ),
        _rotation  ( rot ),
        _bullet_cooldown ( 0 )
{
  _projectiles = new ordered_list();
}

spaceship::~spaceship()
{

}

void spaceship::renderSpaceship()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(_rotation * 180 / PI, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(AS_SPACESHIP_X1, AS_SPACESHIP_Y1, 0);
    glColor3f(1, 1, 1);
    glVertex3f(AS_SPACESHIP_X2, AS_SPACESHIP_Y2, 0);
    glVertex3f(AS_SPACESHIP_X3, AS_SPACESHIP_Y3, 0);
  glEnd();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(_positionx, _positiony, 0);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f((x1-.5)*80, -(y1-.5)*60, 0);
  glEnd();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

void spaceship::renderProjectiles()
{
  int max = _projectiles->getlength();
  //std::cerr << max << std::endl;
  for (int i = 0; i < max; i++)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    bullet * b = (bullet *) _projectiles->getElement(i);
    glTranslatef(b->posx, b->posy, 0);
    glRotatef(b->rot * 180 / PI, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glBegin(GL_LINES);
      glColor3f(1,1,0.5);
      glVertex3f(-1,0, 0);
      glVertex3f(1,0, 0);
    glEnd();
  }
}

void spaceship::shoot()
{
  std::cout << "links" << std::endl;
  if (_bullet_cooldown <= 0)
  {
    _bullet_cooldown = AS_SPACESHIP_BULLET_COOLDOWN;
    bullet * b = new bullet;
    b->posx = _positionx;
    b->posy = _positiony;
    b->rot = _rotation;
    _projectiles->append(b);
  }
}

void spaceship::boost()
{
  std::cout << "rechts" << std::endl;
  _speedx = AS_SPACESHIP_ACC;
}

void spaceship::calcNewPosition(double tp)
{
  _speedx -= tp / 380 * AS_SPACESHIP_ACC;
  _speedy -= tp / 380 * AS_SPACESHIP_ACC;
//  std::cerr << _bullet_cooldown << std::endl;
  if (_speedx < 0) _speedx = 0;
  if (_speedy < 0) _speedy = 0;
  _positionx += _speedx * tp * cos(_rotation);
  _positiony += _speedy * tp * sin(_rotation);
  if (_bullet_cooldown > 0) _bullet_cooldown -= tp;
  calcBulletPos(tp);
}

void spaceship::calcBulletPos(double tp)
{
  int max = _projectiles->getlength();
  for (int i = 0; i < max; i++)
  {
    bullet * b = (bullet *) _projectiles->getElement(i);
    b->posx += AS_BULLET_SPEED * tp * cos(b->rot);
    b->posy += AS_BULLET_SPEED * tp * sin(b->rot);
  }
}

void spaceship::rotate(double x, double y)
{
  //TODO: ADD max rot speed

  x1 = x;
  y1 = y;
  //90 degree
  if (x == _positionx / 80 + .5) return;
  double new_rot = atan((double) AS_MAP_XYRATIO * std::abs(y -.5)  / std::abs(x -.5));
  //std::cerr << atan((double) std::abs(y + _positiony / (60) -.5)  / std::abs(x- _positionx/80-.5)) *180 / PI << std::endl;  
  if (x-.5 < 0) new_rot = PI - new_rot;
  if (y-.5> 0) new_rot = 2 * PI - new_rot;
  _rotation = new_rot;
}


