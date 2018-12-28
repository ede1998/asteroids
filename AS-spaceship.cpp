/*                                              *
 * file: AS-Spaceship.cpp                       *
 * author: Erik Hennig                          *
 * date: 25.12.2016                             *
 * abstract: implementation of Spaceship class, *
 *          used for player controlled unit     */

#include "AS-spaceship.h"
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>

extern uint32_t NOW;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

constexpr int Spaceship::VERTICES_X[];
constexpr int Spaceship::VERTICES_Y[];

Spaceship::Spaceship(double x, double y, double rot) : 
        _positionx ( x   ),
        _positiony ( y   ),
        _speedx    ( 0.  ),
        _speedy    ( 0.  ),
        _rotation  ( rot ),
	_desired_rotation ( rot ),
	_last_boost_activation ( 0 ),
        _last_bullet_activation ( 0 )
{
  Shape::CornerList cl;
  const Point pos(x,y);
  auto make_point = [] (double x, double y) -> Point { return Point(x,y); };
  std::transform(std::begin(VERTICES_X), std::end(VERTICES_X), std::begin(VERTICES_Y), std::back_inserter(cl), make_point);
  std::transform(cl.begin(), cl.end(), cl.begin(), std::bind2nd(std::plus<Point>(), pos));
  _shape.setCorners(std::move(cl));
}

Spaceship::~Spaceship()
{
}

const Shape& Spaceship::getShape() const
{
  return _shape;
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
  if (_last_bullet_activation + BULLET_COOLDOWN > NOW) return;
  _last_bullet_activation = NOW;
  _projectiles.emplace_back(_positionx, _positiony, _rotation);
}

void Spaceship::boost()
{
  if (_last_boost_activation + BOOST_COOLDOWN > NOW) return;
  _last_boost_activation = NOW;
  _speedx = ACCELERATION * std::abs(std::cos(_rotation));
  _speedy = ACCELERATION * std::abs(std::sin(_rotation));
}

void Spaceship::calcNewPosition(double tp)
{
  _speedx -= tp * ACCELERATION / 100;
  _speedy -= tp * ACCELERATION / 100;
  if (_speedx < 0) _speedx = 0;
  if (_speedy < 0) _speedy = 0;

  const double difference = _desired_rotation - _rotation;
  const double normalized_difference = std::remainder(difference, 2 * M_PI);
  // Rotate faster if difference is greater
  _rotation += normalized_difference * ROTATION_SPEED * tp;
  // Keep rotation in +- PI
  _rotation = std::remainder(_rotation, 2 * M_PI);

  const double delta_x = (_speedx + MIN_SPEED) * std::cos(_rotation) * tp;
  const double delta_y = (_speedy + MIN_SPEED) * std::sin(_rotation) * tp;

  _positionx += delta_x;
  _positiony += delta_y;

  _shape.move(delta_x, delta_y);

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
  // x,y should be position in world

  double deltaX = x - _positionx;
  double deltaY = y - _positiony;

  _desired_rotation = std::atan2(deltaY, deltaX);
}


