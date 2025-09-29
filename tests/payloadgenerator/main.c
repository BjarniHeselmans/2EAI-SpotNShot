#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#pragma pack(1)

uint8_t magic_pattern[5] = {0x4,0x5,0x8,0x1,0x2};
#define MAGIC_SIZE 5

#define FILENAME "packets.bin"

#define ITERATIONS 10

typedef struct {
    float x;
    float y;
    float v;
} Object;

typedef struct {
    uint16_t packet_size; 
    uint8_t num_objects;  
    Object *objects;      
} Packet;

void writePacket(FILE *file, Packet *packet) {
    fwrite(magic_pattern, 1, MAGIC_SIZE, file);
    fwrite(&packet->packet_size, sizeof(uint16_t), 1, file);
    fwrite(&packet->num_objects, sizeof(uint8_t), 1, file);
    fwrite(packet->objects, sizeof(Object), packet->num_objects, file);
    printf("Pritning hexdump of objects\n");
    for(int i=0;i<(packet->num_objects*sizeof(Object));i++){
        printf("0x%x ",((uint8_t*)(packet->objects))[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    FILE *file = fopen(FILENAME, "wb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    //Create data packet
    Packet packet;
    packet.num_objects = 3;
    packet.packet_size = sizeof(uint16_t) + sizeof(uint8_t) + (packet.num_objects * sizeof(Object));
    packet.objects = malloc(packet.num_objects * sizeof(Object));
    packet.objects[0] = (Object){1.1f, 2.2f, 3.3f};
    packet.objects[1] = (Object){4.4f, 5.5f, 6.6f};
    packet.objects[2] = (Object){7.7f, 8.8f, 9.9f};
    writePacket(file, &packet);

    //Add noise and write
    for(int i=0;i<ITERATIONS;i++){
        packet.objects[0].x += (float)(rand())/RAND_MAX;
        packet.objects[0].y += (float)(rand())/RAND_MAX;
        packet.objects[0].v += (float)(rand())/RAND_MAX;

        packet.objects[1].x -= (float)(rand())/RAND_MAX;
        packet.objects[1].y -= (float)(rand())/RAND_MAX;
        packet.objects[1].v -= (float)(rand())/RAND_MAX;

        packet.objects[2].x += (float)(rand()-(RAND_MAX/2))/RAND_MAX;
        packet.objects[2].y += (float)(rand()-(RAND_MAX/2))/RAND_MAX;
        packet.objects[2].v += (float)(rand()-(RAND_MAX/2))/RAND_MAX;

        writePacket(file, &packet);
    }

    fclose(file);
    free(packet.objects);

    file = fopen(FILENAME, "rb");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    return 0;
}