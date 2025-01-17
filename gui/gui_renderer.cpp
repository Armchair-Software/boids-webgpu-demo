#include "gui_renderer.h"
#include <emscripten/html5.h>
#include <imgui/imgui_impl_emscripten.h>
#include <imgui/imgui_impl_wgpu.h>
#include "logstorm/logstorm.h"
#include "vectorstorm/aabb/aabb3.h"
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
  if(!ImGui::Begin("Boids Parameters")) {
    ImGui::End();
    return;
  }
  ImGui::SetWindowSize({600, 600});

  ImGui::InputInt("num_boids", const_cast<int*>(reinterpret_cast<int const*>(&boids.flock.num_boids)), 1, 100, ImGuiInputTextFlags_ReadOnly);
  // TODO: reinitialise when editing
  if(ImGui::Button("Reset positions")) boids.flock.distribute_boids_randomly(aabb3f{-50.0f, -100.0f, 50.0f, 50.0f, -80.0f, 150.0f}, 1234);
  if(ImGui::InputInt("Frames between updates", reinterpret_cast<int*>(&boids.frames_between_boids_updates))) {
    boids.boids_to_update_per_tick = boids.flock.num_boids / boids.frames_between_boids_updates;
    boids.frames_since_last_boids_update = 0;
  }
  ImGui::InputInt("Frames since last update", reinterpret_cast<int*>(&boids.frames_since_last_boids_update), 1, 100, ImGuiInputTextFlags_ReadOnly);
  ImGui::InputInt("Boids to update per frame", reinterpret_cast<int*>(&boids.boids_to_update_per_tick), 1, 100, ImGuiInputTextFlags_ReadOnly);
  // TODO: section: display
  ImGui::DragFloat("World scale", &boids.world_scale, 0.1f, 0.1f, 10.0f, "%.1f");

  // TODO: float world_scale{4.0f};

  // TODO: collapsing section flockstorm parameters



  if(ImGui::DragFloat("Collision avoidance range", &boids.flock.collision_avoidance_range, 0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Collision avoidance scale", &boids.flock.collision_avoidance_scale, 0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Velocity matching range",   &boids.flock.velocity_matching_range,   0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Velocity matching scale",   &boids.flock.velocity_matching_scale,   0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Flock centering range",     &boids.flock.flock_centering_range,     0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Flock centering scale",     &boids.flock.flock_centering_scale,     0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Goal seeking scale",        &boids.flock.goal_seeking_scale,        0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Acceleration maximum",      &boids.flock.acceleration_max,          0.001f, 0.0f, 0.0f)) boids.flock.update_precomputed_quantities();
  if(ImGui::DragFloat("Damping factor",            &boids.flock.damping_factor,            0.0001f, 0.0f, 0.0f, "%.4f")) boids.flock.update_precomputed_quantities();
  //if(ImGui::DragFloat("Speed limit maximum",      flock.speed_limit_max,            0.01f,  0.0f, 0.0f)) flock.update_precomputed_quantities();
  //if(ImGui::DragFloat("Speed limit minimum",      flock.speed_limit_min,            0.001f, 0.0f, 0.0f)) flock.update_precomputed_quantities();
  //if(ImGui::Button("Copy to clipboard")) {
    // TODO
  //}

  ImGui::DragFloat3("Goal position", &boids.flock.goal_position[0]);

  // TODO: obstacle sphere management: add, remove, move, scale

  // TODO: collapsing section positions
  // TODO: std::vector<vec3f> boid_positions_last{boids.num_boids};
  // TODO: std::vector<vec3f> boid_positions_next{boids.num_boids};
  // TODO: std::vector<vec3f> boid_positions_current{boids.num_boids};

  // TODO: graphs window: total system energy etc

  ImGui::End();
}

}
