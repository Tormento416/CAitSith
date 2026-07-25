#pragma once

#include "Camera.hpp"
#include "Lighting.hpp"
#include "Mesh.hpp"
#include "SculptEngine.hpp"
#include "AIPipeline.hpp"

namespace CAitSith {

class ViewportUI {
public:
    ViewportUI();

    // Render ImGui Control Panels
    void RenderUI(
        Camera& camera,
        LightSource& light,
        Mesh& activeMesh,
        SculptEngine& sculptEngine,
        AIPipeline& aiPipeline
    );

    // Prompt Buffer Access
    const char* GetPromptText() const { return m_promptBuffer; }

private:
    char m_promptBuffer[512]{"Cyberpunk warrior character with detailed samurai armor"};
    char m_filepathBuffer[256]{"character_output.obj"};
    char m_apiKeyBuffer[128]{""};

    int m_selectedProvider{0};
    int m_polyCountTarget{15000};
    int m_selectedPrimitive{0};
};

} // namespace CAitSith
