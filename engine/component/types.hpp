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
struct TypeName<Andromeda::Components::Quad>
{
  static const char *Get()
  {
    return "Quad";
  }
};

template <>
struct TypeName<Andromeda::Components::RGBColorMaterial>
{
  static const char *Get()
  {
    return "RGBColorMaterial";
  }
};

template <>
struct TypeName<Andromeda::Components::Shape2d>
{
  static const char *Get()
  {
    return "Shape2d";
  }
};

template <>
struct TypeName<Andromeda::Components::Sphere>
{
  static const char *Get()
  {
    return "Sphere";
  }
};

template <>
struct TypeName<Andromeda::Components::Stroke>
{
  static const char *Get()
  {
    return "Stroke";
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
struct TypeName<Andromeda::Components::LegacyQuad>
{
  static const char *Get()
  {
    return "LegacyQuad";
  }
};


#endif // ANDROMEDA_ENGINE_COMPONENTS_TYPES 