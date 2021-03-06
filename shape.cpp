/*                                                     *
 * file: shape.cpp                                     *
 * author: Erik Hennig                                 *
 * date: 28.12.2018                                    *
 * abstract: a polygon shape for collision detection   */

#include "shape.h"
#include <numeric>
#include <cassert>
#include <algorithm>
#include <functional>

Shape::Shape(const Point& p, const CornerList& cl)
	: Shape(p)
{
  _corners = cl;
  assert(_corners.size() > 0);
}

Shape::Shape(const Point& p)
: _position(p)
{

}

Shape::Shape()
: _position(0,0)
{
}

void Shape::setCorners(const CornerList& cl)
{
  _corners = cl;
}

void Shape::setPosition(const Point& p)
{
  _position = p;
}

bool Shape::checkCollision(const Shape& other) const
{
  const double collision_dist = getAvgRadius() + other.getAvgRadius();
  const Point vec_this_other = other.getCenter() - getCenter();
  const double actual_dist = vec_this_other.getLength();
  
  return actual_dist <= collision_dist;
}

void Shape::move(double x, double y)
{
  const Point p(x,y);
  _position = _position + p;
}

Point Shape::getCenter() const
{
  const Point center = _position + getRelativeCenter();
  return center;
}

Point Shape::getRelativeCenter() const
{
  const size_t num_points = _corners.size();
  const Point relative_center = std::accumulate(_corners.begin(), _corners.end(), Point(0,0)) / num_points;
  return relative_center;
}

double Shape::getAvgRadius() const
{
  const size_t num_points = _corners.size();
  const Point center = getRelativeCenter();

  // Calculate all distances to center and average
  std::vector<double> distances;
  for (const Point& p : _corners)
  {
    const Point vec_p_center = p - center;
    distances.push_back(vec_p_center.getLength());
  }
  return std::accumulate(distances.begin(), distances.end(), 0) / num_points;
}
