#ifndef __ANDROMEDA_CORE_API__
#define __ANDROMEDA_CORE_API__

#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

namespace Andromeda
{

	enum RenderingAPI
	{
		OpenGL,
		Metal,
		WebGL,
		None
	};

	struct Entity;
	struct Component;
	struct UI;

	class Renderer;
	class Editor;
	class EditorCamera;
	class Window;
	class Log;
}

namespace Andromeda::Runtime
{
	class Storage;
};

namespace Andromeda::Components
{
	class Transform;
	struct Mesh2d;
	struct Texture2d;
	class Camera;
}

namespace Andromeda::Types
{
	struct WindowConfog;
	struct Component
	{
		const char *name;
		Andromeda::Entity *comp;
	};
}

#endif // __ANDROMEDA_CORE_API__