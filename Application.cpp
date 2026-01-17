#include "Application.h"
#include "imgui/imgui.h"
#include <vector>
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <chrono>
#include <ctime>

namespace ClassGame {
        //
        // our global variables
        //
        static bool g_LogWindowVisible = true;
        static bool g_AutoScroll = true;
        static std::vector<std::string> g_LogMessages;
        static std::mutex g_LogMutex;

        static std::string CurrentTimestamp()
        {
            using clock = std::chrono::system_clock;
            auto now = clock::now();
            std::time_t t = clock::to_time_t(now);
            std::tm tm;
            #if defined(_WIN32)
                localtime_s(&tm, &t);
            #else
                localtime_r(&t, &tm);
            #endif
            char buf[32];
            std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm);
            return std::string(buf);
        }

        void ConsoleLog(const char* message)
        {
            if (!message) return;
            std::lock_guard<std::mutex> lock(g_LogMutex);
            std::ostringstream oss;
            oss << "[" << CurrentTimestamp() << "] " << message;
            g_LogMessages.emplace_back(oss.str());
        }

        void FileLog(const char* message)
        {
            if (!message) return;
            std::ofstream ofs("app.log", std::ios::app);
            if (!ofs.is_open()) return;
            ofs << "[" << CurrentTimestamp() << "] " << message << '\n';
            ofs.flush();
        }

        void DebugLog(const char* message)
        {
            ConsoleLog(message);
            FileLog(message);
        }

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            DebugLog("Game started successfully");
            DebugLog("Application initialized");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End();

            // Draw our Debug Console
            ShowLogWindow();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }

        void ShowLogWindow(bool* p_open)
        {
            bool* open = p_open ? p_open : &g_LogWindowVisible;
            if (!open) return;

            if (ImGui::Begin("Debug Console", open))
            {
                ImGui::Checkbox("Auto-scroll", &g_AutoScroll);
                ImGui::SameLine();
                if (ImGui::Button("Clear"))
                {
                    std::lock_guard<std::mutex> lock(g_LogMutex);
                    g_LogMessages.clear();
                }

                ImGui::Separator();

                ImGui::BeginChild("LogRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
                {
                    std::lock_guard<std::mutex> lock(g_LogMutex);
                    for (const auto& line : g_LogMessages)
                    {
                        ImGui::TextUnformatted(line.c_str());
                    }
                    if (g_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    {
                        ImGui::SetScrollHereY(1.0f);
                    }
                }
                ImGui::EndChild();
            }
            ImGui::End();
        }

        void ToggleLogWindow()
        {
            g_LogWindowVisible = !g_LogWindowVisible;
        }

        bool IsLogWindowVisible()
        {
            return g_LogWindowVisible;
        }
}
