#pragma once

// This file is automatically generated from render/shaders/default.wgsl by ./compile_resource_to_raw_string.sh

namespace render::shaders {

inline constexpr char const *default_wgsl{R"1366a8cee8786564(struct vertex_input {
  @builtin(instance_index) instance: u32,
  @location(0) position: vec3f,
  @location(1) normal: vec3f,
  @location(2) colour: vec4f,
};
struct vertex_output {
  @builtin(position) position: vec4f,
  @location(1) @interpolate(flat, first) colour: vec4f,
};
struct uniform_struct {
  model_view_projection_matrix: array<mat4x4f, 30 * 30>,
  normal_matrix: mat3x3f,
};
@group(0) @binding(0) var<uniform> uniforms: uniform_struct;
const light_dir = vec3f(0.872872, 0.218218, -0.436436); 
const ambient = 0.5f;
@vertex
fn vs_main(in: vertex_input) -> vertex_output {
  var out: vertex_output;
  out.position = uniforms.model_view_projection_matrix[in.instance] * vec4f(in.position, 1.0);
  let transformed_normal = uniforms.normal_matrix * in.normal;
  let diffuse_intensity = (max(dot(transformed_normal, light_dir), 0.0) * (1.0 - ambient)) + ambient;
  out.colour = vec4f(in.colour.rgb * diffuse_intensity, in.colour.a);
  return out;
}
@fragment
fn fs_main(in: vertex_output) -> @location(0) vec4f {
  return in.colour;
}
)1366a8cee8786564"};

} // namespace render::shaders
