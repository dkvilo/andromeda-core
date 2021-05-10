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

    Andromeda::Components::Shape2d *shape = static_cast<Andromeda::Components::Shape2d *>(this->GetComponent("Shape2d"));
    if (shape != nullptr)
    {
      shape->position = this->position;
      shape->radius = transform->scale;
    }

    Andromeda::Components::Stroke *stroke = static_cast<Andromeda::Components::Stroke *>(this->GetComponent("Stroke"));
    if (stroke != nullptr)
    {
      stroke->position = this->position;
      stroke->radius = transform->scale;
    }

    for (auto item : this->components)
    {
      item.comp->update(dt);
    }
  }
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__