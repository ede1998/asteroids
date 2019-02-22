/*                                                     *
 * file: shape.h                                       * 
 * author: Erik Hennig                                 *
 * date: 28.12.2018                                    *
 * abstract: a polygon shape for collision detection   */

#pragma once

#include <vector>
#include "point.h"


class Shape
{
public:
  using CornerList = std::vector<Point>;
  Shape(const Point& p, const CornerList& cl);
  Shape(const Point& p);
  Shape();

  void setCorners(const CornerList& cl);
  void setPosition(const Point& p);

  bool checkCollision(const Shape& other) const;
  void move(double x, double y);
private:
  CornerList _corners;
  Point _position;

  double getAvgRadius() const;
  Point getCenter() const;
  Point getRelativeCenter() const;
};
