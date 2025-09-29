# Abbreviation list
Note: This list will grow as the development is progressing.

# FMCW (Frequency Modulated Continuous Wave)
FMCW is a radar technique where the frequency of a continuous wave signal is modulated over time. In the case of the TI IWR1642, the frequency modulation is a linear sweep. This is also known as a chirp. Note that other types of frequency sweeps, such as a triangular sweep, exist. Also, note that the TI IWR1642 won't actually transmit a continuous wave but has inter-frame (collection of chirps) processing time, which breaks up the continuous wave. By measuring the frequency shift between the transmitted and received signals, it can determine the distance (range) and velocity of a target.

# IPC (Inter Processor Communication)
IPC is a mechanism that allows application and data path processing chains (DPC) to communicate with each other. The applications and DPC could be located on the same subsystem or different subsystems.

# BPM (Binary Phase Modulation)
BPM is a technique used in FMCW radar (such as on the IWR1642BOOST) to improve virtual antenna separation and increase angular resolution without adding extra hardware antennas. It works by modulating the phase of transmitted chirps on different transmit (TX) antennas, allowing the radar system to separate signals more effectively.
(The IWR1642 can 'ping-pong' between its two TX antennas => see documentation for more info)

BPM Chirping involves modulating the phase of transmitted chirps (frequency-modulated signals) using a binary phase shift (0 or 180 degrees). It is primarily used in MIMO radar systems to improve angular resolution and enhance virtual antenna array formation.

# MIMO (Multiple Input Multiple Output)
- **Multiple Transmit (Tx) and Receive (Rx) Antennas:**
  - A single Tx antenna sends a chirp signal, which reflects off objects and is received by multiple Rx antennas.
  - If there are N_Tx transmit antennas and N_Rx receive antennas, the total number of virtual antennas becomes N_Tx × N_Rx.
- **Creating Virtual Antennas for Higher Resolution:**
  - By using time multiplexing (activating different transmit antennas at different times) or BPM (Binary Phase Modulation), the radar simulates more antennas than it physically has. This increases the radar aperture, allowing better detection of angles and smaller objects.
- **Angle of Arrival (AoA) Estimation:**
  - With more antennas, the radar can use techniques like beamforming and angle estimation algorithms (such as MUSIC or FFT-based AoA estimation) to determine the direction of incoming signals more accurately.

# EDMA (Enhanced Direct Memory Access)
EDMA is a more advanced version of traditional DMA (Direct Memory Access). It is specifically designed for high-performance data movement on TI's embedded processors, including the IWR1642 mmWave radar SoC.
- Move ADC data from radar sensors to memory
- Transfer radar cube data to the DSP for processing
- Send processed data to UART or another interface
- Reduce CPU workload by automating data transfers

# LVDS (Low Voltage Differential Signaling)
LVDS is a high-speed data transmission standard used to transfer large amounts of data efficiently while minimizing power consumption and electromagnetic interference (EMI). In TI mmWave radar sensors, LVDS is mainly used for raw data output, such as streaming ADC (Analog-to-Digital Converter) data directly to an external processor or storage device for offline processing.

### Use cases:
- **Real-time debugging** – View raw ADC data externally.
- **Offline processing** – Capture data for custom DSP algorithms.
- **Testing & validation** – Compare raw vs. processed data.
  (Can be left uninitialized on the TI IWR1642 if LVDS is not used)

# DPM ioctl (Data Path Manager IO Control)
It is a function in the DPM (Data Path Manager) module of the TI mmWave SDK that allows control and configuration of the data processing pipeline.
- Managing the execution of Data Processing Chains (DPCs).
- Handling communication between the Master Subsystem (MSS) and DSP Subsystem (DSS).
- Coordinating the radar processing pipeline after receiving raw ADC data.

DPM is a key part of the mmWave SDK architecture, ensuring that radar data flows smoothly from capture → processing → output.

# CFAR (Constant False Alarm Rate)
**Video explanation:** [YouTube Link](https://www.youtube.com/watch?v=BEg29UuZk6c)

Non-coherent detection.
CFAR is a signal processing technique used in radar systems to detect targets while maintaining a constant false alarm rate, even in varying noise and interference conditions. The IWR1642, which is a millimeter-wave (mmWave) radar sensor from Texas Instruments (TI), uses CFAR algorithms in its DSP (Digital Signal Processor) for object detection.

In the context of the TI IWR1642, CFAR is often applied in Range-Doppler processing to distinguish targets from background noise. The three main types of CFAR algorithms commonly used in TI’s mmWave radar processing are:
- **CFAR_CA (Cell Averaging)**
- **CFAR_CAGO (Cell Averaging Greatest Of)**
- **CFAR_CASO (Cell Averaging Smallest Of)**

