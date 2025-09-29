import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    with open(filename, "r") as f:
        return f.readlines()

def hex_to_float(hex_list):
    byte_array = bytearray([int(h, 16) for h in hex_list])
    return np.frombuffer(byte_array, dtype=np.float32)[0]

def parse_line(line):
    parts = line.strip().split()
    magic_len = 5
    packet_size_len = 2
    object_count_index = magic_len + packet_size_len

    object_count = int(parts[object_count_index], 16)
    object_data = parts[object_count_index + 1:]

    positions = []
    for i in range(object_count):
        start = i * 12
        x = hex_to_float(object_data[start:start + 4])
        y = hex_to_float(object_data[start + 4:start + 8])
        # snelheid wordt hier genegeerd, we berekenen die zelf
        positions.append((x, y))

    return positions

def plot_with_velocity_vectors(filename):
    lines = read_data(filename)
    fig, ax = plt.subplots()

    prev_positions = None

    for i, line in enumerate(lines):
        positions = parse_line(line)
        xs, ys = zip(*positions)

        ax.clear()
        ax.set_xlim(0, 3)
        ax.set_ylim(0, 3)
        ax.set_title(f"Iteratie {i + 1}")
        ax.set_xlabel("X (m)")
        ax.set_ylabel("Y (m)")
        ax.grid(True)

        ax.scatter(xs, ys, color='blue')

        if prev_positions and len(prev_positions) == len(positions):
            for (x0, y0), (x1, y1) in zip(prev_positions, positions):
                dx = x1 - x0
                dy = y1 - y0
                ax.arrow(x0, y0, dx, dy, head_width=0.05, head_length=0.07, fc='red', ec='red')

        prev_positions = positions
        plt.pause(0.5)

    plt.show()

# Voer uit
plot_with_velocity_vectors("test_data.txt")
