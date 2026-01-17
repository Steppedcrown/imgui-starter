// NOTE: Test framework generated with AI assistance

#include "test.h"
#include "Application.h"
#include "imgui/imgui.h"

namespace ClassGame {
    void runTests()
    {
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
        ImGui::Begin("Testing Terminal");
        
        if (ImGui::Button("Log Info"))
        {
            DebugInfo("This is an info message.");
        }
        
        if (ImGui::Button("Log Warning"))
        {
            DebugWarn("This is a warning message.");
        }
        
        if (ImGui::Button("Log Error"))
        {
            DebugError("This is an error message.");
        }
        
        ImGui::End();
    }
}
