DMX Controller with Joystick for Raspberry Pi Pico

This project is a **DMX controller** using a **Raspberry Pi Pico** to control a moving head light via **DMX-512**. The system uses loops to count up one meter per each cycle, calculates the angles and adjust the spot to light up on the right position. 
## Features

- Sends **DMX-512** signals to control a moving head light
- Supports up to **508 DMX channels**
- Implemented in **C++** using the **Pico SDK**

## Hardware Requirements

- **Raspberry Pi Pico**
- **RS485 Module** (for DMX signal conversion)
- **FunGeneration Pico Spot 20 LED** (or any DMX-compatible moving head light)
- **Wiring & Breadboard**

## Wiring Diagram

VBUS connected to RS485 module and Joystick.
GND connected to RS485 module and Joystick and cable shield  for DMX 

| Component            | Pico GPIO        |
| -------------------- | ---------------- |
| RS485 DI (Data)      | GPIO 0 (UART TX) |
| RS485 DE/RE (Enable) | GPIO 14          |

## Installation & Compilation

### 1. **Set up Pico SDK**

Ensure you have the **Pico SDK** installed on your system. Follow the official Raspberry Pi Pico documentation to set it up.

### 2. **Clone this repository**

```sh
git clone https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot
```
(should be updated later when we want to merge this to our main branch)
### 3. **Build the project**

```sh
mkdir build && cd build
cmake ..
ninja
```

### 4. **Flash the binary to Raspberry Pi Pico**

1. Connect your **Pico in BOOTSEL mode** (hold BOOTSEL while plugging in USB).
2. Copy the generated `controllerDMX.uf2` file to the mounted **RPI-RP2 drive**.

## Usage

Once flashed, the system will:

1. Initialize DMX communication.
2. Read joystick input continuously.
3. Send updated DMX values to control the moving head light.

Open a serial monitor (e.g., **PuTTY**, `minicom`, or `screen`) to see debug output:

```sh
screen /dev/ttyUSB0 115200
```

Expected output:

```
DMX Controller Start
Initializing DMX on GPIO 0...
DMX ready for use!
Joystick values: Azimuth = 128, Elevation = 64
DMX data sent: [0, 128, 64, 255, 150, 100]
```

## Code Overview

The main logic:

- **Enable RS485 transceiver**
- Running loops with increment one meter each cycle
- **Send DMX data frame when transmission is available**

## Future Improvements

- Add **joystick button support** for light mode changes
- Implement **automatic calibration** for joystick drift
- Optimize **DMX update rate** for smoother transitions

## License

This project is open-source under the **MIT License**.