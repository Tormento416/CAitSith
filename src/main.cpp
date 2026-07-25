#include <iostream>
#include <memory>
#include <string>

#include "Camera.hpp"
#include "Lighting.hpp"
#include "Mesh.hpp"
#include "SculptEngine.hpp"
#include "AIPipeline.hpp"
#include "ViewportUI.hpp"

using namespace CAitSith;

int main(int argc, char** argv) {
    std::cout << "====================================================\n";
    std::cout << "          CAitSith 3D AI Character Designer        \n";
    std::cout << "====================================================\n\n";

    // 1. Initialize Viewport Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f);
    std::cout << "[1/5] Initialized Orbit Camera (Target: [0,0,0], Distance: 5.0).\n";

    // 2. Initialize Light Source
    LightSource light;
    light.position = glm::vec3(4.0f, 5.0f, 4.0f);
    std::cout << "[2/5] Light Source configured at position (" 
              << light.position.x << ", " << light.position.y << ", " << light.position.z << ").\n";

    // 3. Initialize Base Poly-mesh
    Mesh activeMesh = Mesh::CreateSphere(1.0f, 32, 32);
    std::cout << "[3/5] Base 3D Sphere Poly-Mesh created (" 
              << activeMesh.GetVertices().size() << " vertices, " 
              << activeMesh.GetIndices().size() / 3 << " triangles).\n";

    // 4. Initialize Digital Sculpting Engine
    SculptEngine sculptEngine;
    sculptEngine.SetTool(SculptTool::Clay);
    sculptEngine.SetRadius(0.6f);
    sculptEngine.SetStrength(0.25f);
    std::cout << "[4/5] Digital Sculpting Engine loaded (Active Tool: Clay, Radius: 0.6, Strength: 0.25).\n";

    // 5. Initialize AI Generation Pipeline
    AIPipeline aiPipeline;
    std::cout << "[5/5] AI Text-to-3D Pipeline engine initialized.\n\n";

    // Demonstration of Interactive Mesh Operations
    std::cout << "----------------------------------------------------\n";
    std::cout << "Executing Test 3D Sculpting Operations...\n";
    
    // Test Raycast & Clay Brush application at origin
    Ray ray{ glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f) };
    bool hit = sculptEngine.ApplyTool(activeMesh, ray);
    if (hit) {
        std::cout << " -> Applied Clay brush stroke at ray intersection.\n";
        std::cout << " -> Vertices recalculated with updated smooth normals.\n";
    }

    // Export initial demo mesh
    std::string exportPath = "demo_character.obj";
    if (activeMesh.SaveToOBJ(exportPath)) {
        std::cout << " -> Saved mesh export to '" << exportPath << "'.\n";
    }

    // AI Generation Prompt Demo
    std::cout << "\n----------------------------------------------------\n";
    std::cout << "Testing AI Text-to-3D Generation Dispatch...\n";
    AIGenerationConfig aiConfig;
    aiConfig.prompt = "Futuristic cybernetic paladin warrior with ornate armor";
    
    aiPipeline.GenerateCharacterFromText(aiConfig, [](bool success, const std::string& msg, Mesh newMesh) {
        if (success) {
            std::cout << "\n[AI Callback] " << msg << "\n";
            std::cout << "[AI Callback] Generated character mesh with " 
                      << newMesh.GetVertices().size() << " vertices.\n";
        } else {
            std::cout << "\n[AI Callback Error] " << msg << "\n";
        }
    });

    std::cout << "\nCAitSith framework startup sequence complete!\n";
    std::cout << "====================================================\n";

    return 0;
}
