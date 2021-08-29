#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include <box2d/box2d.h>

class ContactListener : public b2ContactListener
{
public:
  void BeginContact(b2Contact *contact);
  void EndContact(b2Contact *contact);
};

#endif /* CONTACT_LISTENER */
