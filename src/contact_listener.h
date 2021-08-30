#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "phys_object.h"

#include <box2d/box2d.h>
#include <vector>
#include <functional>

class ContactListener : public b2ContactListener
{
public:
  ContactListener(int n_cars, std::function<void(int)> on_lap);

  void PreSolve(b2Contact *contact, const b2Manifold *old_manifold);
  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);

private:
  std::vector<bool> potential_laps;
  std::function<void(int)> on_lap;

  bool is_potential_lap(b2Body *body_a, b2Body *body_b, bool is_begin);
  PhysObject *cast_to_phys_obj(b2Body *body);
  int try_get_car_index(b2Body *body_a, b2Body *body_b);
};

#endif /* CONTACT_LISTENER */
