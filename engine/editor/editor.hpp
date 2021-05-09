#ifndef ANDROMEDA_EDITOR_SPACE_HPP
#define ANDROMEDA_EDITOR_SPACE_HPP

#include "andromeda.hpp"
#include "entity/entity.hpp"
#include "component/component.hpp"

#ifdef ANDROMEDA_EDITOR
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "window/window.hpp"

class Andromeda::Editor
{
private:
  Andromeda::Window *m_window;
  const char *glsl_version = "#version 130";
  bool show_editable_state = false;
  int selected_ent_index = 0;

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

  void set_window_impl(Andromeda::Window *window)
  {
    this->m_window = window;
  }

private:
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
    io.Fonts->AddFontFromFileTTF("./assets/font/Ruda-Bold.ttf", 15.0f, &config);

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

    ImGui_ImplGlfw_InitForOpenGL(this->m_window->GetId(), true);
    ImGui_ImplOpenGL3_Init(this->glsl_version);
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
    static char str0[128] = "Hello, World";
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
        bool is_open = ImGui::TreeNode(ent->name);
        if (ent->is_enabled)
        {
          ImGui::SameLine();
          ImGui::Text("Disabled");
        }

        if (is_open)
        {

          ImGui::Separator();
          ImGui::Checkbox("Disabled", &ent->is_enabled);
          ImGui::Separator();
          ImGui::Text("Entity flag: %d", ent->flag);

          Editor::DrawEntityComponentEditableProperties(ent);

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
#endif
  }

  static void DrawEntityComponentEditableProperties(Andromeda::Entity *ent)
  {
#ifdef ANDROMEDA_EDITOR

    Andromeda::Components::Transform *transform = static_cast<Andromeda::Components::Transform *>(ent->GetComponent("Transfrom"));
    if (transform != nullptr)
    {
      ImGui::Separator();
      ImGui::Text("Component [%s]", transform->name);
      ImGui::Text("Position");
      ImGui::SliderFloat("X", &transform->position.x, 0.0f, 1000.0f);
      ImGui::SliderFloat("Y", &transform->position.y, 0.0f, 1000.0f);
      ImGui::Text("Scale");
      ImGui::SliderFloat("xyz", &transform->scale, 0, 400);
    }

    Andromeda::Components::RGBColorMaterial *color_material = static_cast<Andromeda::Components::RGBColorMaterial *>(ent->GetComponent("RGBColorMaterial"));
    if (color_material != nullptr)
    {
      ImGui::Separator();
      ImGui::Text("Component [%s]", color_material->name);
      ImGui::Text("Color");
      ImGui::ColorEdit3("Primary", (float *)&color_material->color);
    }

    Andromeda::Components::Gizmo2d *gizmo = static_cast<Andromeda::Components::Gizmo2d *>(ent->GetComponent("Gizmo2d"));
    if (gizmo != nullptr)
    {
      ImGui::Separator();
      ImGui::Text("Component [%s]", gizmo->name);
      ImGui::Text("Rotation");
      ImGui::SliderFloat3("xyz", (float *)&gizmo->rotation, -360, 360);
      ImGui::SliderFloat("Angle", &gizmo->angle, 0, 360);
      ImGui::Text("Offset");
      ImGui::SliderFloat("xy", &gizmo->offset, 0, 100);
      ImGui::Text("Segments");
      ImGui::SliderInt("Count", &gizmo->segments, 4, 100);
      ImGui::Text("Line");
      ImGui::SliderInt("Width", &gizmo->line_width, 1, 10);
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

#endif // ANDROMEDA_EDITOR_SPACE_HPP
