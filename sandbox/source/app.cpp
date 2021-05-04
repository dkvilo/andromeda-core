#include "app.hpp"

void put_pixel_impl(unsigned int size, const L::Vec2 pos, const glm::vec3 color)
{
  glPointSize(size);
  glTranslatef(pos.x, pos.y, 0);
  glBegin(GL_POINTS);
  glVertex3f(pos.x, pos.y, 0.0f);
  glColor3f(color.r, color.g, color.b);
  glEnd();
}

struct Sprite : public Andromeda::Entity
{
  void update() override
  {
    put_pixel_impl(this->scale, this->position, this->color);
  };
};

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

  Sprite player;
  player.name = "Player";
  player.flag = 0;
  player.scale = 161.f;
  player.position = L::Vec2(50.f, 62.f);
  player.color = glm::vec3(0.985f, 0.145f, 0.442f);
  Andromeda::Manager::AddEntity(0, &player);

  Sprite enemy;
  enemy.name = "Enemy";
  enemy.is_static = true;
  enemy.flag = 1;
  enemy.scale = 100;
  enemy.position = L::Vec2(100.f, 40.f);
  enemy.color = glm::vec3(1, 1, 1);
  Andromeda::Manager::AddEntity(1, &enemy);

  while (!Andromeda::Window::ShouldClose(app.GetWidnowId()))
  {
    // Leasent for global events
    Andromeda::Window::PullEvents();

    // Update time in sandbox env
    app.UpdateTime(Andromeda::Window::TimeNow());

    // Draw in sandbox
    app.Draw(app.Width, app.Height);

    for (int i = 0; i < Andromeda::Manager::Registry.size(); i++)
    {
      auto ent = Andromeda::Manager::GetEntity(i);
      if (!ent->is_static)
      {
        ent->update();
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
