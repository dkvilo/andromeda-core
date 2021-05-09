#ifndef __ENGINE_ENTITY__
#define __ENGINE_ENTITY__

#include <vector>
#include <string.h>

#include "andromeda.hpp"

#include "../../../libs/math/vec2.hpp"
#include "../../../libs/math/quat.hpp"

#include "glm/vec3.hpp"

struct Andromeda::Component
{
  const char *name;
  Andromeda::Entity *comp;
};

class Andromeda::Entity
{

public:
  size_t id;
  bool flag;
  glm::vec3 position;
  glm::vec3 rotation;

  bool is_enabled = false;
  bool is_selected = false;
  const char *name = "Unnamed Entity";

  std::vector<Andromeda::Component> components;

public:
  virtual void update(double dt) {}
  void AddComponent(const char *name, Andromeda::Entity *comp)
  {
    Andromeda::Component temp;
    temp.name = name;
    temp.comp = comp;
    this->components.push_back(temp);
  }

  Andromeda::Entity *GetComponent(const char *name)
  {
    for (auto c : this->components)
    {
      if (c.name == name)
      {
        return c.comp;
      }
    }
    return nullptr;
  }
};

namespace Andromeda::SceneManager
{

  std::vector<Andromeda::Entity *> Registry;

  void AddEntity(int index, Entity *ent)
  {
    Registry.push_back(ent);
  }

  Andromeda::Entity *GetEntity(int index)
  {
    return Andromeda::SceneManager::Registry.at(index);
  }
}

#endif // __ENGINE_ENTITY__