
# Moving Head Simulation Data Generator

## Overview
This C program simulates data for a moving-head sensor board that detects moving or changing objects. It generates test data that can be used to test sensor systems, object tracking, or motion detection.

## Key Functions

### `write_speed`
Converts an object's speed (in meters per second) into a 4-byte float and writes it to a file.

- **Parameters**:
  - `FILE *file`: File pointer to write to.
  - `float speed_mps`: Object speed in meters per second.

- **Output**: Writes the speed as a sequence of 4 hexadecimal bytes.

### `generate_test_data`
Generates test data based on user-defined parameters and writes it to a file.

- **Parameters**:
  - `int iterations`: Number of simulation cycles.
  - `int objects`: Total number of objects to simulate.
  - `int moving_objects`: Number of moving objects in each iteration.
  - `bool noise`: Whether to apply noise to static objects.
  - `bool appear`: Whether objects may randomly appear/disappear.
  - `const char* output_file`: Output file name.

- **Process**:
  - Initializes object positions and speeds.
  - In each iteration:
    - Resets speeds.
    - Randomly moves selected objects.
    - Optionally adds noise to stationary objects.
    - Optionally causes objects to appear/disappear.
    - Writes the magic pattern, packet size, object count, positions, and speeds to the file.

### `print_menu`
Displays the CLI options available.

### `main`
Entry point of the program. Parses command-line arguments and calls `generate_test_data` with those settings.

## Magic Pattern
The sequence `{0x04, 0x05, 0x08, 0x01, 0x02}` marks the start of each data packet.

## Data Format
For each object, the data includes:
- **Position**: `x` and `y` coordinates (each as a 4-byte float).
- **Speed**: A 4-byte float in m/s.

Each line in the file contains:
1. Magic pattern (5 bytes)
2. Packet size (2 bytes, little-endian)
3. Object count (1 byte)
4. For each object:
   - 4 bytes for `x` position
   - 4 bytes for `y` position
   - 4 bytes for speed

## CLI Options

- `-n [iterations]`: Number of iterations (default: 10)
- `-o [objects]`: Number of objects (default: 5)
- `-m [moving_objects]`: Number of moving objects (default: 1)
- `--noise`: Add small random changes to static objects
- `--appear`: Allow objects to randomly appear/disappear
- `--output [file]`: Output filename (default: `test_data.txt`)

## Example

```bash
./main -n 20 -o 10 -m 3 --noise --appear --output test_output.txt
```

---

# Object Position Visualizer (Python)

This Python tool visualizes the movement of objects in XY space using data from a `.txt` file. Each object is shown as a point, and movement direction is visualized using red arrows between frames.

## Requirements

### Python Version
- Python 3.7 or higher

### Required Libraries

Install using pip:

```bash
pip install matplotlib numpy
```

## Usage

1. Make sure your test data (`test_data.txt`) is generated using the C++ program.
2. Place the Python script and `test_data.txt` in the same directory.
3. Run the script:

```bash
python visualizer.py
```

## Project Structure

```bash
your_project_folder/
│
├── visualizer.py        # Visualization script
├── test_data.txt        # Hex data file generated from the C++ program
└── README.md            # This file
```

## What Does It Do?

- Reads each line (frame) of object data.
- Decodes `x` and `y` float32 values.
- Draws each object as a blue dot.
- Calculates the movement vector between frames.
- Draws a red arrow representing movement direction and magnitude.
- Pauses 0.5 seconds between frames for animation.

## Assumptions

- Each frame has the same number of objects in the same order.
- The format strictly follows the structure from the C++ simulation.
