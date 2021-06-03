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

  Transform *c_Transform;
  Shape2d *c_Shape;
  Stroke *c_Stroke;
  Quad *c_Quad;
  Sphere *c_Sphere;

  bool m_Initialized = false;

  GameObject(const char *name)
  {
    m_Name = name;
    m_ID = UUID().V1();
  }

  void update(double dt)
  {
    if (!m_Initialized)
    {
      c_Transform = static_cast<Transform *>(GetComponent("Transform"));
      c_Shape = static_cast<Shape2d *>(GetComponent("Shape2d"));
      c_Stroke = static_cast<Stroke *>(GetComponent("Stroke"));
      c_Quad = static_cast<Quad *>(GetComponent("Quad"));
      c_Sphere = static_cast<Sphere *>(GetComponent("Sphere"));

      m_Initialized = true;
    }

    if (c_Transform != nullptr)
    {
      m_Position = c_Transform->m_Position;
    }

    if (c_Shape != nullptr)
    {
      c_Shape->m_Position = c_Transform->m_Position;
      c_Shape->m_Radius = c_Transform->m_Scale;
      c_Shape->m_Rotation = c_Transform->m_Rotation;
      c_Shape->m_Angle = c_Transform->m_Angle;
    }

    if (c_Stroke != nullptr)
    {
      c_Stroke->m_Position = c_Transform->m_Position;
      c_Stroke->m_Radius = c_Transform->m_Scale;
      c_Stroke->m_Rotation = c_Transform->m_Rotation;
      c_Stroke->m_Angle = c_Transform->m_Angle;
    }

    if (c_Quad != nullptr)
    {
      c_Quad->m_Position = c_Transform->m_Position;
      c_Quad->m_Rotation = c_Transform->m_Rotation;
    }

    if (c_Sphere != nullptr)
    {
      c_Sphere->m_Position = c_Transform->m_Position;
      c_Sphere->m_Radius = c_Transform->m_Scale;
      c_Sphere->m_Rotation = c_Transform->m_Rotation;
      c_Sphere->m_Angle = c_Transform->m_Angle;
    }

    for (auto item : GetComponents())
    {
      item.comp->update(dt);
    }
  }
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__