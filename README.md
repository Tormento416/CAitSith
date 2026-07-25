# CAitSith 3D AI Character Designer

An interactive C++ application designed for AI-driven 3D character creation, digital mesh sculpting, real-time lighting, and industry-standard 3D file export.

---

## 🖥️ Platform Compatibility & System Requirements

**CAitSith** is designed from the ground up to be **100% Cross-Platform**. Rebuilding or running the engine across different operating systems requires zero code modifications.

### Supported Operating Systems & Compilers

| Platform | Supported Versions | Recommended Compiler | Windowing & Input Driver |
| :--- | :--- | :--- | :--- |
| **Windows** | Windows 10, Windows 11 (64-bit) | **MSVC** (Visual Studio 2019/2022), **MinGW-w64**, or **Clang** | Native Win32 / GLFW |
| **macOS** | macOS 10.14+ (Intel & Apple Silicon M1/M2/M3/M4) | **Apple Clang** (Xcode Command Line Tools) | Cocoa / OpenGL Bridge |
| **Linux** | Ubuntu, Fedora, Arch, Debian, Manjaro, etc. | **GCC** (GCC 7+) or **Clang** | X11 / Wayland / Mesa / NVIDIA |
| **WSL / WSL2** | Ubuntu / Debian via WSLg | **GCC 15.2+** / **Clang** | Mesa / X11 / Wayland display |

### Minimum Hardware Requirements
* **Processor**: Intel, AMD, or ARM64 (Apple Silicon M-series) 64-bit CPU.
* **Graphics**: Any GPU supporting OpenGL 3.3 Core Profile (Intel HD 4000+, NVIDIA GTX 400+, AMD Radeon HD 5000+, Apple Silicon).
* **RAM**: 2 GB minimum (4 GB+ recommended for high poly-count sculpting).
* **Storage**: 100 MB available space.

---

## 🏛️ Application Architecture

The software is structured into five core modular systems:

1. **3D Orbit Camera (`Camera.hpp / Camera.cpp`)**:
   - 360-degree Orbit, Pitch/Yaw rotation, Pan, and Zoom functionality.
   - Calculates dynamic View and Perspective projection matrices.

2. **Light Control System (`Lighting.hpp`)**:
   - Directional light source position manipulation in 3D space.
   - Configurable ambient, diffuse, and specular Phong lighting.

3. **Poly-Mesh Engine (`Mesh.hpp / Mesh.cpp`)**:
   - Vertex, Normal, UV coordinates data structure.
   - Primitives generators (Sphere, Cube, Cylinder).
   - Dynamic per-vertex normal recalculations.
   - File I/O for **Wavefront `.obj`** and **3D Printing `.stl`** formats.

4. **Digital Sculpting Suite (`SculptEngine.hpp / SculptEngine.cpp`)**:
   - Möller–Trumbore ray-triangle mesh hit testing.
   - **Clay / Inflate Brush**: Pushes vertices along surface normals.
   - **Smooth Brush**: Averages neighboring vertex positions.
   - **Flatten Brush**: Projects local geometry onto target plane.
   - **Grab / Move Brush**: Translates vertices within falloff radius.
   - **Trim / Slice Plane**: Cuts geometry along a cutting plane.

5. **AI Text-to-3D Pipeline (`AIPipeline.hpp / AIPipeline.cpp`)**:
   - Asynchronous dispatch for cloud 3D generation APIs (Tripo3D, Meshy, Stability AI 3D).
   - Generates high-quality poly-mesh base models from natural text prompts.

---

## 🛠️ Building & Running

### Prerequisites
* **C++ Compiler**: MSVC (Visual Studio 2022 / Build Tools), Clang, or GCC (C++17 support).
* **Build System**: CMake 3.16+.

### Build Commands
```bash
# Generate build files
cmake -B build -S .

# Compile target
cmake --build build --config Release

# Run executable
./build/bin/Release/CAitSith.exe
```
