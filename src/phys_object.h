#ifndef PHYS_OBJECT
#define PHYS_OBJECT

#include "body_data.h"

class PhysObject
{
public:
  BodyData get_body_data()
  {
    return body_data;
  }

protected:
  BodyData body_data;
};

#endif /* PHYS_OBJECT */
