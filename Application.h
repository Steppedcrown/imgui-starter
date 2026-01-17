// NOTE: Logging system generated with AI assistance

#pragma once
#include "imgui/imgui.h"

namespace ClassGame {
    struct messageType {
        const char* text;
        ImVec4 color;
    };

    // Default message type: [INFO] with white text
    static const messageType MESSAGE_TYPE_INFO = {"[INFO]", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)};
    static const messageType MESSAGE_TYPE_WARN = {"[WARN]", ImVec4(1.0f, 1.0f, 0.0f, 1.0f)};
    static const messageType MESSAGE_TYPE_ERROR = {"[ERROR]", ImVec4(1.0f, 0.0f, 0.0f, 1.0f)};

    void GameStartUp();
    void RenderGame();
    void EndOfTurn();
    
    // Logging window management
    void ShowLogWindow(bool* p_open = nullptr);
    void ToggleLogWindow();
    bool IsLogWindowVisible();

    // Logging outputs
    void ConsoleLog(const char* message, const messageType& type = MESSAGE_TYPE_INFO);
    void FileLog(const char* message);
    void DebugLog(const char* message, const messageType& type = MESSAGE_TYPE_INFO);

    // Convenience functions for different severity levels
    void DebugInfo(const char* message);
    void DebugWarn(const char* message);
    void DebugError(const char* message);
}
