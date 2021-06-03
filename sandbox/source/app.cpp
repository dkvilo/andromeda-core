#include "app.hpp"

using namespace glm;
using namespace Andromeda::Components;

// Sandbox Draw Implementation
void Sandbox::Draw(int width, int height)
{
  // Extend Base Renderer from sandbox
  Sandbox::BaseRenderer(width, height);
  glClearColor(0.11f, 0.11f, 0.11f, 1);
}

int main(int argc, char const *argv[])
{

  Sandbox app = Sandbox();

  Andromeda::Editor::SetWindow(app.Window());
  Andromeda::Editor::Init();

  GameObject player = GameObject();
  player.AddComponent<RGBColorMaterial>(new RGBColorMaterial(vec3(0.951f, 0.070f, 0.381f)));
  player.AddComponent<Shape2d>(new Shape2d());
  player.AddComponent<Stroke>(new Stroke());
  player.AddComponent<Transform>(new Transform(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.5f));
  Andromeda::SceneManager::AddEntity(&player);

  GameObject quad = GameObject("Test Shape");
  quad.AddComponent<RGBColorMaterial>(new RGBColorMaterial(vec3(0.928f, 1.000f, 0.387f)));
  quad.AddComponent<Quad>(new Quad());
  quad.AddComponent<Transform>(new Transform(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.5f));
  Andromeda::SceneManager::AddEntity(&quad);

  GameObject ball = GameObject("Ball");
  ball.AddComponent<RGBColorMaterial>(new RGBColorMaterial(vec3(0.928f, 1.000f, 0.387f)));
  ball.AddComponent<Transform>(new Transform(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.5f));
  ball.AddComponent<Sphere>(new Sphere());
  Andromeda::SceneManager::AddEntity(&ball);

  RGBColorMaterial *colorMaterial = static_cast<RGBColorMaterial *>(ball.GetComponent("RGBColorMaterial"));

  Transform *transform = static_cast<Transform *>(ball.GetComponent("Transform"));
  if (transform != nullptr)
  {
    // Pick rotation side
    transform->m_Rotation.y = 0.347f;
    // Scale up the mesh
    transform->m_Scale = 0.631f;
  }

  while (!Andromeda::Window::ShouldClose(app.GetWidnowId()))
  {
    // Listen for window events
    Andromeda::Window::PullEvents();

    // Update time in sandbox env
    app.UpdateTime(Andromeda::Window::TimeNow());

    // Draw in sandbox
    app.Draw(app.m_Width, app.m_Height);

    for (uint32_t i = 0; i < Andromeda::SceneManager::Registry.size(); i++)
    {
      auto ent = Andromeda::SceneManager::GetEntity(i);
      if (ent->m_Flag)
      {
        // Update entity
        ent->update(app.m_ElapsedTime);

        //  Update color values dynamically based on elapsedTime
        if (colorMaterial != nullptr)
        {
          colorMaterial->m_Color =
              vec3(abs(sin(L::Math::Lerp(.0f, .7f, app.m_ElapsedTime))),
                   abs(cos(L::Math::Lerp(.0f, .7f, app.m_ElapsedTime))),
                   abs(sin(L::Math::Lerp(.0f, .4f, app.m_ElapsedTime))));
        }

        // Update rotation angle based on elapsedTime
        if (transform != nullptr)
        {
          transform->m_Angle = 90.0f * app.m_ElapsedTime;
        }
      }
    }

    // // Resize Geometry owned by sandbox
    app.Resize();

    // // Update Endinge Editor UI
    Andromeda::Editor::Update();

    // Swap Buffers
    Andromeda::Window::SwapBuffers(app.GetWidnowId());
  }

  // Clean Up
  Andromeda::Editor::Clean();
  Andromeda::Window::Destory(app.GetWidnowId());

  return 0;
}
