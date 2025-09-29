/*
gcc main.cpp -o main.exe
main
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nieuwe Magic Pattern
const unsigned char magic_pattern[] = {0x04, 0x05, 0x08, 0x01, 0x02};

// Functie om de snelheid (v) naar een 4-byte float om te zetten en te schrijven
void write_speed(FILE *file, float speed_mps) {
    unsigned char* speed_bytes = (unsigned char*) &speed_mps;
    for (int i = 0; i < 4; i++) {
        fprintf(file, "%02X ", speed_bytes[i]);
    }
}

// Functie om de objecten te genereren
void generate_test_data(int iterations, int objects, int moving_objects, bool noise, bool appear, const char* output_file) {
    FILE *file = fopen(output_file, "w");
    if (!file) {
        printf("Error: Could not open file %s for writing\n", output_file);
        return;
    }

    int positions[objects][2];  // Posities in centimeters
    float speeds[objects];      // Array om snelheden op te slaan voor elk object

    for (int j = 0; j < objects; j++) {
        positions[j][0] = rand() % 256; // Willekeurige positie (0-255) in meters
        positions[j][1] = rand() % 256; // Willekeurige positie (0-255) in meters
        speeds[j] = 0.0f; // Standaard snelheid is 0 m/s voor alle objecten
    }

    // Print de Magic Pattern aan het begin van elke iteratie
    for (int i = 0; i < iterations; i++) {
        // Reset snelheden voor elke iteratie
        for (int j = 0; j < objects; j++) {
            speeds[j] = 0.0f; // Zet snelheid van alle objecten op 0
        }

        // Willekeurige objecten krijgen snelheid (maximale aantal bewegende objecten)
        for (int m = 0; m < moving_objects; m++) {
            int moving_object = rand() % objects;
            positions[moving_object][0] += (rand() % 21) - 10; // Willekeurige beweging tussen -10 en 10 cm
            positions[moving_object][1] += (rand() % 21) - 10; // Willekeurige beweging tussen -10 en 10 cm

            if (positions[moving_object][0] < 0) positions[moving_object][0] = 0;
            if (positions[moving_object][0] > 255) positions[moving_object][0] = 255;
            if (positions[moving_object][1] < 0) positions[moving_object][1] = 0;
            if (positions[moving_object][1] > 255) positions[moving_object][1] = 255;

            speeds[moving_object] = ((rand() % 50 + 1) / 10.0f) / 2.0f; // Willekeurige snelheid tussen 0.05 en 2.5 m/s
        }

        // Voeg geen ruis toe aan de stilstaande objecten
        if (noise) {
            for (int j = 0; j < objects; j++) {
                if (speeds[j] == 0.0f) {
                    speeds[j] = (rand() % 5 + 1) / 100.0f; // Voeg kleine snelheid toe als er ruis is
                }
            }
        }

        // Willekeurig object laten verschijnen/verdwijnen
        if (appear && (rand() % 5 == 0)) {
            int index = rand() % objects;
            positions[index][0] = rand() % 256;
            positions[index][1] = rand() % 256;
        }

        // Bereken de Packet Size voor deze iteratie (nu als 2 bytes)
        int packet_size = sizeof(magic_pattern) + 2 + 1 + (objects * (4 + 4 + 4)); // Magic Pattern + 2-byte Packet Size + Object Count + (4 bytes voor x, 4 bytes voor y, 4 bytes voor snelheid)

        // Debugging output naar terminal
        printf("Iteration %d\n", i + 1);
        for (int j = 0; j < objects; j++) {
            // Omrekenen van posities van centimeters naar meters
            float pos_x_meters = positions[j][0] / 100.0f;
            float pos_y_meters = positions[j][1] / 100.0f;
            printf("Object %d: Position (%.2f m, %.2f m), Speed %.2f m/s\n", j + 1, pos_x_meters, pos_y_meters, speeds[j]);
        }

        // Schrijf Magic Pattern naar bestand
        for (int m = 0; m < sizeof(magic_pattern); m++) {
            fprintf(file, "%02X ", magic_pattern[m]);
        }

        // Schrijf de Packet Size als een 2-byte waarde naar bestand (Little Endian)
        unsigned char packet_size_bytes[2];
        packet_size_bytes[0] = packet_size & 0xFF;        // LSB
        packet_size_bytes[1] = (packet_size >> 8) & 0xFF; // MSB
        fprintf(file, "%02X %02X ", packet_size_bytes[0], packet_size_bytes[1]); // Packet Size in hexadecimaal (2 bytes)

        // Schrijf Object Count naar bestand
        fprintf(file, "%02X ", objects);      // Object Count in hexadecimaal

        // Schrijf Posities en Snelheden van objecten naar bestand (zonder debug)
        for (int j = 0; j < objects; j++) {
            // Schrijf de posities in meters als 4-byte floats
            float pos_x_meters = positions[j][0] / 100.0f;
            float pos_y_meters = positions[j][1] / 100.0f;
            unsigned char* pos_x_bytes = (unsigned char*) &pos_x_meters;
            unsigned char* pos_y_bytes = (unsigned char*) &pos_y_meters;

            for (int k = 0; k < 4; k++) {
                fprintf(file, "%02X ", pos_x_bytes[k]);
            }
            for (int k = 0; k < 4; k++) {
                fprintf(file, "%02X ", pos_y_bytes[k]);
            }

            // Schrijf snelheid als 4-byte float
            write_speed(file, speeds[j]); // Schrijf snelheid
        }

        fprintf(file, "\n");
    }

    fclose(file);
    printf("Data written to %s\n", output_file);
}

// Functie om het menu weer te geven
void print_menu() {
    printf("\n=== Optie Menu ===\n");
    printf("-n [iterations]         Aantal iteraties (standaard: 10)\n");
    printf("-o [objects]            Aantal objecten (standaard: 5)\n");
    printf("-m [moving_objects]     Aantal bewegende objecten (standaard: 1)\n");
    printf("--noise                 Voeg ruis toe aan stilstaande objecten\n");
    printf("--appear                Laat objecten willekeurig verschijnen/verdwijnen\n");
    printf("--output [file]         Bestandsnaam voor output (standaard: test_data.txt)\n");
    printf("\n");
}

int main(int argc, char* argv[]) {
    int iterations = 35;
    int objects = 1;
    int moving_objects = 1;  // Standaard één object beweegt
    bool noise = false;
    bool appear = false;
    const char* output_file = "test_data.txt";

    // Verwerk de commandoregelopties
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            iterations = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            objects = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            moving_objects = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--noise") == 0) {
            noise = true;
        } else if (strcmp(argv[i], "--appear") == 0) {
            appear = true;
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else {
            printf("Invalid argument: %s\n", argv[i]);
            return 1;
        }
    }

    // Genereer de testdata
    generate_test_data(iterations, objects, moving_objects, noise, appear, output_file);

    return 0;
}
