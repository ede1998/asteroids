/*                                                     *
 * file: AS-asteroid.h                                 *
 * author: Erik Hennig                                 *
 * date: 27.12.2018                                    *
 * abstract: represents an asteroid                    */

#pragma once

#include <vector>
#include "shape.h"


class Asteroid
{
public:
  Asteroid(double posx, double posy, double speedx, double speedy, int mass);
  ~Asteroid();
  
  const Shape& getShape() const;
  void render() const;
  void process(double tp);
  static Asteroid generate(int mass);
private:
  double _positionx;
  double _positiony;
  const double _speedx;
  const double _speedy;
  const int _mass;
  Shape _shape;

  std::vector<Point> _corners;

  constexpr static int MASS_MAX  = 15000;
  constexpr static int MASS_SINGLE_MAX = 3000;
  constexpr static double MAX_SPEED = 1.6;
};
