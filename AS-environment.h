/*                                                     *
 * file: AS-environment.h                              *
 * author: Erik Hennig                                 *
 * date: 29.12.2016                                    *
 * abstract: controls environment of asteroids game    */

#include "AS-spaceship.h"

#define AS_ASTEROID_MASS_MAX 15000
#define AS_ASTEROID_MASS_SINGLE_MAX 3000
#define AS_ASTEROID_SPEED 100

struct point
{
  double x, y;
};

struct asteroid
{
  double posx, posy;
  double speedx, speedy;
  int mass;
  //vertices (relative)
  point v[7];
};

class environment
{
  public:
    environment();
    ~environment();
    void render();
    int detectCollision(spaceship s);
    void detectCollision(bullet b);
    void process();
    void generate();
    
  private:
    ordered_list asteroids;
    void generateAsteroid(int mass);
    void splitAsteroid();
    void moveAsteroid();
    void checkhealth();
    int calcmass();

};
