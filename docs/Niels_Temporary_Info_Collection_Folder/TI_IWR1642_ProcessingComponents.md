# TI IWR1642 Subsystems

## 1.) MSS (Master Subsystem: ARM Cortex R4F)  
*Reference: TI IWR1642 Datasheet, page 64*

The **Master Subsystem (MSS)** controls all the device peripherals and housekeeping activities. It contains:
- A **Cortex-R4F processor**
- Associated peripherals and housekeeping components (DMA, CRC, etc.)
- **Peripheral interfaces:** I2C, UART, SPI, CAN, PMIC clocking module, PWM, and more
- Connected to the **Master Interconnect** through the **Peripheral Central Resource (PCR interconnect)**

---

## 2.) DSS (Digital Signal Processing Subsystem: C674x DSP)  
*Reference: TI IWR1642 Datasheet, page 64*

The **DSP Subsystem (DSS)** contains:
- A **high-performance C674x DSP**
- A **high-bandwidth interconnect** for high-speed data transfer (128-bit, 200MHz)
- **Associated peripherals:**
  - Four **DMAs** for data transfer
  - **LVDS interface** for measurement data output
  - **L3 Radar Data Cube Memory**
  - **ADC Buffers**
  - **CRC Engine**
  - **Data Handshake Memory**

### Key Components:
| Component  | Purpose |
|------------|---------------------------------------------------------------|
| **DPU (Data Processing Unit)** | Performs low-level radar processing tasks (FFT, CFAR, Doppler estimation, AoA). |
| **DPC (Data Path Chain)** | Groups multiple DPUs into a functional processing module (e.g., range processing, object detection). |
| **DPM (Data Path Manager)** | Orchestrates DPCs, manages task execution, and inter-process communication. |

---

## 3.) HSRAM (High-Speed RAM)

The **HSRAM** is an **on-chip fast memory** used for storing intermediate radar data and speeding up processing.
### Used for:
- **Radar ADC Data** – Raw samples from the RF front-end.  
- **Range FFT & Doppler FFT results** – Intermediate signal processing data.  
- **CFAR Detection Output** – Potential object locations.  
- **Object Tracking Data** – Position, velocity, and other tracked information.  

Since HSRAM has **low latency and high bandwidth**, it allows the DPUs to efficiently perform **real-time processing**.

---

## 4.) + 5.) + 6.) RSS (Radar Subsystem)

### 4.) BSS (Baseband Subsystem)
The **BSS (Baseband Subsystem)** is a **firmware component** running on the **Radar Hardware Accelerator (R4F Cortex-M4)**.
### Responsibilities:
- **Chirp sequencing** – Manages radar signal transmission patterns.  
- **ADC data capture** – Collects reflected radar signals.  
- **Data transfer** – Moves captured data for further processing.  

- The **BSS firmware** is provided **precompiled** by TI in the **mmWave SDK**.
- It communicates with the **MSS (Master Subsystem)** and **DSS (DSP Subsystem)** to send **processed radar data**.

---

### 5.) RF and Analog Subsystem
This subsystem is the **physical hardware** that generates and transmits the **mmWave signals**.

| Component | Purpose |
|------------|---------------------------------------------------------------|
| **PLL (Phase-Locked Loop)** | Generates radar transmission frequencies. |
| **TX Antennas** | Send out radar signals. |
| **RX Antennas** | Receive the reflected signals. |
| **ADC (Analog-to-Digital Converter)** | Converts received analog signals into digital data. |
| **LNA (Low Noise Amplifier), Mixers, Filters** | Enhance and process signals before ADC conversion. |

---

### 6.) Hardware Accelerators
The **hardware accelerators** are designed for **efficient signal processing**.
- **FFT processing** – Computes frequency-domain transformations.  
- **Filtering** – Reduces noise and enhances signal quality.  
- **Radar signal computations** – Speeds up processing tasks to enable real-time operation.

---

**Summary:** The IWR1642 includes a well-structured architecture with distinct processing subsystems, dedicated hardware accelerators, and efficient memory management, making it ideal for **real-time radar signal processing and object detection**.

