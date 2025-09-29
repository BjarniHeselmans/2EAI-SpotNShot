
# Usage Guide for Movement Simulation Tools

This guide describes how to use two systems for simulating object motion and visualizing it in real-time.

---

## Contents

1. [C Payload Generator (Automatic)](#1-c-payload-generator-automatic)
2. [Manual Control Generator (Interactive with Python Live Plot)](#2-manual-control-generator-interactive)

---

## 1. C Payload Generator (Automatic)

This tool generates multiple iterations of object motion data automatically using configurable parameters.

### Build Instructions

```bash
gcc payload_generator.c -o payload_generator.exe
```

Or with g++ if using C++:

```bash
g++ payload_generator.cpp -o payload_generator.exe
```

### Usage

```bash
./payload_generator.exe [options]
```

### ⚙️ CLI Options

| Option             | Description                                                |
|--------------------|------------------------------------------------------------|
| `-n [iterations]`  | Number of frames to generate (default: 10)                |
| `-o [objects]`     | Number of objects to simulate (default: 5)               |
| `-m [moving_objs]` | Number of objects that move per frame (default: 1)       |
| `--noise`          | Add noise to static objects                               |
| `--appear`         | Randomly make objects appear/disappear                    |
| `--output [file]`  | Output file name (default: `test_data.txt`)              |

### 💡 Example

```bash
./payload_generator -n 50 -o 5 -m 2 --noise --appear --output test_data.txt
```

---

## 2. Manual Control Generator (Interactive)

This tool allows you to control object movement with your keyboard (`W`, `A`, `S`, `D`) and log the motion data live. A Python script visualizes the movement in real time.

### Compile C Manual Control Tool

```bash
gcc manual_control.c -o manual_control.exe -lm
```

### Run the Simulator

```bash
./manual_control.exe manual_output.txt
```

#### Controls

| Key | Action        |
|-----|---------------|
| W   | Move up       |
| A   | Move left     |
| S   | Move down     |
| D   | Move right    |
| Q   | Quit program  |

Each key press appends a new data line to `manual_output.txt`.

---

### Start Live Python Visualizer

In a second terminal:

```bash
python Visu.py
```

This script will:
- Continuously read `manual_output.txt`
- Plot the object's position
- Draw an arrow indicating movement direction

### Works in Real-Time

Both programs run concurrently:
- One writes movement
- One reads and visualizes it live

---

## Data Format for Both Systems

Each data line follows this hex layout:

```
MAGIC(5B) PACKET_SIZE(2B) OBJECT_COUNT(1B) X(4B float) Y(4B float) V(4B float)
```

---

## Example File Layout

```
movement_project/
├── payload_generator.cpp     # Automatic data generator
├── manual_control.c          # Manual interactive movement
├── test_data.txt             # Output from payload_generator
├── manual_output.txt         # Output from manual control
├── Visu.py                   # Python live plot
├── README.md                 # Documentation
└── USAGE_GUIDE.md            # This file
```

---

## Summary

| Generator        | Input Style     | Output              | Visualization |
|------------------|------------------|----------------------|----------------|
| payload_generator | Automatic params | `test_data.txt`     | Python post-process |
| manual_control    | Interactive keys | `manual_output.txt` | Python live-view     |
