# imgui-starter

Using the provided code provided here you have a base Dear IMGUI project for Windows and macOS. There is a basic CMakefile in this project that includes the necessary files to create an application that brings up just a basic screen.

You must add a logging system to this code that you will be using THROUGHOUT the quarter. This logging system should do two things.

It should be able to log to a Dear IMGUI debug console
It should also log its output to a file.

For the submission, make a branch of this repo and submit a new GitHub URL

---

## Logging System Implementation 01/17/26

**Development Platform:** macOS

**Note:** This logging system was developed with AI assistance (GitHub Copilot).

I implemented a logging system with three core functions: ConsoleLog (displays messages in an ImGui window), FileLog (writes to logs/debug.log), and DebugLog (calls both). The system supports three severity levels (Info, Warn, Error) using a messageType struct containing text and color, with color-coded display in the console. The Debug Console includes multi-select filtering via checkboxes, auto-scroll, clear functionality, and clipboard export options. I also created a testing window which currently has buttons for logging different message types to the console and log file, but will serve as a place to test certain parts of the game in the future. I did not ask any clarifying questions to the professor, although I did ask Copilot about the rubrics specifications for message levels which led me to adding the different message types as well as filtering capabilities. All modified files include AI assistance citations as required.
