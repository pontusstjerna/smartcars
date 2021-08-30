#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "phys_object.h"

#include <box2d/box2d.h>
#include <vector>

class ContactListener : public b2ContactListener
{
public:
  ContactListener(int n_cars);

  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);

private:
  bool is_potential_lap(b2Body *body_a, b2Body *body_b, bool is_begin);
  std::vector<bool> potential_laps;
  PhysObject *cast_to_phys_obj(b2Body *body);
  int try_get_car_index(b2Body *body_a, b2Body *body_b);
};

#endif /* CONTACT_LISTENER */
