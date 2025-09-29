# TI IWR1642 Tools: 
Note: Leave all install folders at their default locations

## 1.) Software:
- **Code Composer Studio (CCS)**
- **Radar Toolbox version ...**
  - CCS prompts to install the correct version of Radar Toolbox when opening a demo example for the first time.
- **mmWave SDK 3.6.0.0-LTS** (xWR6843, xWR6443, xWR1843, and xWR1642):
  - After installing the SDK, open Code Composer Studio.
  - Go to *File -> Preferences -> Code Composer Studio Settings*.
  - Navigate to *General -> Products -> Discovered Products* and click the refresh icon.
  - Now Code Composer Studio is able to see the SDK and other installed tools.
- **Uniflash** (Used for flashing release builds (.out file); debug builds can be flashed using Code Composer Studio itself.)

### Drivers:
- **XDS110 Debug Probe:** JTAG debugging & flashing  
  - TI XDS110 Drivers (Should come with Code Composer Studio)
- **CP2105 USB-to-UART:** Radar data to PC / Serial communication (PuTTY, mmWave Visualizer)  
  - Silicon Labs CP2105 Drivers

### Visualizer App: (Used in combination with the TI demo projects)
- [mmWave Demo Visualizer (Version 3.6.0)](https://dev.ti.com/gallery/view/mmwave/mmWave_Demo_Visualizer/ver/3.6.0/)
- The visualizer version needs to be compatible with the installed mmWave SDK version.

### TICloudAgent Bridge:
- Chrome browser extension used for the visualizer app.
- Prompted to install the first time the visualizer is used.

### TI Cloud Agent Application:
- Used for the visualizer app.
- Prompted to download and install the first time the visualizer is used.

## 2.) Hardware: 
(source: ChatGPT)

### 1. Using the IWR1642BOOST Alone (No Additional Hardware Required)
✅ You can read RF sensor data directly using:
- The onboard UART (over USB, via the CP2105 USB-to-UART bridge).
- The mmWave SDK (TI's demo firmware) which outputs raw radar data over UART.
- mmWave Demo Visualizer (a GUI tool that can display radar point cloud data in real-time).
- Custom software that reads UART output.

🚀 **How?**
- Connect the IWR1642BOOST via USB (with power from the 5V barrel jack).
- Run TI’s mmWave Demo Visualizer or use Python, MATLAB, or a C program to capture and process the raw radar data from UART.

### 2. When You Need the MMWAVE-DEVPACK
🔹 The **MMWAVE-DEVPACK** is only needed for advanced debugging and raw data capture.
- Provides a higher-bandwidth data interface (LVDS) for directly capturing raw ADC samples from the RF front end.
- Required if you want to record raw I/Q radar data for advanced post-processing.
- Needed for debugging with external tools (like JTAG) beyond the built-in debugger.

❌ **You do NOT need the MMWAVE-DEVPACK** if you're just reading processed sensor data from the IWR1642BOOST.

### 3. When You Need a LaunchPad
🔹 A TI **LaunchPad** is not required for standard operation, but you may want one if:
- You need to interface the IWR1642BOOST with another MCU (like an MSP430 or TM4C).
- You're building a custom embedded system where a separate microcontroller will process radar data.

❌ **If you're working with a PC via USB, you do NOT need a LaunchPad.**

