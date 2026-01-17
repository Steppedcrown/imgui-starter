// NOTE: Logging system generated with AI assistance

#pragma once

namespace ClassGame {
    void GameStartUp();
    void RenderGame();
    void EndOfTurn();
    
    // Logging window management
    void ShowLogWindow(bool* p_open = nullptr);
    void ToggleLogWindow();
    bool IsLogWindowVisible();

    // Logging outputs
    void ConsoleLog(const char* message);
    void FileLog(const char* message);
    void DebugLog(const char* message);
}
