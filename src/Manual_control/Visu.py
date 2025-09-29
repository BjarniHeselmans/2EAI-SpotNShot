import matplotlib.pyplot as plt
import numpy as np
import time
import os

def hex_to_float(hex_list):
    byte_array = bytearray([int(h, 16) for h in hex_list])
    return np.frombuffer(byte_array, dtype=np.float32)[0]

def read_last_frame(filename, last_index):
    with open(filename, "r") as f:
        lines = f.readlines()
        if last_index < len(lines):
            line = lines[last_index].strip().split()
            if len(line) >= 20:
                x = hex_to_float(line[8:12])
                y = hex_to_float(line[12:16])
                v = hex_to_float(line[16:20])
                return (x, y, v), last_index + 1
    return None, last_index

def live_plot(filename):
    plt.ion()
    fig, ax = plt.subplots()
    prev_pos = None
    line_index = 0

    while True:
        data, line_index = read_last_frame(filename, line_index)
        if data:
            x, y, v = data

            ax.clear()
            ax.set_xlim(0, 3)
            ax.set_ylim(0, 3)
            ax.set_title(f"Live Position")
            ax.set_xlabel("X (m)")
            ax.set_ylabel("Y (m)")
            ax.grid(True)

            ax.scatter([x], [y], color='blue')

            if prev_pos:
                dx = x - prev_pos[0]
                dy = y - prev_pos[1]
                ax.arrow(prev_pos[0], prev_pos[1], dx, dy,
                         head_width=0.03, head_length=0.04, fc='red', ec='red')

            prev_pos = (x, y)
            plt.draw()
        plt.pause(0.1)

# Start live visualisatie
live_plot("manual_output.txt")
