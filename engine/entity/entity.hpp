#ifndef __ENGINE_ENTITY__
#define __ENGINE_ENTITY__

#include <vector>

#include "../../../libs/math/vec2.hpp"
#include "../../../libs/math/quat.hpp"

#include "andromeda.hpp"
#define GLM_HAS_UNRESTRICTED_UNIONS
#include "glm/vec3.hpp"

//
// TODO: Refactor the entity, add the component infrastructure
// THIS IS TEMP IMPLEMENTATION
// HERE WILL BE ONLY flag, position, orientation, update and components array
//
struct Andromeda::Entity
{
  int flag;
  glm::vec3 color;
  L::Vec2 position;
  L::Quat orientation;
  int scale;
  bool is_selected = false;
  virtual void update() {}
  const char *name = "Unnamed Entity";
  bool is_static = false;
};

namespace Andromeda::Manager
{

  std::vector<Andromeda::Entity *> Registry;

  void AddEntity(int index, Entity *ent)
  {
    Registry.push_back(ent);
  }

  Andromeda::Entity *GetEntity(int index)
  {
    return Andromeda::Manager::Registry.at(index);
  }

}

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