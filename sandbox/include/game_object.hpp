#ifndef __SANDBOX_APP__ENT_GAME_OBJECT__
#define __SANDBOX_APP__ENT_GAME_OBJECT__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"

#include "../../libs/math/functions.hpp"

struct GameObject : public Andromeda::Entity
{

  GameObject(const char *name)
  {
    this->name = name;
  }

  void update(double dt)
  {
    Andromeda::Components::Transform *transform = static_cast<Andromeda::Components::Transform *>(this->GetComponent("Transfrom"));
    if (transform != nullptr)
    {
      this->position = transform->position;
    }

    Andromeda::Components::Circle2d *circle = static_cast<Andromeda::Components::Circle2d *>(this->GetComponent("Circle2d"));
    if (circle != nullptr)
    {
      circle->position = this->position;
      circle->radius = transform->scale;
    }

    Andromeda::Components::Gizmo2d *gizmo = static_cast<Andromeda::Components::Gizmo2d *>(this->GetComponent("Gizmo2d"));
    if (gizmo != nullptr)
    {
      gizmo->position = this->position;
      gizmo->radius = transform->scale;
    }

    for (auto item : this->components)
    {
      item.comp->update(dt);
    }
  }
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__