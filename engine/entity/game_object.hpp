#ifndef __ENGINE_GAME_OBJECT__
#define __ENGINE_GAME_OBJECT__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"

#include "libs/math/functions.hpp"
#include "libs/util/uuid.hpp"

using namespace L::Util;
using namespace Andromeda::Components;

struct GameObject : public Andromeda::Entity
{

	Mesh2d 		*c_Mesh2d;
	Camera		*c_Camera;
	Transform 	*c_Transform;
	Texture2d 	*c_Texture;

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
			c_Mesh2d 	= static_cast<Mesh2d    *>(GetComponent("Mesh2d"));
			c_Texture 	= static_cast<Texture2d *>(GetComponent("Texture2d"));
			c_Transform = static_cast<Transform *>(GetComponent("Transform"));
			c_Camera	= static_cast<Camera 	*>(GetComponent("Camera"));

			m_Initialized = true;
		}

		if (c_Transform != nullptr)
		{
			m_Position = c_Transform->m_Position;
			m_Rotation = c_Transform->m_Rotation;
		}

		if (c_Mesh2d != nullptr)
		{
			c_Mesh2d->m_Position = m_Position;
			c_Mesh2d->m_Rotation = m_Rotation;
			
			if (c_Transform != nullptr)
			{
				c_Mesh2d->m_Scale = c_Transform->m_Scale;
				c_Mesh2d->m_Model = c_Transform->m_Projection;
			}
			
			if (c_Texture != nullptr)
			{
				c_Mesh2d->c_Texture = *c_Texture;
			}

			if (c_Camera != nullptr)
			{
				c_Mesh2d->m_View = c_Camera->m_Projection;
			}
		}

		/**
		 * 
		 * Update entity components
		 * 
		 */
		for (auto item : GetComponents())
		{
			if (item.comp->m_Flag)
			{
				item.comp->update(dt);
			}
		}
	}
};

#endif // __ENGINE_GAME_OBJECT__
