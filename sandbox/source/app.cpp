#include "app.hpp"

using namespace glm;
using namespace Andromeda::Components;

/// Sandbox Draw Implementation
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

  GameObject player = GameObject("Player");
  player.AddComponent("RGBColorMaterial", new RGBColorMaterial(vec3(0.951f, 0.070f, 0.381f)));
  player.AddComponent("Shape2d", new Shape2d());
  player.AddComponent("Stroke", new Stroke());
  player.AddComponent("Transfrom", new Transform(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.5f));
  Andromeda::SceneManager::AddEntity(&player);

  GameObject enemy = GameObject("Enemy");
  enemy.AddComponent("RGBColorMaterial", new RGBColorMaterial(vec3(0.951f, 0.070f, 0.381f)));
  enemy.AddComponent("Shape2d", new Shape2d());
  enemy.AddComponent("Stroke", new Stroke());
  enemy.AddComponent("Transfrom", new Transform(vec3(1.f, 2.f, 0.f), vec3(0.f, 0.f, 0.f), 0.4f));
  Andromeda::SceneManager::AddEntity(&enemy);

  GameObject quad = GameObject("Quad");
  quad.AddComponent("RGBColorMaterial", new RGBColorMaterial(vec3(0.928f, 1.000f, 0.387f)));
  quad.AddComponent("Quad", new Quad());
  quad.AddComponent("Transfrom", new Transform(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.5f));
  quad.AddComponent("Stroke", new Stroke());
  Andromeda::SceneManager::AddEntity(&quad);

  while (!Andromeda::Window::ShouldClose(app.GetWidnowId()))
  {
    // Leasent for global events
    Andromeda::Window::PullEvents();

    // Update time in sandbox env
    app.UpdateTime(Andromeda::Window::TimeNow());

    // Draw in sandbox
    app.Draw(app.Width, app.Height);

    for (int i = 0; i < Andromeda::SceneManager::Registry.size(); i++)
    {
      auto ent = Andromeda::SceneManager::GetEntity(i);
      if (ent->flag)
      {
        ent->update(app.elapsedTime);
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
