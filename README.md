# CAitSith 3D AI Character Designer

An interactive C++ application designed for AI-driven 3D character creation, digital mesh sculpting, real-time lighting, and industry-standard 3D file export.

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
