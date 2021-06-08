#ifndef __ENGINE_COMPONENT__
#define __ENGINE_COMPONENT__

#include "andromeda.hpp"

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class Andromeda::Component
{
public:
	mat4 m_Projection;

	Component() : m_Projection(1.0f) {}

	void UpdateProjection(float top, float right, float bottom, float left, float near, float far)
	{
		m_Projection = ortho(top, right, bottom, left, near, far);
	}

	vec3 ScreenToWorldSpace(const vec3 &position)
	{
		return vec3(vec4(position, 1.0f) * m_Projection);
	}
};

#endif // __ENGINE_COMPONENT__