// NOTE: Test framework generated with AI assistance

#include "test.h"
#include "Application.h"
#include <chrono>

namespace ClassGame {
    void runTests()
    {
        static auto last_log_time = std::chrono::steady_clock::now();
        auto current_time = std::chrono::steady_clock::now();
        auto delta_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_log_time);
        
        if (delta_time.count() >= 1)
        {
            DebugInfo("This is an info message.");
            DebugWarn("This is a warning message.");
            DebugError("This is an error message.");
            last_log_time = current_time;
        }
    }
}
