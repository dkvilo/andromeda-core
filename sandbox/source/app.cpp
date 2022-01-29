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

	// GameObject quad2 = GameObject("Test Shape 2");
	// 	quad2.AddComponent<Texture2d>(new Texture2d("./sandbox/assets/texture/blank.png", 0));
	// 	quad2.AddComponent<Mesh2d>(new Mesh2d(1.0f));

	// 	quad2.AddComponent<Transform>(
	// 		new Transform(
	// 			vec3(1.0f, 0.0f, 1.0f), 	// Position
	// 			vec3(0.0f, 0.0f, 1.0f), 	// Rotation
	// 			vec3(10.0f, 10.0f, 10.0f)	// Scale
	// 		)
	// 	);
		
	// 	quad2.AddComponent<Camera>(new Camera(
	// 		vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
	// 		vec3(0, 0, 0), // and looks at the origin
	// 		vec3(0, 1, 0) // Head is up (set to 0,-1, 0 to look upside-down)
	// 	));

	// Andromeda::SceneManager::AddEntity(&quad2);
	

	GameObject quad = GameObject("Test Shape");
		quad.AddComponent<Texture2d>(new Texture2d("./sandbox/assets/texture/default.png", 1));
		quad.AddComponent<Mesh2d>(new Mesh2d(1.0f));

		quad.AddComponent<Transform>(
			new Transform(
				vec3(1.0f, 0.0f, 1.0f), 	// Position
				vec3(0.0f, 0.0f, 1.0f), 	// Rotation
				vec3(10.0f, 10.0f, 10.0f)	// Scale
			)
		);
		
		quad.AddComponent<Camera>(new Camera(
			vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			vec3(0, 0, 0), // and looks at the origin
			vec3(0, 1, 0) // Head is up (set to 0,-1, 0 to look upside-down)
		));

	Andromeda::SceneManager::AddEntity(&quad);


	while (!Andromeda::Window::ShouldClose(app.GetWidnowId()))
	{
		// Listen for window events
		Andromeda::Window::PullEvents();

		// Update time in sandbox env
		app.UpdateTime(Andromeda::Window::TimeNow());

#if defined(ANDROMEDA_EDITOR)
		app.m_FrameBuffer->Bind();
#endif
		// Draw in sandbox
		app.Draw(app.m_Width, app.m_Height);

		for (uint32_t i = 0; i < Andromeda::SceneManager::Registry.size(); i++)
		{
			auto ent = Andromeda::SceneManager::GetEntity(i);
			if (ent->m_Flag)
			{
				// Update entity
				ent->update(app.m_ElapsedTime);
			}
		}
 
#if defined(ANDROMEDA_EDITOR)
		app.m_FrameBuffer->Unbind();
#endif

		// Resize 
		app.Resize();

		// Update Endinge Editor UI
		Andromeda::Editor::Update(app.m_FrameBuffer->GetTextureID());

		// Swap Buffers
		Andromeda::Window::SwapBuffers(app.GetWidnowId());
	}

	// Clean Up
	Andromeda::Editor::Clean();
	Andromeda::Window::Destory(app.GetWidnowId());

	return 0;
}
