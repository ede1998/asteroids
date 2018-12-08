/*                                          *
 * file: AS-spaceship.h                     *
 * author: Erik Hennig                      *
 * date: 25.12.2016                         *
 * abstract: definition of spaceship class, *
 *          used for player controlled unit */

#define AS_SPACESHIP_BULLET_COOLDOWN 50
#define AS_SPACESHIP_BULLET_DMG 100
#define AS_BULLET_SPEED 0.1
#define AS_SPACESHIP_ACC 0.03

#define AS_MAP_LEFT -40
#define AS_MAP_RIGHT 40
#define AS_MAP_BOTTOM -30
#define AS_MAP_TOP 30
#define AS_MAP_WIDTH (std::abs(AS_MAP_RIGHT)+std::abs(AS_MAP_LEFT))
#define AS_MAP_HEIGHT (std::abs(AS_MAP_TOP)+std::abs(AS_MAP_BOTTOM))
#define AS_MAP_XYRATIO (AS_MAP_HEIGHT/AS_MAP_WIDTH)

#define AS_SPACESHIP_X1 5
#define AS_SPACESHIP_Y1 0
#define AS_SPACESHIP_X2 -5
#define AS_SPACESHIP_Y2  5
#define AS_SPACESHIP_X3  -5
#define AS_SPACESHIP_Y3  -5

#define PI 3.14159265358979

#include "Ordered-list.h"

struct bullet
{
  double rot, posx, posy;
};

class spaceship
{
  public:
    spaceship(double x, double y, double rot = 0);
    virtual ~spaceship();
    void renderSpaceship();
    void renderProjectiles();
    void shoot();
    void boost();
    void rotate(double x, double y);
    void calcNewPosition(double tp);
    double x1,y1;
  private:
    double _positionx;
    double _positiony;
    double _speedx;
    double _speedy;
    double _rotation;
    int _bullet_cooldown;
    ordered_list * _projectiles;
    void calcBulletPos(double tp);
};

