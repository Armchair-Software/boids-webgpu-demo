#pragma once
#include "logstorm/logstorm_forward.h"

class ImGui_ImplWGPU_InitInfo;
class boids_manager;

namespace gui {

class gui_renderer {
  logstorm::manager &logger;
  boids_manager &boids;

public:
  gui_renderer(logstorm::manager &logger, boids_manager &boids);

  void init(ImGui_ImplWGPU_InitInfo &wgpu_info);

  void draw();

  void draw_boids_params_window();
};

}
