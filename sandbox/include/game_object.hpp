#ifndef __SANDBOX_APP__ENT_GAME_OBJECT__
#define __SANDBOX_APP__ENT_GAME_OBJECT__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "editor/editor.hpp"
#include "component/component.hpp"

#include "../../libs/math/functions.hpp"
#include "../../libs/util/uuid.hpp"

using namespace L::Util;
using namespace Andromeda::Components;

struct GameObject : public Andromeda::Entity
{

	Transform *c_Transform;
	Shape2d *c_Shape;
	Stroke *c_Stroke;
	Quad *c_Quad;
	Sphere *c_Sphere;
	Texture2d *c_Texture;
	LegacyQuad *c_LegacyQuad;

	bool m_Initialized = false;

	GameObject()
	{
		m_ID = UUID().V1();
	}

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
			c_Texture = static_cast<Texture2d *>(GetComponent("Texture2d"));
			c_LegacyQuad = static_cast<LegacyQuad *>(GetComponent("LegacyQuad"));

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
			if (c_Texture != nullptr)
			{
				c_Sphere->m_Texture = c_Texture->m_Texture;
			}
		}

		if (c_LegacyQuad != nullptr)
		{
			c_LegacyQuad->m_Position = c_Transform->m_Position;
			c_LegacyQuad->m_Rotation = c_Transform->m_Rotation;
			c_LegacyQuad->m_Angle = c_Transform->m_Angle;

			if (c_LegacyQuad->m_UseTransform)
			{
				c_LegacyQuad->m_Dimensions = vec2(c_Transform->m_Scale);
			}

			if (c_Texture != nullptr)
			{
				c_LegacyQuad->m_Texture = c_Texture->m_Texture;
			}
		}

		// Update entity components
		for (auto item : GetComponents())
		{
			if (item.comp->m_Flag)
			{
				item.comp->update(dt);
			}
		}
	}
};

#endif // __SANDBOX_APP__ENT_GAME_OBJECT__