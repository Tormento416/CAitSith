#pragma once

#include <string>
#include <functional>
#include <future>
#include "Mesh.hpp"

namespace CAitSith {

enum class AIProvider {
    Tripo3D,
    Meshy,
    Stability3D,
    LocalONNX
};

struct AIGenerationConfig {
    AIProvider provider{AIProvider::Tripo3D};
    std::string apiKey{""};
    std::string prompt{""};
    int polyCountTarget{10000};
    bool generateTextures{true};
};

class AIPipeline {
public:
    AIPipeline();

    // Async Prompt Generation Request
    void GenerateCharacterFromText(
        const AIGenerationConfig& config,
        std::function<void(bool success, const std::string& message, Mesh generatedMesh)> callback
    );

    // Status Check
    bool IsGenerating() const { return m_isGenerating; }
    float GetProgressPercent() const { return m_progress; }
    std::string GetStatusMessage() const { return m_statusMessage; }

private:
    bool m_isGenerating{false};
    float m_progress{0.0f};
    std::string m_statusMessage{"Idle"};
};

} // namespace CAitSith
