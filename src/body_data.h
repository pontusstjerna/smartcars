#ifndef BODY_DATA
#define BODY_DATA

enum BodyType
{
  CAR,
  GOAL_LINE,
  TRACK_SEGMENT
};

struct BodyData
{
  BodyType body_type;
  int index;

  BodyData(BodyType body_type, int index) : body_type(body_type), index(index) {}
  BodyData(BodyType body_type) : body_type(body_type), index(0) {}
};

#endif /* BODY_DATA */
