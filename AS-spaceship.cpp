/*                                              *
 * file: AS-Spaceship.cpp                       *
 * author: Erik Hennig                          *
 * date: 25.12.2016                             *
 * abstract: implementation of Spaceship class, *
 *          used for player controlled unit     */

#include "AS-Spaceship.h"
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <cmath>

Spaceship::Spaceship(double x, double y, double rot) : 
        _positionx ( x   ),
        _positiony ( y   ),
        _speedx    ( 0.  ),
        _speedy    ( 0.  ),
        _rotation  ( rot ),
        _bullet_cooldown ( 0 )
{
}

Spaceship::~Spaceship()
{

}

void Spaceship::renderSpaceship()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(_positionx, _positiony, 0);
  glRotatef(_rotation * 180 / M_PI, 0, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(VERTICES_X[0], VERTICES_Y[0], 0);
    glColor3f(1, 1, 1);
    glVertex3f(VERTICES_X[1], VERTICES_Y[1], 0);
    glVertex3f(VERTICES_X[2], VERTICES_Y[2], 0);
  glEnd();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glPushMatrix();
  //glLoadIdentity();
  //glMatrixMode(GL_PROJECTION);
  //glBegin(GL_LINES);
  //  glColor3f(1, 0, 0);
  //  glVertex3f(0, 0, 0);
  //  glVertex3f((x1-.5)*80, -(y1-.5)*60, 0);
  //glEnd();
  //glMatrixMode(GL_MODELVIEW);
  //glPopMatrix();
}

void Spaceship::renderProjectiles()
{
  for (auto iter = _projectiles.begin(); iter != _projectiles.end(); ++iter)
  {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(iter->_positionx, iter->_positiony, 0);
    glRotatef(iter->_rotation * 180 / M_PI, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glBegin(GL_LINES);
      glColor3f(1,1,0.5);
      glVertex3f(-1,0, 0);
      glVertex3f(1,0, 0);
    glEnd();
  }
}

void Spaceship::shoot()
{
  if (_bullet_cooldown <= 0)
  {
    _bullet_cooldown = BULLET_COOLDOWN;
    _projectiles.emplace_back(_positionx, _positiony, _rotation);
  }
}

void Spaceship::boost()
{
  _speedx = ACCELERATION * std::abs(std::cos(_rotation));
  _speedy = ACCELERATION * std::abs(std::sin(_rotation));
}

void Spaceship::calcNewPosition(double tp)
{
  _speedx -= tp / 380 * ACCELERATION;
  _speedy -= tp / 380 * ACCELERATION;
//  std::cerr << _bullet_cooldown << std::endl;
  if (_speedx < 0) _speedx = 0;
  if (_speedy < 0) _speedy = 0;
  _positionx += _speedx * tp * cos(_rotation);
  _positiony += _speedy * tp * sin(_rotation);
  if (_bullet_cooldown > 0) _bullet_cooldown -= tp;
  calcBulletPos(tp);
}

void Spaceship::calcBulletPos(double tp)
{
  for (auto iter = _projectiles.begin(); iter != _projectiles.end(); ++iter)
  {
    iter->_positionx += Bullet::SPEED * tp * std::cos(iter->_rotation);
    iter->_positiony += Bullet::SPEED * tp * std::sin(iter->_rotation);
  }
}

void Spaceship::rotate(double x, double y)
{
  //TODO: ADD max rot speed
  // x,y should be position in world

  double deltaX = x - _positionx;
  double deltaY = y - _positiony;

  _rotation = std::atan2(deltaY, deltaX);
}


