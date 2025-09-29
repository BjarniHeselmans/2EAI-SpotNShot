## Use the mmWave demo without the Demo visualizer web app:

### 1.) Use TeraTerm terminal with a parsing script (macro .ttl):
Download TeraTerm terminal:  
[GitHub - TeraTermProject](https://github.com/TeraTermProject/osdn-download/releases)  
(Other terminals don't seem to handle the high baudrate of 921600 for the radar data. There should exist a parser Macro script (.ttl) to translate the received binary data from the sensor to readable text that TeraTerm can use, which other terminals cannot.)

1. Open a terminal on the Application/User UART COM port at baudrate **115200** to send the configuration commands.
2. Open a terminal on the Auxiliary Data COM port at baudrate **921600**.
3. Configure the TI IWR1642 by sending commands over the Application/User COM port.
   - All possible configuration commands need to be sent before `sensorStart` can be sent.
   - Partial configuration is not allowed when the TI IWR1642 is started for the first time.
   - Read the **mmWave SDK user guide** for more details.
   - Example configuration files can be found in the SDK installation folder:
     ```
     C:\ti\mmwave_sdk_03_06_02_00-LTS\packages\ti\demo\xwr16xx\mmw\profiles
     ```
4. Configure the TeraTerm serial terminal to use the macro .ttl file:
   - **TO DO:** Find the .ttl file to enable real-time translation of received radar data.
5. The data should now be printed in a readable format.

---

### 2.) Record a .dat file and parse it with the shipped parser scripts (.py):

#### **Recording a .dat file using the mmWave Demo visualizer:**
1. Open the visualizer web app.
2. Connect to the device.
3. Set the configurations and send them to the TI IWR1642.
4. Open the **Plots** tab.
5. Perform any additional tuning if required.
6. Configure the desired max recording period.
7. Start recording and wait for the time to expire or manually stop it.
8. The `.dat` file should download automatically (sometimes it may not download correctly).
9. Example: `xwr16xx_processed_stream.dat` (3s recording example).

#### **Parsing the .dat file:**
Python scripts to parse `.dat` files are included in the demo application.

- **Script location:**
  ```
  C:\ti\mmwave_sdk_03_06_02_00-LTS\packages\ti\demo\parser_scripts
  ```
- **Main script:** `mmw_demo_example_script.py`
- **Command to invoke the parser:**
  ```
  python3 mmw_demo_example_script.py <recorded_dat_file_from_Visualizer>.dat
  ```
  *(If `python3` is not recognized, try using `python` instead.)*

#### **Saving parsed data:**
To write output to a file:
```cmd
python3 mmw_demo_example_script.py <recorded_dat_file_from_Visualizer>.dat > output.txt
```
For appending instead of overwriting:
```cmd
python3 mmw_demo_example_script.py <recorded_dat_file_from_Visualizer>.dat >> output.txt
```

---

### 3.) UART Data capture without using the mmWave Demo visualizer app:

#### **Using the AR_MSS_LOGGER, AR_RS232TX, and AR_RS232RX pins:**  
**Note:** Seems impossible on the **TI IWR1642BOOST RevB** board.

- **AR_MSS_LOGGER:** J5 connector R26 → Processed radar data
- **AR_RS232TX:** J6 connector R169 → User CLI commands
- **AR_RS232RX:** J6 connector R166 → TI IWR1642 CLI responses or other debug messages
- **Forum post reference:** [TI E2E Forum](https://e2e.ti.com/support/sensors-group/sensors/f/sensors-forum/668271/iwr1642boost-reading-the-uart-part-without-usb)

**Issue:**
- The board schematics and assembly files state these resistors should remain unpopulated.
- The board assembly file does not show these resistors, meaning they are likely not routed on the board.

#### **Probing these pins:**
These pins connect to the onboard **TM4C1294NCPDTT3 (ARM-based microcontroller) XDS110 emulator**:
- **AR_MSS_LOGGER:** R136
- **AR_RS232TX:** R128
- **AR_RS232RX:** R129

**Limitations:**
- Direct access to these lines is **not possible** unless wires are soldered at these resistors.
- Debug probing is possible.
- **TO DO:** Test probing these pins with an oscilloscope.

---

### 4.) I2C/SPI Data capture:

#### **TO DO:**
- Figure out how to initialize and configure these communication modules.
  - Check GPIO and UART demo code.
- Figure out how to disable the UART data port and send data over I2C/SPI.
- Determine if the CLI can receive configuration commands via I2C/SPI.
  - Alternative: Use a fixed configuration at sensor startup (not ideal for fine-tuning as each change requires recompiling and flashing new firmware).
