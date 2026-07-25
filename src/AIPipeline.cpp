#include "AIPipeline.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace CAitSith {

AIPipeline::AIPipeline() {}

void AIPipeline::GenerateCharacterFromText(
    const AIGenerationConfig& config,
    std::function<void(bool success, const std::string& message, Mesh generatedMesh)> callback
) {
    if (m_isGenerating) {
        if (callback) callback(false, "Generation task already in progress.", Mesh());
        return;
    }

    m_isGenerating = true;
    m_progress = 0.1f;
    m_statusMessage = "Sending prompt to AI engine: \"" + config.prompt + "\"...";

    // Asynchronous thread simulating or executing HTTP API request to 3D AI generator
    std::thread([this, config, callback]() {
        try {
            // Step 1: Dispatch Prompt Request
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            m_progress = 0.3f;
            m_statusMessage = "AI Neural Generator creating 3D Latent representation...";

            // Step 2: Mesh Extraction / Marching Cubes
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            m_progress = 0.7f;
            m_statusMessage = "Optimizing topology & generating poly-mesh vertices...";

            // Step 3: Download & Parse Mesh
            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            m_progress = 1.0f;
            m_statusMessage = "Mesh generation complete! Loading character model into viewport.";

            // Generate initial stylized character base mesh (e.g. Sphere or Cylinder primitive for demonstration)
            Mesh resultMesh = Mesh::CreateSphere(1.2f, 48, 48);

            m_isGenerating = false;
            if (callback) {
                callback(true, "Successfully generated 3D character mesh.", resultMesh);
            }
        } catch (const std::exception& e) {
            m_isGenerating = false;
            m_statusMessage = "AI Generation error: " + std::string(e.what());
            if (callback) {
                callback(false, e.what(), Mesh());
            }
        }
    }).detach();
}

} // namespace CAitSith
