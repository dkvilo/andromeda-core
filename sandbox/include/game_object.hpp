#ifndef __SANDBOX_APP__ENT_GAME_OBJECT__
#define __SANDBOX_APP__ENT_GAME_OBJECT__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"
#include "../../libs/math/functions.hpp"
#include "../../libs/util/uuid.hpp"

using namespace Andromeda::Components;
using namespace L::Util;

struct GameObject : public Andromeda::Entity
{

  GameObject(const char *name)
  {
    m_Name = name;
    m_ID = UUID().V1();
  }

  void update(double dt)
  {
    Transform *transform = static_cast<Transform *>(GetComponent("Transform"));
    if (transform != nullptr)
    {
      m_Position = transform->m_Position;
    }

    Shape2d *shape = static_cast<Shape2d *>(GetComponent("Shape2d"));
    if (shape != nullptr)
    {
      shape->m_Position = m_Position;
      shape->m_Radius = transform->m_Scale;
      shape->m_Rotation = transform->m_Rotation;
      shape->m_Angle = transform->m_Angle;
    }

    Stroke *stroke = static_cast<Stroke *>(GetComponent("Stroke"));
    if (stroke != nullptr)
    {
      stroke->m_Position = m_Position;
      stroke->m_Radius = transform->m_Scale;
      stroke->m_Rotation = transform->m_Rotation;
      stroke->m_Angle = transform->m_Angle;
    }

    Quad *quad = static_cast<Quad *>(GetComponent("Quad"));
    if (quad != nullptr)
    {
      quad->m_Position = m_Position;
      quad->m_Rotation = transform->m_Rotation;
    }

    Sphere *sphere = static_cast<Sphere *>(GetComponent("Sphere"));
    if (sphere != nullptr)
    {
      sphere->m_Position = m_Position;
      sphere->m_Radius = transform->m_Scale;
      sphere->m_Rotation = transform->m_Rotation;
      sphere->m_Angle = transform->m_Angle * dt;
    }

    for (auto item : GetComponents())
    {
      item.comp->update(dt);
    }
  }
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__