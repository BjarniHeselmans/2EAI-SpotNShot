# [mmWave Demo Visualizer](https://dev.ti.com/gallery/view/mmwave/mmWave_Demo_Visualizer/ver/3.6.0/)
Note, this is the copied information that the webapp will prompt to the user upon opening.

## Steps for Using this App

1. **First-time Setup:**
   - You may be prompted to install a plug-in and the TI Cloud Agent Application.

2. **Power up the mmWave Sensor and Load the mmWave Demo:**
   - The demo is located at: `mmwave_sdk/_<ver>/packages/ti/demo/<platform>/mmw`
   - Refer to the mmWave SDK User Guide for more details.

3. **Connect the Sensor to Your PC via USB:**
   - The app will attempt to auto-detect the COM ports.
   - If auto-detection fails, configure the serial ports manually:
     - **CFG_port:** COM port for `XDS110 Class Application/User UART`, Baud: `115200`
     - **Data_port:** COM port for `XDS110 Class Auxiliary Data port`, Baud: `921600`
   - *Hint:* Check the Windows Device Manager to find the correct COM port numbers.

4. **Connect to the Target:**
   - The app will automatically try to connect.
   - If the connection fails, click the bottom-left corner to retry.

5. **Configure the Sensor:**
   - Go to the **CONFIGURE** tab and select:
     - Frequency Band
     - Platform
     - Plots to visualize (via checkboxes in "Plot Selection")
   - Click **"SEND CONFIG TO MMWAVE DEVICE"** to apply the configuration.
   - Click **"SAVE CONFIG TO PC"** to save the settings.

6. **View Real-Time Data:**
   - Switch to the **PLOTS** tab to see live radar data.
   - The "Real-time Tuning" and "Advanced Commands" tabs allow fine-tuning without stopping the sensor.

7. **Modify Configuration Without Rebooting:**
   - Go back to the **CONFIGURE** tab to change settings.
   - Click **"SEND CONFIG TO MMWAVE DEVICE"** again to apply changes.

## Special Cases & Required Actions

- **If you change the Platform:** Ensure the COM ports match the TI EVM you are configuring.
- **If you change the SDK version:** Ensure the mmWave demo running on the EVM matches the selected SDK version.
- **If you change the Antenna Configuration:** Reboot the TI EVM before sending the new configuration.
- **If the Board is Rebooted:** Restart the process from Step 1.

## Advanced Options

- **Load a Custom Configuration File:**
  - Click **"LOAD CONFIG FROM PC AND SEND"** (found in the PLOTS tab).
  - Ensure the first two commands in the config file are:
    ```
    sensorStop
    flushCfg
    ```

- **Pause and Resume Data Streaming:**
  - Click **"STOP"** to pause sensor operation.
  - Click **"START"** to resume without reconfiguring.

- **Offline Mode:**
  - The online/cloud version is recommended, but an offline version is available under **Help -> Download or Clone Visualizer**.

- **Record Data for Offline Analysis:**
  - Click **"Record Start"** in the PLOTS tab.
  - Refer to the **mmWave Demo Visualizer User's Guide** for details.
  - Ensure your browser meets the requirements for `ti-widget-streamsaver`.

---

This guide summarizes the key steps for using the mmWave Demo Visualizer effectively. 
