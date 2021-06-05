
#ifndef __ANDROMEDA_EDITOR_CAMERA_HPP__
#define __ANDROMEDA_EDITOR_CAMERA_HPP__

#include "andromeda.hpp"
#include "entity/entity.hpp"

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class Andromeda::EditorCamera : public Andromeda::Entity
{

public:
  EditorCamera() = default;
  
  EditorCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(ortho(left, right, bottom, top)), m_ViewMatrix(1.0f)
    {
    } 

  void SetProjection(float left, float right, float bottom, float top)
  {
    m_ProjectionMatrix = ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix; 
  }

  void CalculateViewMatrix()
  {
    mat4 transform = translate(mat4(1.0f), m_Position) 
      * rotate(mat4(1.0f), radians(m_Rotation), vec3(0, 0, 1));
		
    m_ViewMatrix = inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
  }

  float GetRotation() const 
  {
    return m_Rotation;
  }

  void SetRotation(float rotation)
  {
    m_Rotation = rotation; 
    CalculateViewMatrix();
  }

  const mat4& GetProjectionMatrix() const 
  {
    return m_ProjectionMatrix;
  }
  
  const mat4& GetViewMatrix() const
  {
    return m_ViewMatrix;
  }
  
  const mat4& GetViewProjectionMatrix() const
  {
    return m_ViewProjectionMatrix;
  }

private:
  mat4 m_ViewProjectionMatrix;
  mat4 m_ViewMatrix;
  mat4 m_ProjectionMatrix;
  float m_Rotation;
};

#endif // __ANDROMEDA_EDITOR_CAMERA_HPP__
