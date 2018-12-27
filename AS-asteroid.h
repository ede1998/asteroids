/*                                                     *
 * file: AS-asteroid.h                                 *
 * author: Erik Hennig                                 *
 * date: 27.12.2018                                    *
 * abstract: represents an asteroid                    */

#pragma once

#include <vector>

struct Point
{
  double x, y;
  Point(double x, double y): x(x), y(y) {}
};

class Asteroid
{
public:
  Asteroid(double posx, double posy, double speedx, double speedy, int mass);
  ~Asteroid();
  
  void render() const;
  void process(double tp);

  static Asteroid generate(int mass);
private:
  double _positionx;
  double _positiony;
  const double _speedx;
  const double _speedy;
  const int _mass;

  std::vector<Point> _corners;

  constexpr static int MASS_MAX  = 15000;
  constexpr static int MASS_SINGLE_MAX = 3000;
  constexpr static double MAX_SPEED = 1.6;
};
