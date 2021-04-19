#ifndef __ENGINE_ENTITY__
#define __ENGINE_ENTITY__

#include "../../../libs/math/vec2.hpp"
#include "../../../libs/math/quat.hpp"

#include "andromeda.hpp"

struct Andromeda::Entity
{
  int flag;
  L::Vec2 position;
  L::Quat orientation;
  virtual void update();
};

/*

  Usage:

    struct Door : public Andromeda::Entity
    {
      bool is_opened;
      void update() override;
    };

    void do_something(Door *d)
    {
      d->update();
    }

    void x(Andromeda::Entity *d)
    {
      d->update();
    }

    void y() {
      Door d;
      x(&d);
    }
    
*/

#endif // __ENGINE_ENTITY__