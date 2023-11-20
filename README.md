# NCD

The Network Connection Discovery Tool (NCD) is a simple, command-line tool developed in C for Windows/Linux platforms. It provides functionality to list active TCP network connections on a Windows/Linux machine.

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
- Windows/Linux Operating System
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
## Use Cases
The Network Connection Discovery Tool (NCD) can be an effective component in testing network security by helping to understand the patterns of network connections, which is essential in identifying potentially malicious activity or unauthorized access. Here's an explanation tailored to the provided scenarios:

![image4-15](https://github.com/yaron4u/NCD/assets/67191566/b3f51796-79c2-4461-be50-657dfe3cf8ef)

### Scenario #1: Multiple Local Addresses to a Single Remote Address
In this scenario, there are two different local IP addresses (IP A and IP B) communicating over the same local port (port X) to the same remote address (IP C) on the same remote port (port Y). This could indicate a number of things in a security context:

- **Load Balancing**: If IPs A and B are part of a server cluster, this might be normal load-balanced traffic to a specific service.
- **Potential Spoofing or Hijacking**: If IP B is not recognized as part of your local infrastructure, it could be a sign of IP spoofing or a hijacked device trying to communicate with a known remote service, attempting to exfiltrate data or engage in a command and control activity.
- **Redundant Connections**: This might also represent multiple services or applications from different servers within the same network communicating with a common external service.

### Scenario #2: A Single Local Address to Multiple Remote Addresses
Here, a single local IP address (IP A) is using the same local port (port X) to communicate with two different remote addresses (IP C and IP D) on different remote ports (port Y and port Z). This might suggest:

- **Normal Operations**: If the local IP is a client or server, it may simply be accessing different services, which is typical behavior for a multitasking system.
- **Distributed Service Access**: The local system might be interacting with different microservices or APIs across the internet.
- **Potential Compromise**: If the remote addresses are unknown or suspicious, this could be an indication of a compromised system reaching out to multiple command and control servers or exfiltrating data to different locations.

In both scenarios, NCD can help to:

- **Detect Anomalies**: By regularly monitoring the active connections, anomalies that deviate from the normal pattern can be detected, which might indicate security issues.
- **Baseline Normal Activity**: Establish a baseline of normal network activity to more easily identify suspicious behavior.
- **Identify Unauthorized Connections**: Spot unexpected external connections that could signify a breach.
- **Support Incident Response**: During a security incident, quickly ascertain the scope of the affected systems by listing active connections.

### Usage in Attack Scenario 
NCD can be used to:

- **Validate Test Traffic**: Ensure that the generated attack traffic is flowing as expected to the target systems.
- **Monitor Defense Efficacy**: Observe how defensive mechanisms (like firewalls or intrusion prevention systems) react to the simulated attacks.
- **Post-Attack Analysis**: After an attack, NCD can provide insights into which connections were made, helping in post-mortem analysis to improve security postures.
---
## Troubleshooting
If you encounter any issues during compilation or running the tool, ensure that:
- Necessary libraries (`ws2_32.lib` and `iphlpapi.lib`) are correctly linked.
- The Windows SDK is properly installed and configured in your development environment.

