/*                                          *
 * file: AS-spaceship.h                     *
 * author: Erik Hennig                      *
 * date: 25.12.2016                         *
 * abstract: definition of spaceship class, *
 *          used for player controlled unit */

#include <vector>

#define AS_MAP_LEFT -40
#define AS_MAP_RIGHT 40
#define AS_MAP_BOTTOM -30
#define AS_MAP_TOP 30
#define AS_MAP_WIDTH (std::abs(AS_MAP_RIGHT)+std::abs(AS_MAP_LEFT))
#define AS_MAP_HEIGHT (std::abs(AS_MAP_TOP)+std::abs(AS_MAP_BOTTOM))
#define AS_MAP_XYRATIO ((double)AS_MAP_HEIGHT/AS_MAP_WIDTH)


struct Bullet
{
  double _rotation, _positionx, _positiony;
  Bullet(double posx, double posy, double rot)
	  : _rotation(rot), _positionx(posx), _positiony(posy)
  {
  }
  constexpr static int DAMAGE = 100;
  constexpr static double SPEED = 0.1;
};

class Spaceship
{
  public:
    Spaceship(double x, double y, double rot = 0);
    virtual ~Spaceship();
    void renderSpaceship();
    void renderProjectiles();
    void shoot();
    void boost();
    void rotate(double x, double y);
    void calcNewPosition(double tp);
  private:
    double _positionx;
    double _positiony;
    double _speedx;
    double _speedy;
    double _rotation;
    int _bullet_cooldown;
    std::vector<Bullet> _projectiles;
    void calcBulletPos(double tp);

    constexpr static int VERTICES_X[] = {5,-5,-5};
    constexpr static int VERTICES_Y[] = {0,5,-5};
    constexpr static double ACCELERATION = 0.03;
    constexpr static int BULLET_COOLDOWN = 50;
};

