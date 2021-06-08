#ifndef __ENGINE_ENTITY__
#define __ENGINE_ENTITY__

#include <string>
#include <vector>

#include "andromeda.hpp"
#include "log/log.hpp"
#include "component/types.hpp"

#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Andromeda::Entity
{

public:
	bool m_Flag = true;

	std::string m_ID;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;

	const char *m_Name = "Unnamed Entity";

private:
	std::vector<Andromeda::Types::Component> m_Components;

public:
	virtual void update(double dt) {}

	// Type and Name Safe
	template <typename T>
	void AddComponent(Andromeda::Entity *comp)
	{

		const char *typeName = TypeName<T>().Get();
		for (auto comp : m_Components)
		{
			// Check for unique name
			ASSERT(comp.name != typeName, "[GameObject] component already exists with the name:", typeName);
			// Check for type
			auto status = static_cast<T *>(comp.comp);
			ASSERT(status, "[GameObject] component already exists with the type:", typeName);
		}
		m_Components.push_back(Andromeda::Types::Component{name : typeName, comp});

		Andromeda::Log::SetPrefix(typeName);
		Andromeda::Log::Print("component added");
	}

	void AddComponent(const char *name, Andromeda::Entity *comp)
	{
		for (auto comp : m_Components)
		{
			ASSERT(comp.name != name, "[GameObject] component already exists with the name:", name);
		}
		m_Components.push_back(Andromeda::Types::Component{name, comp});
	}

	std::vector<Andromeda::Types::Component> GetComponents() const
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