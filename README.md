# NCD

The Network Connection Discovery Tool (NCD) is a simple, command-line tool developed in C for Windows platforms. It provides functionality to list active TCP network connections on a Windows machine.

---
## **Disclaimer**

This script is developed for educational and research purposes only.

**By using this code, you agree to the following:**

1. You will not use this code, in whole or in part, for malicious intent, including but not limited to unauthorized mining on third-party systems.
2. You will seek explicit permission from any and all system owners before running or deploying this code.
3. You understand the implications of running mining software on hardware, including the potential for increased wear and power consumption.
4. The creator of this script cannot and will not be held responsible for any damages, repercussions, or any negative outcomes that result from using this script.

If you do not agree to these terms, please do not use or distribute this code.

---
## Features
- Lists all active TCP connections.
- Displays local and remote addresses along with their respective ports.
- Shows the state of each TCP connection.
- Simple command-line interface for ease of use.

---
## Requirements
- Windows Operating System
- GCC Compiler for Windows (MinGW or similar)
- Windows Software Development Kit (SDK) for access to necessary libraries and headers.

---
## Installation and Compilation
1. **Clone the repository using:**
```
git clone https://github.com/yaron4u/NCD
```
2. **Compilation:**
   Navigate to the directory containing the source code in your command prompt or terminal. Compile the code using the following command:
   ```
   gcc NCD.c -o NCD -lws2_32 -liphlpapi
   ```

## Usage
After compiling the tool, run it using the command line:
```
./NCD.exe
```
The tool will display a list of all active TCP connections including the local and remote addresses, ports, and the state of each connection.

---
## Troubleshooting
If you encounter any issues during compilation or running the tool, ensure that:
- You are using a compatible Windows environment.
- Necessary libraries (`ws2_32.lib` and `iphlpapi.lib`) are correctly linked.
- The Windows SDK is properly installed and configured in your development environment.

