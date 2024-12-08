# Boids demo with WebGPU & Emscripten for the Armchair Engine

This is a demonstration of [FlockStorm](https://github.com/VoxelStorm-Ltd/flockstorm) running on the basic WebGPU engine demonstrated in the earlier demos.

For the previous demos, see:
- https://github.com/Armchair-Software/webgpu-demo
- https://github.com/Armchair-Software/webgpu-demo2

![image](https://github.com/user-attachments/assets/6e757524-1334-420f-991d-7d8a4445eeb4)

## Live demo
Live demo: https://armchair-software.github.io/boids-webgpu-demo/

This requires Firefox Nightly, or a recent version of Chrome or Chromium, with webgpu and Vulkan support explicitly enabled.

## Dependencies
- [FlockStorm](https://github.com/VoxelStorm-Ltd/flockstorm) (included)
- [Emscripten](https://emscripten.org/)
- CMake
- [VectorStorm](https://github.com/Armchair-Software/vectorstorm) (included)
- [LogStorm](https://github.com/VoxelStorm-Ltd/logstorm) (included)
- [MemoryStorm](https://github.com/VoxelStorm-Ltd/memorystorm) (included)
- [magic_enum](https://github.com/Neargye/magic_enum) (included)
- [dear imgui](https://github.com/ocornut/imgui) with the proposed `imgui_impl_emscripten` backend (included)

## Building
The easiest way to assemble everything (including in-tree shader resource assembly) is to use the included build script:
```sh
./build.sh
```

To launch a local server and bring up a browser:
```sh
./run.sh
```

For manual builds with CMake, and to adjust how the example is run locally, inspect the `build.sh` and `run.sh` scripts.
