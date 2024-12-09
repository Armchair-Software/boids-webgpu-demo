# Boids demo with WebGPU & Emscripten for the Armchair Engine

This is a demonstration of [FlockStorm](https://github.com/VoxelStorm-Ltd/flockstorm) running on the basic WebGPU engine demonstrated in the earlier demos.

This also (incidentally) demonstrates packaging for native platforms with Electron, and building those packages in CI steps.  Those parts aren't necessary for the main demo, however.

For the other demos, see:
- https://github.com/Armchair-Software/webgpu-demo
- https://github.com/Armchair-Software/webgpu-demo2
- https://github.com/Armchair-Software/webgpu-shader-demo
- https://github.com/Armchair-Software/chatgpt-emscripten-demo

![gif](https://github.com/user-attachments/assets/3737d8b8-1263-4802-a50d-ad85d39659d1)

## Live demo
Live demo: https://armchair-software.github.io/boids-webgpu-demo/

This requires Firefox Nightly, or a recent version of Chrome or Chromium, with webgpu and Vulkan support explicitly enabled.  On mobile, Chrome Canary is confirmed to work on phones that support Vulkan 1.3 upwards.

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
