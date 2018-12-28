/*                                                     *
 * file: AS-environment.cpp                            *
 * author: Erik Hennig                                 *
 * date: 29.12.2016                                    *
 * abstract: controls environment of asteroids game    */

#include "AS-environment.h"
#include <algorithm>
#include <iostream>

extern uint32_t NOW;

Environment::Environment(Spaceship& s)
	: _last_generation ( 0 ),
	  _spaceship ( s )
{
  for (int i = 0; i < 1; ++i)
  {
    _asteroids.push_back(Asteroid::generate(5));
  }
}

Environment::~Environment()
{
}

void Environment::render()
{
  std::for_each(std::begin(_asteroids), std::end(_asteroids),
		  [](const Asteroid& a){
		    a.render(); 
		  });
}

int Environment::detectCollision(Spaceship s)
{
  const auto& ship = s.getShape();
  std::for_each(_asteroids.begin(), _asteroids.end(),
		  [ship] (const Asteroid& a) {
		    if (a.getShape().checkCollision(ship))
		    {
		      std::cout << "collision" << std::endl;
		    }
		  });
  return -1;
}

void Environment::detectCollision(Bullet b)
{

}

void Environment::process(double tp)
{
  std::for_each(std::begin(_asteroids), std::end(_asteroids),
		  [tp](Asteroid& a) {
		    a.process(tp);
		});

  if (_last_generation + GENERATION_COOLDOWN < NOW)
  {
     _asteroids.push_back(Asteroid::generate(5));
     _last_generation = NOW;
  }

  detectCollision(_spaceship);
}

void Environment::generate()
{

}

void Environment::splitAsteroid()
{

}

void Environment::checkHealth()
{

}

int Environment::calcmass()
{
  return -1;
}

