#ifndef CAR
#define CAR

#include <box2d/box2d.h>

class Car
{
public:
  Car(float x, float y, float rot);
  ~Car();

  // 1.95 meter wide, 2 meters long
  float width = 1.95;
  float length = 2;

  float get_x();
  float get_y();
  float get_rot();

private:
  b2Body *body;
};

#endif /* CAR */
