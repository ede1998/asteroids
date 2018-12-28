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
  Shape(const CornerList& cl);
  Shape() = default;

  void setCorners(const CornerList& cl);

  bool checkCollision(const Shape& other) const;
  void move(double x, double y);
private:
  CornerList _corners;

  double getAvgRadius() const;
  Point getCenter() const;
};
