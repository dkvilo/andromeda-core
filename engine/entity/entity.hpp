#ifndef __ENGINE_ENTITY__
#define __ENGINE_ENTITY__

#include "andromeda.hpp"
#include "glm/vec3.hpp"

#include <string>
#include <vector>

struct Andromeda::Component
{
  const char *name;
  Andromeda::Entity *comp;
};

class Andromeda::Entity
{

public:
  bool flag = 1;

  std::string m_ID;
  glm::vec3 m_Position;
  glm::vec3 m_Rotation;

  const char *m_Name = "Unnamed Entity";

private:
  std::vector<Andromeda::Component> m_Components;

public:
  virtual void update(double dt) {}
  void AddComponent(const char *name, Andromeda::Entity *comp)
  {
    m_Components.push_back(Andromeda::Component{name, comp});
  }

  std::vector<Andromeda::Component> GetComponents() const
  {
    return m_Components;
  }

  Andromeda::Entity *GetComponent(const char *name)
  {
    for (auto child : m_Components)
    {
      if (child.name == name)
      {
        return child.comp;
      }
    }
    return nullptr;
  }
};

namespace Andromeda::SceneManager
{

  std::vector<Andromeda::Entity *> Registry;

  void AddEntity(Entity *ent)
  {
    Registry.push_back(ent);
  }

  Andromeda::Entity *GetEntity(int index)
  {
    return Andromeda::SceneManager::Registry.at(index);
  }
}

#endif // __ENGINE_ENTITY__