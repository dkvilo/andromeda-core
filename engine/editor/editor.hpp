#ifndef __ANDROMEDA_EDITOR_SPACE_HPP__
#define __ANDROMEDA_EDITOR_SPACE_HPP__

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"

#include "../../libs/libs.hpp"

#ifdef ANDROMEDA_EDITOR
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
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

  static void Update()
  {
    Get().update_editor_impl();
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

#ifdef ANDROMEDA_EDITOR)

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    float round_value = 3.0f;

    ImGuiStyle *style = &ImGui::GetStyle();
    ImVec4 *colors = style->Colors;

    ImFontConfig config;
    config.OversampleH = 2;
    config.OversampleV = 1;
    config.GlyphExtraSpacing.x = 1.0f;
    io.Fonts->AddFontFromFileTTF("./engine/editor/assets/font/Ruda-Bold.ttf", 15.0f, &config);

    colors[ImGuiCol_Text] = ImVec4(0.952, 0.962, 0.982, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
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
  void update_editor_impl()
  {
#ifdef ANDROMEDA_EDITOR

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool opt_fullscreen = true;
    static bool opt_padding = true;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
    if (opt_fullscreen)
    {
      const ImGuiViewport *viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->WorkPos);
      ImGui::SetNextWindowSize(viewport->WorkSize);
      ImGui::SetNextWindowViewport(viewport->ID);
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (opt_padding)
    {
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding & ImGuiStyleVar_FrameRounding, ImVec2(0.0f, 0.0f));
    }

    ImGui::Begin("Editor Tools", 0, window_flags);
    if (opt_padding)
    {
      ImGui::PopStyleVar();
    }

    // DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    ImGui::End(); // End of the Dockspace

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

  void DrawEntityManagerTool()
  {
#ifdef ANDROMEDA_EDITOR

    ImGui::Begin("Entity Manager Tool");
    ImGui::BeginTabBar("Scene");

    if (ImGui::BeginTabItem("Hierarchy"))
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
          ImGui::Text("Disabled");
        }
        if (is_open)
        {
          // Just render child component as a simple text for now
          for (int j = 0; j < ent->GetComponents().size(); j++)
          {
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

    if (ImGui::BeginTabItem("Environment"))
    {
      ImGui::TextWrapped("This section is responsible for modifing current scene environment, 2DLighting, Shaddow, World Physics");
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Audio"))
    {
      ImGui::TextWrapped("This section is responsible for managing audio streams and resources in current the scene");
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Input"))
    {
      ImGui::TextWrapped("This section is responsible for user Input mapping and device input configuration in the current scene. But you can select Set As Global to uee it in the entire project");
      static bool is_global;
      ImGui::Checkbox("Use as global", &is_global);
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar(); // End Entity Manager Tool
    ImGui::End();

    ImGui::Begin("Inspector");
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

    Andromeda::Components::Transform *transform = static_cast<Andromeda::Components::Transform *>(ent->GetComponent("Transform"));
    if (transform != nullptr)
    {
      ImGui::Separator();
      ImGui::Text("%s", transform->m_Name);
			ImGui::DragFloat3("Position", glm::value_ptr(transform->m_Position));
      ImGui::DragFloat("Scale", &transform->m_Scale);
      ImGui::Text("Rotation");
      ImGui::DragFloat3("xyz", glm::value_ptr(transform->m_Rotation), -1, 1);
      ImGui::DragFloat("Angle", &transform->m_Angle);
    }

    Andromeda::Components::RGBColorMaterial *color_material = static_cast<Andromeda::Components::RGBColorMaterial *>(ent->GetComponent("RGBColorMaterial"));
    if (color_material != nullptr)
    {
      ImGui::Separator();
      ImGui::Checkbox(color_material->m_Name, &color_material->m_Flag);
      ImGui::Text("Color");
      ImGui::ColorEdit3("Primary", glm::value_ptr(color_material->m_Color));
    }

    Andromeda::Components::Shape2d *shape = static_cast<Andromeda::Components::Shape2d *>(ent->GetComponent("Shape2d"));
    if (shape != nullptr)
    {
      ImGui::Separator();
      ImGui::Checkbox(shape->m_Name, &shape->m_Flag);
      ImGui::Text("Segments");
      ImGui::DragInt("Face", &shape->m_Segments, 0, shape->m_Triangles);
      ImGui::Text("Triangles");
      ImGui::DragInt("Max Triangles", &shape->m_Triangles, 3, 100);
    }

    Andromeda::Components::Quad *quad = static_cast<Andromeda::Components::Quad *>(ent->GetComponent("Quad"));
    if (quad != nullptr)
    {
      ImGui::Separator();
      ImGui::Checkbox(quad->m_Name, &quad->m_Flag);
    }

    Andromeda::Components::Texture2d *texture = static_cast<Andromeda::Components::Texture2d *>(ent->GetComponent("Texture2d"));
    if (texture != nullptr)
    {
      ImGui::Separator();
      ImGui::Checkbox(texture->m_Name, &texture->m_Flag);
      ImGui::Separator();
      ImGui::Text("Path: %s", texture->m_Path);
      ImGui::Separator();
      ImGui::Text("ID: %d", texture->m_Texture);
    }

    Andromeda::Components::LegacyQuad *legacyQuad = static_cast<Andromeda::Components::LegacyQuad *>(ent->GetComponent("LegacyQuad"));
    if (legacyQuad != nullptr)
    {
      ImGui::Separator();
      ImGui::Text("%s", legacyQuad->m_Name);
      ImGui::Text("Dimensions");
      ImGui::Checkbox("Use Transform", &legacyQuad->m_UseTransform);
      if (!legacyQuad->m_UseTransform)
      {
        ImGui::DragFloat2("XY", glm::value_ptr(legacyQuad->m_Dimensions), 0.1f, 10.f);
      }
    }

    Andromeda::Components::Stroke *stroke = static_cast<Andromeda::Components::Stroke *>(ent->GetComponent("Stroke"));
    if (stroke != nullptr)
    {
      ImGui::Separator();
      ImGui::Checkbox(stroke->m_Name, &stroke->m_Flag);
      ImGui::Text("Offset");
      ImGui::DragFloat("xy", &stroke->m_Offset, 0, 100);
      ImGui::Text("Segments");
      ImGui::DragInt("Count", &stroke->m_Segments, 3, 100);
      ImGui::Text("Line");
      ImGui::DragInt("Width", &stroke->m_LineWidth, 1, 10);
      ImGui::ColorEdit3("Border", glm::value_ptr(stroke->m_ColorMaterial->m_Color));
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
