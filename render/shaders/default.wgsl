struct vertex_input {
  @builtin(instance_index) instance: u32,
  @location(0) position: vec3f,
  @location(1) normal: vec3f,
  @location(2) colour: vec4f,
  @location(3) model_matrix0: vec4f,                                            // reconstruct a mat4x4f from four vec4fs
  @location(4) model_matrix1: vec4f,
  @location(5) model_matrix2: vec4f,
  @location(6) model_matrix3: vec4f,
};

struct vertex_output {
  @builtin(position) position: vec4f,
  @location(1) @interpolate(flat, first) colour: vec4f,
};

struct uniform_struct {
  view_projection_matrix: mat4x4f,
  normal_matrix: mat3x3f,
};

@group(0) @binding(0) var<uniform> uniforms: uniform_struct;

const light_dir = vec3f(0.872872, 0.218218, -0.436436);                         // manually normalised (1.0, 0.25, -0.5)
const ambient = 0.5f;

@vertex
fn vs_main(in: vertex_input) -> vertex_output {
  let model_matrix = mat4x4f(
    in.model_matrix0,
    in.model_matrix1,
    in.model_matrix2,
    in.model_matrix3,
  );

  var out: vertex_output;
  out.position = uniforms.view_projection_matrix * model_matrix * vec4f(in.position, 1.0);
  let transformed_normal = uniforms.normal_matrix * in.normal;

  let diffuse_intensity = (max(dot(transformed_normal, light_dir), 0.0) * (1.0 - ambient)) + ambient;
  out.colour = vec4f(in.colour.rgb * diffuse_intensity, in.colour.a);

  return out;
}

@fragment
fn fs_main(in: vertex_output) -> @location(0) vec4f {
  return in.colour;
}
