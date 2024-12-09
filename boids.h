#pragma once

#include <vector>
#include "vectorstorm/vector/vector3.h"
#include "flockstorm/flockstorm.h"

class boids_manager {
public:
  #ifdef NDEBUG
    flockstorm::manager flock{5'000};
  #else
    flockstorm::manager flock{1'000};
  #endif // NDEBUG

private:
  std::vector<vec3f> boid_positions_last{flock.num_boids};
  std::vector<vec3f> boid_positions_next{flock.num_boids};
public:
  std::vector<vec3f> boid_positions_current{flock.num_boids};
  unsigned int frames_between_boids_updates{10};
  unsigned int frames_since_last_boids_update{0};

  unsigned int boids_to_update_per_tick{flock.num_boids / frames_between_boids_updates};

  float world_scale{4.0f};

  boids_manager();

  void update();
};
