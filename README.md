# Keylogger for Windows

This project is a simple keylogger written in C++ for Windows OS. The application captures every keystroke and logs it to a file.

## Description

Keylogger is a utility for monitoring and recording all keystrokes on a keyboard. This program can be useful for testing keyboards or for other purposes that require tracking keyboard input.

## Features
- Сalculates the interval between pressing a key
- Supports special keys like Shift, Ctrl, Alt, and function keys (F1-F12)
- Saves logs to a specified file
- Adds .exe to the Windows Startup registry

## Requirements
- Windows OS
- Visual Studio
- C++ compiler


## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/feqle/keylogger
   cd keylogger

2.Compile the project (if needed):
 ◦ Open the project in Visual Studio.
 ◦ Сhange the code for yourself , for example the path of files
 ◦ Build the project: Build -> Build Solutionor press Ctrl+Shift+B.
(OR JUST USE THE FINISHED .exe FILE  - "keylogger.exe")

## Usage
 1. Run keylogger.exe
 2. The program will start tracking and logging all keystrokes to the logs.txt file(or to the file that you specified in the code) .

## Contributing
If you would like to contribute to the project, please create a pull request or open an issue for discussion.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.
