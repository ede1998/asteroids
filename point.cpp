/*                                                     *
 * file: point.cpp                                     *
 * author: Erik Hennig                                 *
 * date: 28.12.2018                                    *
 * abstract: a point class for collision detection     */

#include "point.h"
#include <cmath>

Point::Point(double x, double y)
	: x(x), y(y)
{
}

double Point::getLength() const
{
  return std::sqrt(x * x + y * y);
}

Point operator+(const Point& lhs, const Point& rhs)
{
  return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point operator-(const Point& lhs, const Point& rhs)
{
  return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

Point operator/(const Point& lhs, const double scalar)
{
  return Point(lhs.x / scalar, lhs.y / scalar);
}

Point operator*(const Point& lhs, const double scalar)
{
  return Point(lhs.x * scalar, lhs.y * scalar);
}
