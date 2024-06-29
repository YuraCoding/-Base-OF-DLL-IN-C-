#include "mylib.h"
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

// Renamed from 'main' to avocid confusion
void logMessage(const string& message) {
    ofstream logFile;
    logFile.open("C:\\sigma.txt", ios::app); // Make sure the path is correct and writable
    logFile << message << endl;
    logFile.close();
}

void MyFunction() {
    logMessage("MyFunction called!");

    // Execute command
    int result = system("cmd.exe /k echo Hello World");
    if (result != 0) {
        logMessage("Command execution failed!");
    }
    else {
        logMessage("Command executed successfully!");
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved) {
    static bool isInitialized = false; // Ensure MyFunction is called only once

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        if (!isInitialized) {
            logMessage("DLL_PROCESS_ATTACH called");
            MyFunction();  // Call MyFunction on DLL attach
            isInitialized = true;
        }
        break;
    case DLL_THREAD_ATTACH:
        logMessage("DLL_THREAD_ATTACH called");
        break;
    case DLL_THREAD_DETACH:
        logMessage("DLL_THREAD_DETACH called");
        break;
    case DLL_PROCESS_DETACH:
        logMessage("DLL_PROCESS_DETACH called");
        break;
    }

    return TRUE;
}
