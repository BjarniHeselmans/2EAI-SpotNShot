# Spot&Shot Project

## 🔹 Introduction

**Spot&Shot** is an autonomous light tracking system that uses radar technology to detect and track people in a room. A microcontroller receives the radar data, processes the position information, and then controls a **Fun Generation PicoSpot 20 LED** moving head via **DMX**. This allows the person to be automatically illuminated until they leave the room, without the need for a computer.

---

## 🔹 Project Overview

The **Spot&Shot** system consists of the following components:

1. **Radar Sensor**: Detects and tracks people in the room and transmits position data.
2. **Microcontroller**: Processes the radar data and translates it into DMX commands for the light.
3. **Fun Generation PicoSpot 20 LED**: A moving head controlled via DMX to stay focused on the person.

**Operation**:
- The radar sensor detects a person and determines their coordinates in the room.
- The microcontroller receives this data and converts it into pan and tilt values for the light.
- The PicoSpot 20 LED receives the DMX signals and adjusts its direction to follow the person.

---

## 🔹 Hardware Requirements

### 1. Radar Sensor
A suitable radar sensor that can detect movement and position, for example:
- **Omron D6T** (thermal)
- **RX FX antenna (Texas Instruments IWR164)** (Used in this project)
- **Acconeer A111** (pulse radar)

### 2. Microcontroller
A microcontroller that supports DMX output, such as:
- **ESP32** (with a DMX transceiver like the MAX485)
- **Arduino Mega** + (with a DMX transceiver like the MAX485 & DMX Shield)
- **Raspberry Pi Pico** (with custom DMX libraries & with a DMX transceiver like the MAX485)

### 3. Fun Generation PicoSpot 20 LED
- **Light source**: 12 W CREE high-performance white LED
- **Pan/Tilt range**: 540° pan, 200° tilt
- **DMX connections**: 3-pin XLR (DMX In/Out)
- **DMX modes**: 5, 9, or 11 channels

### 4. DMX Control
- **MAX485 module** for RS485 communication (sending DMX signal via UART)
- **DMX Shield** for compatibility with Arduino/Microcontrollers
- **Standalone DMX cable connection** via XLR to the light

---

## 🔹 Software Installation

### 1. Interpreting Radar Data
- The radar sensor sends **coordinates (X, Y)** to the microcontroller via **UART, SPI, or I2C**.
- Use a **Kalman Filter** or **Moving Average** to reduce noise.
- Calculate the person's position in the room and determine the correct **pan and tilt values** for the light.

### 2. Setting Up DMX Communication
- Use a **DMX library** such as:
  - **Arduino DMXSerial** (for Arduino Mega)
  - **ESP-DMX** (for ESP32)
  - **TeensyDMX** (for Teensy)
- Configure the **DMX output** via **UART**:
  - Connect the **MAX485 transceiver** to the TX pin of the microcontroller.
  - Connect the DMX signal wires with a **3-pin XLR connector** to the light.
  - Set the correct **DMX address settings** on the light (default **address 1**).

### 3. Converting Radar to DMX
- **Translate the X,Y position** of the person to **Pan/Tilt values**:
  - Use a scaling factor to convert coordinates into DMX values (0-255 for 8-bit DMX, 0-65535 for 16-bit DMX).
  - **Pan = X coordinate → DMX channel 1**
  - **Tilt = Y coordinate → DMX channel 2**
- Send DMX signals every **50ms** for smooth movements.

---

## 🔹 Configuration and Testing

1. **Connecting Hardware**:
   - Connect the radar to the microcontroller via UART/SPI/I2C.
   - Connect the DMX output from the microcontroller to the light via **MAX485** and **XLR cable**.
   - Check the power supply for all components.

2. **Testing the Software**:
   - Test the **radar output**: print coordinates in the **serial monitor**.
   - Test the **DMX output**: send fixed values to the light and check the movement.
   - Combine both systems and check if the light correctly follows the person.

3. **Fine-tuning**:
   - **Set threshold values** to avoid false detections.
   - **Add speed limits** so the light does not move too abruptly.
   - **Fail-safe**: when no person is detected, keep the light in a neutral position.

---

## 🔹 References

- **Radar Sensor Documentation**:
  - Omron D6T: [Datasheet](https://www.omron.com/global/en/)
  - Texas Instruments mmWave: [TI mmWave Docs](https://www.ti.com/sensors/mmwave/overview.html)
- **Microcontroller DMX Control**:
  - DMXSerial Library (Arduino): [GitHub](https://github.com/mathertel/DMXSerial)
  - ESP-DMX: [GitHub](https://github.com/Rickgg/ESP-DMX)
- **Fun Generation PicoSpot 20 LED**:
  - User Manual: [Thomann PDF](https://images.thomann.de/pics/atg/atgdata/document/manual/372642_c_372642_en_online.pdf)
- **DMX Theory and Protocol**:
  - DMX512 Standard: [Wikipedia](https://en.wikipedia.org/wiki/DMX512)
  - DMX via MAX485: [Tutorial](https://www.instructables.com/Using-ESP8266-to-Control-DMX-Light/)
