#include "app.hpp"

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
  player.flag = 0;
  player.AddComponent("RGBColorMaterial", new Andromeda::Components::RGBColorMaterial(glm::vec3(0.951f, 0.070f, 0.381f)));
  player.AddComponent("Shape2d", new Andromeda::Components::Shape2d());
  player.AddComponent("Stroke", new Andromeda::Components::Stroke());
  player.AddComponent("Transfrom", new Andromeda::Components::Transform(glm::vec3(150.f, 162.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 100.f));
  Andromeda::SceneManager::AddEntity(player.flag, &player);

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
      if (!ent->is_enabled)
      {
        ent->update(app.elapsedTime);
      }
    }

    // Resize Geometry owned by sandbox
    app.Resize();

    // Update Endinge Editor UI
    Andromeda::Editor::Update();

    // Swap Buffers
    Andromeda::Window::SwapBuffers(app.GetWidnowId());
  }

  // Clean Up
  Andromeda::Editor::Clean();
  Andromeda::Window::Destory(app.GetWidnowId());

  return 0;
}
