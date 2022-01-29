#ifndef ANDROMEDA_ENGINE_COMPONENT_TYPES
#define ANDROMEDA_ENGINE_COMPONENTS_TYPES

#include "../andromeda.hpp"

template <typename T>
struct TypeName
{
	static const char *Get()
	{
		return typeid(T).name();
	}
};

template <>
struct TypeName<Andromeda::Components::Transform>
{
	static const char *Get()
	{
		return "Transform";
	}
};

template <>
struct TypeName<Andromeda::Components::Mesh2d>
{
	static const char *Get()
	{
		return "Mesh2d";
	}
};
template <>
struct TypeName<Andromeda::Components::Texture2d>
{
	static const char *Get()
	{
		return "Texture2d";
	}
};

template <>
struct TypeName<Andromeda::Components::Camera>
{
	static const char *Get()
	{
		return "Camera";
	}
};


#endif // ANDROMEDA_ENGINE_COMPONENTS_TYPES