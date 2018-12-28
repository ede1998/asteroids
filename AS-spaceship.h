/*                                          *
 * file: AS-spaceship.h                     *
 * author: Erik Hennig                      *
 * date: 25.12.2016                         *
 * abstract: definition of spaceship class, *
 *          used for player controlled unit */

#pragma once

#include <cstdint>
#include <vector>
#include "AS-map.h"
#include "shape.h"

struct Bullet
{
  double _rotation, _positionx, _positiony;
  Bullet(double posx, double posy, double rot)
	  : _rotation(rot), _positionx(posx), _positiony(posy)
  {
  }
  constexpr static int DAMAGE = 100;
  constexpr static double SPEED = 3;
};

class Spaceship
{
  public:
    Spaceship(double x, double y, double rot = 0);
    virtual ~Spaceship();
    void renderSpaceship();
    void renderProjectiles();
    const Shape& getShape() const;
    void shoot();
    void boost();
    void rotate(double x, double y);
    void calcNewPosition(double tp);
  private:
    double _positionx;
    double _positiony;
    double _speedx;
    double _speedy;
    double _rotation;
    double _desired_rotation;
    uint32_t _last_boost_activation;
    uint32_t _last_bullet_activation;
    std::vector<Bullet> _projectiles;
    Shape _shape;
    void calcBulletPos(double tp);

    constexpr static int VERTICES_X[] = {5,-5,-5};
    constexpr static int VERTICES_Y[] = {0,5,-5};
    constexpr static double ACCELERATION = 1;
    constexpr static int BULLET_COOLDOWN = 100;
    constexpr static uint32_t BOOST_COOLDOWN = 10000;
    constexpr static double ROTATION_SPEED = 0.05;
    constexpr static double MIN_SPEED = 0.3;
};

