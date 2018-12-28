/*                                                     *
 * file: point.h                                       * 
 * author: Erik Hennig                                 *
 * date: 28.12.2018                                    *
 * abstract: a point class for collision detection     */

#pragma once

struct Point
{
  double x, y;
  Point(double x, double y);
  double getLength() const;
};

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator/(const Point& lhs, const double scalar);
Point operator*(const Point& lhs, const double scalar);
