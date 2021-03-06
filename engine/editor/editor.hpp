#ifndef __ANDROMEDA_EDITOR_SPACE_HPP__
#define __ANDROMEDA_EDITOR_SPACE_HPP__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"

#include "../../engine/libs/libs.hpp"

#ifdef ANDROMEDA_EDITOR
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "fa-icons.hpp"
#endif

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "window/window.hpp"

#include "glm/gtc/type_ptr.hpp"

class Andromeda::Editor
{
	private:
		Andromeda::Window *m_Window;
		Andromeda::Entity *m_SelectedEntity;
		bool m_ShowEditableState = false;
		const char *m_GlslVersion = "#version 130";

	public:
		static void Init()
		{
			Get().setup_editor_impl();
		}

		static void Update(uint32_t frameBufferTextureID)
		{
			Get().update_editor_impl(frameBufferTextureID);
		}

		static void Clean()
		{
			Get().clean_up_editor_impl();
		}

		static void SetWindow(Andromeda::Window *window)
		{
			Get().set_window_impl(window);
		}

		static const char *GetSelectedEntityID()
		{
			return Get().get_selected_entity_ID_impl();
		}

	private:
		const char *get_selected_entity_ID_impl() const
		{
			if (m_SelectedEntity != nullptr)
			{
				return m_SelectedEntity->m_ID.c_str();
			}
			return nullptr;
		}

		void set_window_impl(Andromeda::Window *window)
		{
			m_Window = window;
		}

		void setup_editor_impl()
		{

#ifdef ANDROMEDA_EDITOR

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO &io = ImGui::GetIO();

			// Load main font (Ruda)
			{
				ImFontConfig config;
				config.OversampleH = 2;
				config.OversampleV = 1;
				config.GlyphExtraSpacing = ImVec2(1.0f, 1.0f);
				io.Fonts->AddFontFromFileTTF("./engine/editor/assets/font/Ruda-Bold.ttf", 14.5f, &config);
			}

			// Load Icons font
			{
				ImFontConfig config;
				config.MergeMode = true;
				config.PixelSnapH = true;

				config.OversampleH = 2;
				config.OversampleV = 1;
				config.GlyphExtraSpacing = ImVec2(3.0f, 3.0f);

				static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
				io.Fonts->AddFontFromFileTTF("./engine/editor/assets/font/Fa-Solid-900.ttf", 11.0f, &config, icons_ranges);
			}

			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

			ImGuiStyle *style = &ImGui::GetStyle();
			ImVec4 *colors = style->Colors;

			colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

			style->FramePadding = ImVec2(4, 2);
			style->ItemSpacing = ImVec2(10, 2);
			style->IndentSpacing = 12;
			style->ScrollbarSize = 10;

			style->WindowRounding = 4;
			style->FrameRounding = 4;
			style->PopupRounding = 4;
			style->ScrollbarRounding = 6;
			style->GrabRounding = 4;
			style->TabRounding = 4;
			style->ItemSpacing = ImVec2(10, 10);

			style->WindowTitleAlign = ImVec2(1.0f, 0.5f);
			style->WindowMenuButtonPosition = ImGuiDir_Right;

			ImGui_ImplGlfw_InitForOpenGL(m_Window->GetId(), true);
			ImGui_ImplOpenGL3_Init(m_GlslVersion);
#endif
		}

	private:
		void update_editor_impl(uint32_t frameBufferTextureID)
		{
#ifdef ANDROMEDA_EDITOR

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoResize;

			const ImGuiViewport *viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding & ImGuiStyleVar_FrameRounding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("Editor Tools", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
			ImGui::PopStyleVar();

			// DockSpace
			ImGuiIO &io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			ImGui::End(); // End of the Dockspace

			Editor::DrawGameViewPort(frameBufferTextureID);
			Editor::DrawEntityManagerTool();
			Editor::DrawProximaCommandLineTool();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		}

	private:
		void
			clean_up_editor_impl() const
			{
#ifdef ANDROMEDA_EDITOR
				ImGui_ImplOpenGL3_Shutdown();
				ImGui_ImplGlfw_Shutdown();
				ImGui::DestroyContext();
#endif
			}

		static void DrawProximaCommandLineTool()
		{
#ifdef ANDROMEDA_EDITOR
			ImGui::Begin("Proxima Command Line Tool");
			static char str0[128] = "@load_scene sandbox_01";
			ImGui::PushItemWidth(-1);
			ImGui::LogText(str0);
			ImGui::InputText("Proxima VM", str0, IM_ARRAYSIZE(str0));
			ImGui::PopItemWidth();
			ImGui::End();
#endif
		}

		void DrawGameViewPort(uint32_t texture)
		{
#ifdef ANDROMEDA_EDITOR
			ImGui::Begin("Viewport", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

			glm::vec2 windowSize = GetLargestSizeForViewport();
			glm::vec2 windowPos = GetCenteredPositionForViewport(windowSize);

			// Center Framebuffer Texture
			ImGui::SetCursorPos(ImVec2(windowPos.x, windowPos.y));

			ImGui::Image((ImTextureID)texture, ImVec2(windowSize.x, windowSize.y), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
#endif
		}

		static float TargetAspectRatio()
		{
			return 1.780f / 1.0f;
		}

		static glm::vec2 GetLargestSizeForViewport()
		{
#ifdef ANDROMEDA_EDITOR

			ImVec2 windowSize = ImGui::GetContentRegionAvail();

			windowSize.x -= ImGui::GetScrollX();
			windowSize.y -= ImGui::GetScrollY();

			float aspectWidth = windowSize.x;
			float aspectHight = aspectWidth / TargetAspectRatio();

			if (aspectHight > windowSize.y)
			{
				aspectWidth = aspectHight * TargetAspectRatio();
				aspectHight = windowSize.y;
			}

			return glm::vec2(aspectWidth, aspectHight);
#endif
		}

		static glm::vec2 GetCenteredPositionForViewport(const glm::vec2 &aspectSize)
		{
#ifdef ANDROMEDA_EDITOR

			ImVec2 windowSize = ImGui::GetContentRegionAvail();

			windowSize.x -= ImGui::GetScrollX();
			windowSize.y -= ImGui::GetScrollY();

			float viewportX = (windowSize.x / 2.0f) - (aspectSize.x / 2.0f);
			float viewportY = (windowSize.y / 2.0f) - (aspectSize.y / 2.0f);

			return glm::vec2(viewportX + ImGui::GetCursorPosX(), viewportY + ImGui::GetCursorPosY());
#endif
		}

		void DrawEntityManagerTool()
		{
#ifdef ANDROMEDA_EDITOR

			ImGui::Begin("Entity Manager Tool");
			ImGui::BeginTabBar("Scene");

			if (ImGui::BeginTabItem(ICON_FA_LIST_UL "Hierarchy"))
			{
				int manager_size = Andromeda::SceneManager::Registry.size();
				ImGui::Separator();
				ImGui::SetWindowFontScale(1.2);
				ImGui::Text("Entity Count: %d", manager_size);
				ImGui::SetWindowFontScale(1);
				ImGui::Separator();

				for (int i = 0; i < manager_size; i++)
				{
					auto ent = Andromeda::SceneManager::GetEntity(i);
					bool is_open = ImGui::TreeNode(ent->m_Name);
					if (!ent->m_Flag)
					{
						ImGui::SameLine();
						ImGui::Text(ICON_FA_EYE_SLASH);
					}
					if (is_open)
					{
						// Just render child component as a simple text for now
						for (int j = 0; j < ent->GetComponents().size(); j++)
						{
							ImGui::Text(ICON_FA_DICE_D6);
							ImGui::SameLine();
							ImGui::Text(ent->GetComponents()[j].name);
						}

						if (m_SelectedEntity != nullptr)
						{
							m_SelectedEntity = nullptr;
						}

						m_ShowEditableState = true;
						m_SelectedEntity = ent;
						ImGui::TreePop();
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(ICON_FA_FAN "Environment"))
			{
				ImGui::TextWrapped("This section is responsible for modifing current scene environment, 2DLighting, Shaddow, World Physics");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(ICON_FA_MUSIC "Audio"))
			{
				ImGui::TextWrapped("This section is responsible for managing audio streams and resources in current the scene");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem(ICON_FA_PLUG "Input"))
			{
				ImGui::TextWrapped("This section is responsible for user Input mapping and device input configuration in the current scene. But you can select Set As Global to uee it in the entire project");
				static bool is_global;
				ImGui::Checkbox("Use as global", &is_global);
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar(); // End Entity Manager Tool
			ImGui::End();

			ImGui::Begin(ICON_FA_LIST_UL "Inspector");
			if (m_ShowEditableState && m_SelectedEntity != nullptr)
			{
				Editor::DrawEntityComponentEditableProperties(m_SelectedEntity);
			}
			ImGui::End();
#endif
		}

		static void DrawEntityComponentEditableProperties(Andromeda::Entity *ent)
		{
#ifdef ANDROMEDA_EDITOR

			ASSERT(ent, "Entity was not initialized", NULL);

			ImGui::Separator();
			ImGui::Checkbox(ent->m_Name, &ent->m_Flag);
			ImGui::Separator();
			ImGui::Text("ID: %s", ent->m_ID.c_str());

			auto transform = static_cast<Transform *>(ent->GetComponent("Transform"));
			if (transform != nullptr)
			{
				ImGui::Separator();
				ImGui::Text(ICON_FA_DICE_D6 "%s", transform->m_Name);
				ImGui::DragFloat3("Position", glm::value_ptr(transform->m_Position));
				ImGui::SliderFloat3("Scale", glm::value_ptr(transform->m_Scale), 0.0f, 10.f);
				ImGui::SliderFloat3("Rotation", glm::value_ptr(transform->m_Rotation), -1, 1);
				ImGui::SliderFloat("Angle", &transform->m_Angle, -360.0f, 360.f);
			} 

			auto camera = static_cast<Camera *>(ent->GetComponent("Camera"));
			if (camera != nullptr)
			{
				ImGui::Separator();
				ImGui::Text(ICON_FA_DICE_D6 "%s", camera->m_Name);
				ImGui::DragFloat3("Eye", glm::value_ptr(camera->GetEye()));
				ImGui::DragFloat3("Center", glm::value_ptr(camera->GetCenter()));
				ImGui::DragFloat3("Up", glm::value_ptr(camera->GetUp()));
			}

			auto texture = static_cast<Texture2d *>(ent->GetComponent("Texture2d"));
			if (texture != nullptr)
			{
				ImGui::Separator();
				ImGui::Text(ICON_FA_DICE_D6 "%s", texture->m_Name);
				ImGui::Text(ICON_FA_DICE_D6 "Path: %s", texture->m_Texture->GetPath());
				// ImGui::Text(ICON_FA_DICE_D6 "SLOT: %s", texture->m_Texture->GetSlot());
				ImGui::Image((ImTextureID) texture->m_Texture->GetRendererID(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));	
			}
#endif
		}

	public:
		static Editor &Get()
		{
			static Editor instance;
			return instance;
		}

		Editor(){};
};

#endif // __ANDROMEDA_EDITOR_SPACE_HPP__
