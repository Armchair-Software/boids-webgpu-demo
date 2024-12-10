#include "boids.h"
#include "vectorstorm/aabb/aabb3.h"

boids_manager::boids_manager() {
  /// Default c'tor
  std::mt19937::result_type seed{1234};
  flock.distribute_boids_randomly(aabb3f{-50.0f, -100.0f, 50.0f, 50.0f, -80.0f, 150.0f}, seed);
  flock.goal_position.assign(0.0f, -25.0f, 50.0f);
  for(unsigned int i{0}; i != flock.num_boids; ++i) {
    boid_positions_next[i] = flock.get_position(i) * world_scale;
    boid_positions_last[i] = boid_positions_next[i];
  }

  /*
  // tending very slightly towards chaotic explosion, good filaments and sub-shoals
  flock.collision_avoidance_range = 3.5f;
  flock.collision_avoidance_scale = 0.100f;
  flock.velocity_matching_range   = 5.0f;
  flock.velocity_matching_scale   = 0.100f;
  flock.flock_centering_range     = 7.0f;
  flock.flock_centering_scale     = 0.150f;
  flock.goal_seeking_scale        = 0.200f;
  flock.acceleration_max          = 0.600f;
  flock.damping_factor            = 0.9140f;                                    // needs very careful tuning to maintain overall system energy balance - 0.915 is sometimes too low, 0.916 is just a bit too high
  */

  // only-just eventually stable with occasional orbiting sub-flocks
  flock.collision_avoidance_range = 3.5f;
  flock.collision_avoidance_scale = 0.100f;
  flock.velocity_matching_range   = 5.0f;
  flock.velocity_matching_scale   = 0.099f;                                     // just below 0.100 seems to be important to avoid divergence
  flock.flock_centering_range     = 7.0f;
  flock.flock_centering_scale     = 0.150f;
  flock.goal_seeking_scale        = 0.200f;
  flock.acceleration_max          = 0.600f;
  flock.damping_factor            = 0.9140f;                                    // needs very careful tuning to maintain overall system energy balance
  flock.update_precomputed_quantities();
}

void boids_manager::update() {
  /// Update boids each frame
  if(frames_since_last_boids_update == frames_between_boids_updates) {
    // update the interpolation start and end points
    flock.update_partial_finalise();

    std::swap(boid_positions_last, boid_positions_next);
    for(unsigned int i{0}; i != flock.num_boids; ++i) {
      boid_positions_next[i] = flock.get_position(i) * world_scale;
      boid_positions_current[i] = boid_positions_last[i];
    }
    frames_since_last_boids_update = 0;
  } else {
    // interpolate boid positions in sections each frame
    flock.update_partial(boids_to_update_per_tick * frames_since_last_boids_update, boids_to_update_per_tick * (frames_since_last_boids_update + 1));

    auto const factor{static_cast<float>(frames_since_last_boids_update) / static_cast<float>(frames_between_boids_updates)};
    for(unsigned int i{0}; i != flock.num_boids; ++i) {
      boid_positions_current[i] = boid_positions_last[i].lerp(factor, boid_positions_next[i]);
    }
    ++frames_since_last_boids_update;
  }
}
