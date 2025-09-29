
# Manual Movement Simulation with Live Visualization

This project allows you to simulate object movement using your keyboard (`W`, `A`, `S`, `D`) and visualize it live using a Python script. It's useful for testing motion tracking systems, sensor board behavior, or demo purposes.

---

## 🧩 Features

- Control object movement manually via keyboard input (no need to press Enter).
- Write new position + velocity data into a `.txt` file in real-time.
- Visualize object position and velocity vector live using a Python `matplotlib` plot.
- Clean and minimal 2D interface.

---

## 🛠️ Requirements

### C (for manual control program)
- GCC compiler (Linux, macOS, MSYS2 on Windows)
- Standard C libraries

### Python (for live visualization)
- Python 3.7+
- Libraries:
  ```bash
  pip install matplotlib numpy
  ```

---

## 🚀 How to Use

### 1. Compile the C program:

```bash
gcc manual_control.c -o manual_control -lm
```

> On Windows (MSYS2) this also works.

### 2. Run the movement simulator:

```bash
./manual_control manual_output.txt
```

Then use these keys:

| Key | Action        |
|-----|---------------|
| W   | Move up       |
| A   | Move left     |
| S   | Move down     |
| D   | Move right    |
| Q   | Quit program  |

Each movement will append a new line to `manual_output.txt`.

---

### 3. In another terminal: start the live visualizer

```bash
python live_visualizer.py
```

This Python script will:
- Continuously read new lines from `manual_output.txt`
- Plot current position as a blue dot
- Draw a red arrow to indicate movement vector from previous frame

---

## 📂 File Structure

```
your_project/
│
├── manual_control.c         # C program to control object with WASD
├── manual_output.txt        # Data file written by the C program
├── live_visualizer.py       # Python script to visualize in real-time
└── README.md                # This file
```

---

## ✅ Data Format

Each line in `manual_output.txt` follows this structure (hex format):

```
MAGIC  PACKET_SIZE(2B)  OBJECT_COUNT(1B)  X(float32)  Y(float32)  V(float32)
```

For example:

```
04 05 08 01 02 10 00 01 00 00 80 3F 00 00 80 3F 9A 99 99 3F
```

---

## 💡 Tips

- You can adjust movement step size or speed calculation in `manual_control.c`.
- To support multiple objects, extend the structure in both C and Python code.
- For smooth trails, consider storing position history and drawing lines.

---

Enjoy simulating live object movement and tracking it visually!
