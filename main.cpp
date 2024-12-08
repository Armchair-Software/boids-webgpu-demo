#include <iostream>
#include <functional>
#include <map>
#include <emscripten/html5.h>
#include <imgui/imgui_impl_wgpu.h>
#include "logstorm/logstorm.h"
#include "vectorstorm/aabb/aabb3.h"
#include "vectorstorm/vector/vector3.h"
#include "flockstorm/flockstorm.h"
#include "gui/gui_renderer.h"
#include "render/webgpu_renderer.h"

class game_manager {
  flockstorm::manager boids{500};

  logstorm::manager logger{logstorm::manager::build_with_sink<logstorm::sink::console>()}; // logging system
  render::webgpu_renderer renderer{logger, boids.num_boids};                    // WebGPU rendering system
  gui::gui_renderer gui{logger};                                                // GUI top level

  std::vector<vec3f> boid_positions_last{boids.num_boids};
  std::vector<vec3f> boid_positions_next{boids.num_boids};
  std::vector<vec3f> boid_positions_current{boids.num_boids};

  float world_scale{4.0f};

  void loop_main();

public:
  game_manager();
};

game_manager::game_manager() {
  /// Run the game
  std::mt19937::result_type seed{1234};
  boids.distribute_boids_randomly(aabb3f(10.0f, 0.0f, -10.0f, 0.0f, 10.0f, 0.0f), seed);
  boids.goal_position.assign(0.0f, -50.0f, 100.0f);

  renderer.init(
    [&](render::webgpu_renderer::webgpu_data const& webgpu){
      ImGui_ImplWGPU_InitInfo imgui_wgpu_info;
      imgui_wgpu_info.Device = webgpu.device.Get();
      imgui_wgpu_info.RenderTargetFormat = static_cast<WGPUTextureFormat>(webgpu.surface_preferred_format);
      imgui_wgpu_info.DepthStencilFormat = static_cast<WGPUTextureFormat>(webgpu.depth_texture_format);

      gui.init(imgui_wgpu_info);
    },
    [&]{
      loop_main();
    }
  );
  std::unreachable();
}

void game_manager::loop_main() {
  /// Main pseudo-loop
  boids.update();
  // TODO: periodic update
  // TODO: update in sections to amortise cpu load

  std::swap(boid_positions_last, boid_positions_next);
  for(unsigned int i{0}; i != boids.num_boids; ++i) {
    boid_positions_next[i] = boids.get_position(i) * world_scale;
    boid_positions_current[i] = boid_positions_last[i];
  }

  gui.draw();
  renderer.draw(boid_positions_current);
}

auto main()->int {
  try {
    game_manager game;
    std::unreachable();

  } catch (std::exception const &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    EM_ASM(alert("Error: Press F12 to see console for details."));
  }

  return EXIT_SUCCESS;
}
