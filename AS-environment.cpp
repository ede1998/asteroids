/*                                                     *
 * file: AS-environment.cpp                            *
 * author: Erik Hennig                                 *
 * date: 29.12.2016                                    *
 * abstract: controls environment of asteroids game    */

#include "AS-environment.h"
#include "algorithm"

extern uint32_t NOW;

Environment::Environment()
	: _last_generation ( 0 )
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

