#ifndef __SANDBOX_APP__ENT_GAME_OBJECT__
#define __SANDBOX_APP__ENT_GAME_OBJECT__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"
#include "../../libs/math/functions.hpp"
#include "../../libs/util/uuid.hpp";

using namespace Andromeda::Components;
using namespace L::Util;

struct GameObject : public Andromeda::Entity
{

  GameObject(const char *name)
  {
    this->name = name;
    this->id = UUID().V1();
  }

  void update(double dt)
  {
    Transform *transform = static_cast<Transform *>(this->GetComponent("Transfrom"));
    if (transform != nullptr)
    {
      this->position = transform->position;
    }

    Shape2d *shape = static_cast<Shape2d *>(this->GetComponent("Shape2d"));
    if (shape != nullptr)
    {
      shape->position = this->position;
      shape->radius = transform->scale;
      shape->rotation = transform->rotation;
      shape->angle = transform->angle;
    }

    Stroke *stroke = static_cast<Stroke *>(this->GetComponent("Stroke"));
    if (stroke != nullptr)
    {
      stroke->position = this->position;
      stroke->radius = transform->scale;
      stroke->rotation = transform->rotation;
      stroke->angle = transform->angle;
    }

    Quad *quad = static_cast<Quad *>(this->GetComponent("Quad"));
    if (quad != nullptr)
    {
      quad->position = this->position;
      quad->rotation = transform->rotation;
    }

    Sphere *sphere = static_cast<Sphere *>(this->GetComponent("Sphere"));
    if (sphere != nullptr)
    {
      sphere->position = this->position;
      sphere->radius = transform->scale;
      sphere->rotation = transform->rotation;
      sphere->angle = transform->angle * dt;
    }

    for (auto item : this->components)
    {
      item.comp->update(dt);
    }
  }
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__