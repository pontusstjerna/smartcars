#include "contact_listener.h"
#include "body_data.h"

#include <iostream>

using namespace std;

void ContactListener::BeginContact(b2Contact *contact)
{
  b2Body *body_a = contact->GetFixtureA()->GetBody();
  b2Body *body_b = contact->GetFixtureB()->GetBody();

  BodyData *data_a = NULL;
  BodyData *data_b = NULL;

  data_a = (BodyData *)body_a->GetUserData().pointer;
  data_b = (BodyData *)body_b->GetUserData().pointer;

  cout << "Contact!";
  if (data_a != NULL)
  {
    cout << " A body type: " << data_a->body_type;
  }
  if (data_b != NULL)
  {
    cout << " B body type: " << data_b->body_type;
  }
  cout << endl;
}

void ContactListener::EndContact(b2Contact *contact)
{
  cout << "Contact ended!\n";
}