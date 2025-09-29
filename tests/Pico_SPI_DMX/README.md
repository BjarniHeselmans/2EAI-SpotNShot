# DMX controlling with Raspberry Pi PICO over SPI

This project implements a **DMX-controller** using a **Raspberry Pi Pico**, designed to control a moving head light. the system uses a **5-channel DMX protocol**, and the Pico operates exclusively in **SPI slave mode.**  

It receives a data packets from the [TI IWR1642BOOST ](https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot/blob/master/docs/IWR1642BOOST/datasheets/IWR1642BOOST.pdf) , with the data format described here: [IWR to Pico](https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot/blob/master/docs/standards/iwr_to_pico.md). 

You can also test the setup using another microcontroller or the [Pico master emulator](https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot/tree/master/tests/pico-master-emulator) made for an Raspberry Pi Pico which operates as **SPI master**. 

# Features 
- Sends **DMX-512** signals to control a moving head light
- Receives azimuth, elevation and speed values over **SPI**
- Supports up to **508 DMX channels**
- Implemented in **C++** using the **Pico SDK**
## Hardware Requirements

- **Raspberry Pi Pico** (SPI Slave)
- **RS485 Module** (for DMX signal conversion)
- **FunGeneration Pico Spot 20 LED** (or any DMX-compatible moving head light)
- **Wiring & Breadboard**
- TI IWR1642BOOST (or any SPI master sending compatible data)

___
## Wiring Diagram

| Component       | Pico GPIO                                                                      |
| --------------- | ------------------------------------------------------------------------------ |
| RS485 DI (Data) | GPIO 0 (UART TX)                                                               |
| RS485 DE/RE     | GPIO 14                                                                        |
| SPI MISO        | GPIO 16                                                                        |
| SPI CS (Slave)  | GPIO 17                                                                        |
| SPI SCK         | GPIO 18                                                                        |
| GND             | GND (shared with RS485 and cable shield and shared with other microcontroller) |
| VBUS            | Power supply for RS485                                                         |

___
## Installation & Compilation

### 1. **Set up Pico SDK**

Follow the [official Raspberry Pi Pico documentation](https://www.raspberrypi.com/documentation/pico-sdk/) to install the SDK and toolchain.

### 2. **Clone this repository**


```sh
git clone https://github.com/PXLDigital/2EAI-PEN-2425-SpotNShot
cd 2EAI-PEN-2425-SpotNShot
```

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

After flashing:

1. The Pico initializes DMX communication.    
2. It waits for SPI data from the master.
3. Parses azimuth and elevation values.
4. Sends corresponding DMX signals to the moving head light.

___
