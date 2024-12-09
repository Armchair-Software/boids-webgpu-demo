#include "gui_renderer.h"
#include <emscripten/html5.h>
#include <imgui/imgui_impl_emscripten.h>
#include <imgui/imgui_impl_wgpu.h>
#include "logstorm/logstorm.h"
#include "boids.h"

namespace gui {

gui_renderer::gui_renderer(logstorm::manager &this_logger, boids_manager &this_boids)
  : logger{this_logger},
    boids{this_boids} {
  /// Construct the top level GUI and initialise ImGUI
  logger << "GUI: Initialising";
  #ifndef NDEBUG
    IMGUI_CHECKVERSION();
  #endif // NDEBUG
  ImGui::CreateContext();
  auto &imgui_io{ImGui::GetIO()};

  imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}

void gui_renderer::init(ImGui_ImplWGPU_InitInfo &imgui_wgpu_info) {
  /// Any additional initialisation that needs to occur after WebGPU has been initialised
  ImGui_ImplWGPU_Init(&imgui_wgpu_info);
  ImGui_ImplEmscripten_Init();
}

void gui_renderer::draw() {
  /// Render the top level GUI
  ImGui_ImplWGPU_NewFrame();
  ImGui_ImplEmscripten_NewFrame();
  ImGui::NewFrame();

  draw_boids_params_window();
  //ImGui::ShowDemoWindow();

  ImGui::Render();                                                              // finalise draw data (actual rendering of draw data is done by the renderer later)
}

void gui_renderer::draw_boids_params_window() {
  /// Draw the boids parameters window
  if(!ImGui::Begin("Chat")) {
    ImGui::End();
    return;
  }
  ImGui::SetWindowSize({600, 600});

  ImGui::InputInt("num_boids", const_cast<int*>(reinterpret_cast<int const*>(&boids.flock.num_boids)), 1, 100, ImGuiInputTextFlags_ReadOnly);
  // TODO: reinitialise when editing
  // TODO: reset button
  if(ImGui::InputInt("Frames between updates", reinterpret_cast<int*>(&boids.frames_between_boids_updates))) {
    boids.boids_to_update_per_tick = boids.flock.num_boids / boids.frames_between_boids_updates;
    boids.frames_since_last_boids_update = 0;
  }
  ImGui::InputInt("Frames since last update", reinterpret_cast<int*>(&boids.frames_since_last_boids_update), 1, 100, ImGuiInputTextFlags_ReadOnly);
  ImGui::InputInt("Boids to update per frame", reinterpret_cast<int*>(&boids.boids_to_update_per_tick), 1, 100, ImGuiInputTextFlags_ReadOnly);
  ImGui::DragFloat("World scale", &boids.world_scale, 0.1f, 0.1f, 10.0f, "%.1f");

  // TODO: float world_scale{4.0f};

  // TODO: collapsing section flockstorm

  // TODO: collapsing section positions
  // TODO: std::vector<vec3f> boid_positions_last{boids.num_boids};
  // TODO: std::vector<vec3f> boid_positions_next{boids.num_boids};
  // TODO: std::vector<vec3f> boid_positions_current{boids.num_boids};

  ImGui::End();
}

}
