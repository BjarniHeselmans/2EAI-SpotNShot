#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const unsigned char magic_pattern[] = {0x04, 0x05, 0x08, 0x01, 0x02};

void write_float(FILE *file, float value) {
    unsigned char *bytes = (unsigned char *)&value;
    for (int i = 0; i < 4; i++) {
        fprintf(file, "%02X ", bytes[i]);
    }
}

void manual_control(const char *filename) {
    FILE *file = fopen(filename, "a"); // append-modus!
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }

    float x = 1.0f, y = 1.0f;
    float prev_x = x, prev_y = y;

    printf("Use W/A/S/D to move. Press Q to quit.\n");

    while (1) {
        if (kbhit()) {
            char key = getch();

            prev_x = x;
            prev_y = y;

            switch (key) {
                case 'w': case 'W': y += 0.1f; break;
                case 's': case 'S': y -= 0.1f; break;
                case 'a': case 'A': x -= 0.1f; break;
                case 'd': case 'D': x += 0.1f; break;
                case 'q': case 'Q': fclose(file); return;
                default: continue;
            }

            float dx = x - prev_x;
            float dy = y - prev_y;
            float v = sqrtf(dx * dx + dy * dy);

            // Schrijf lijn naar bestand (1 object)
            for (int i = 0; i < sizeof(magic_pattern); i++) {
                fprintf(file, "%02X ", magic_pattern[i]);
            }

            int packet_size = 5 + 2 + 1 + (4 + 4 + 4); // magic + size(2) + count + x + y + v
            fprintf(file, "%02X %02X ", packet_size & 0xFF, (packet_size >> 8) & 0xFF);
            fprintf(file, "%02X ", 1); // 1 object

            write_float(file, x);
            write_float(file, y);
            write_float(file, v);

            fprintf(file, "\n");
            fflush(file); // belangrijk voor live lezen in Python

            printf("Moved to x=%.2f, y=%.2f (v=%.2f m/s)\n", x, y, v);
        }
    }
}
int main(int argc, char *argv[]) {
    const char *filename = "manual_output.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    manual_control(filename);
    return 0;
}
