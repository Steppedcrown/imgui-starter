#include "Application.h"
#include "imgui/imgui.h"
#include <vector>
#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <chrono>
#include <ctime>
#include <filesystem>

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

        static std::string GetProjectRoot()
        {
            std::string file_path = __FILE__;
            size_t pos = file_path.find_last_of("/\\");
            if (pos == std::string::npos) return ".";
            return file_path.substr(0, pos);
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

            namespace fs = std::filesystem;
            static std::string project_root = GetProjectRoot();
            std::string log_dir = project_root + "/logs";
            
            // Create logs directory if it doesn't exist
            if (!fs::exists(log_dir))
            {
                fs::create_directory(log_dir);
            }

            std::string log_file = log_dir + "/debug.log";
            std::ofstream ofs(log_file, std::ios::app);
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

            ImGui::SetNextWindowSize(ImVec2(500, 250), ImGuiCond_FirstUseEver);
            if (ImGui::Begin("Debug Console", open))
            {
                ImGui::Checkbox("Auto-scroll", &g_AutoScroll);
                ImGui::SameLine();
                if (ImGui::Button("Clear"))
                {
                    std::lock_guard<std::mutex> lock(g_LogMutex);
                    g_LogMessages.clear();
                }

                ImGui::SameLine();
                if (ImGui::Button("Copy last to clipboard"))
                {
                    std::string last;
                    {
                        std::lock_guard<std::mutex> lock(g_LogMutex);
                        if (!g_LogMessages.empty())
                            last = g_LogMessages.back();
                    }
                    if (!last.empty())
                    {
                        ImGui::LogToClipboard();
                        ImGui::LogText("%s", last.c_str());
                        ImGui::LogFinish();
                    }
                }

                ImGui::SameLine();
                if (ImGui::Button("Copy all to clipboard"))
                {
                    std::string all;
                    {
                        std::lock_guard<std::mutex> lock(g_LogMutex);
                        if (!g_LogMessages.empty())
                        {
                            for (const auto& line : g_LogMessages)
                            {
                                all += line;
                                all += '\n';
                            }
                        }
                    }
                    if (!all.empty())
                    {
                        ImGui::LogToClipboard();
                        ImGui::LogText("%s", all.c_str());
                        ImGui::LogFinish();
                    }
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
