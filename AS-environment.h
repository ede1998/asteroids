/*                                                     *
 * file: AS-environment.h                              *
 * author: Erik Hennig                                 *
 * date: 29.12.2016                                    *
 * abstract: controls environment of asteroids game    */

#pragma once

#include "AS-spaceship.h"
#include "AS-asteroid.h"
#include <cstdint>

class Environment
{
  public:
    Environment();
    ~Environment();
    void render();
    int detectCollision(Spaceship s);
    void detectCollision(Bullet b);
    void process(double tp);
    void generate();
    
  private:
    std::vector<Asteroid> _asteroids;
    uint32_t _last_generation;
    void splitAsteroid();
    void checkHealth();
    int calcmass();

    constexpr static uint32_t GENERATION_COOLDOWN = 2000;
};
