/*                                                     *
 * file: AS-environment.h                              *
 * author: Erik Hennig                                 *
 * date: 29.12.2016                                    *
 * abstract: controls environment of asteroids game    */

#include "AS-spaceship.h"

#define AS_ASTEROID_MASS_MAX 15000
#define AS_ASTEROID_MASS_SINGLE_MAX 3000
#define AS_ASTEROID_SPEED 100

struct Point
{
  double x, y;
};

struct Asteroid
{
  double _positionx, _positiony;
  double _speedx, _speedy;
  int _mass;
  //vertices (relative)
  Point v[7];
};

class Environment
{
  public:
    Environment();
    ~Environment();
    void render();
    int detectCollision(Spaceship s);
    void detectCollision(Bullet b);
    void process();
    void generate();
    
  private:
    std::vector<Asteroid> _asteroids;
    void generateAsteroid(int mass);
    void splitAsteroid();
    void moveAsteroid();
    void checkhealth();
    int calcmass();

};
