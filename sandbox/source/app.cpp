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

  GameObject enemy = GameObject("Enemy");
  enemy.flag = 1;
  enemy.AddComponent("RGBColorMaterial", new Andromeda::Components::RGBColorMaterial(glm::vec3(0.951f, 0.070f, 0.381f)));
  enemy.AddComponent("Shape2d", new Andromeda::Components::Shape2d());
  enemy.AddComponent("Stroke", new Andromeda::Components::Stroke());
  enemy.AddComponent("Transfrom", new Andromeda::Components::Transform(glm::vec3(450.f, 462.f, 0.f), glm::vec3(0.f, 0.f, 0.f), 100.f));
  Andromeda::SceneManager::AddEntity(enemy.flag, &enemy);

  L::Graphics::Shader shader = L::Graphics::Shader(
      "./shaders/basic/color.frag",
      "./shaders/basic/color.vert");

  float positions[6] = {
      -0.5,
      -0.5,
      0.0,
      0.5,
      0.5,
      -0.5,
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0); // next 8 bytes 2 * sizeof(float)
  glEnableVertexAttribArray(0);

  while (!Andromeda::Window::ShouldClose(app.GetWidnowId()))
  {
    // Leasent for global events
    Andromeda::Window::PullEvents();

    // Update time in sandbox env
    app.UpdateTime(Andromeda::Window::TimeNow());

    // Draw in sandbox
    app.Draw(app.Width, app.Height);

    shader.Use();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    for (int i = 0; i < Andromeda::SceneManager::Registry.size(); i++)
    {
      auto ent = Andromeda::SceneManager::GetEntity(i);
      if (!ent->is_enabled)
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
