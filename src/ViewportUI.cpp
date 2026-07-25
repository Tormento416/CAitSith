#include "ViewportUI.hpp"
#include <iostream>

namespace CAitSith {

ViewportUI::ViewportUI() {}

void ViewportUI::RenderUI(
    Camera& camera,
    LightSource& light,
    Mesh& activeMesh,
    SculptEngine& sculptEngine,
    AIPipeline& aiPipeline
) {
    // Console UI State Representation (ImGui Calls run when window loop and ImGui context are bound)
}

} // namespace CAitSith
