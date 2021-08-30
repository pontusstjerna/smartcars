#ifndef PHYS_OBJECT
#define PHYS_OBJECT

#include "body_data.h"

class PhysObject
{
public:
  const BodyData body_data;

  //virtual ~PhysObject() = 0;

protected:
  PhysObject(BodyData body_data) : body_data(body_data) {}
};

#endif /* PHYS_OBJECT */
