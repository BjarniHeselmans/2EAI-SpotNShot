#include "spi_interface.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
/*
// Function to shift an array (helper function)
void shift_array(uint8_t* arr, uint8_t size) {
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
}
*/

// Initialize SPI as a slave
void init_spi() {
    spi_init(SPI_PORT, 1000 * 1000);
    spi_set_slave(SPI_PORT, 1);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Multi-byte transfers
   // spi_set_format(SPI_PORT, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
}

// Receive SPI data and parse into detected objects
/*
std::vector<DetectedObject> receive_spi_data() {
    uint8_t patternbuf[5] = {0};
    uint8_t byte;
    
    // Wait for the magic pattern
    while (true) {
        shift_array(patternbuf, 5);
        spi_read_blocking(SPI_PORT, 0, &patternbuf[4], 1);

        if (patternbuf[0] == 4 && patternbuf[1] == 5 && patternbuf[2] == 8 && patternbuf[3] == 1 && patternbuf[4] == 2) {
            break;
        }
    }

    // Gather packet
    uint16_t packet_size;
    uint8_t number_of_objects;

    if (spi_is_readable(SPI_PORT)) {
        spi_read_blocking(SPI_PORT, 0, (uint8_t*)(&packet_size), 2);
    }
    if (spi_is_readable(SPI_PORT)) {
        spi_read_blocking(SPI_PORT, 0, &number_of_objects, 1);
    }

    std::vector<DetectedObject> object_array(number_of_objects);

    if (spi_is_readable(SPI_PORT)) {
        spi_read_blocking(SPI_PORT, 0, (uint8_t*)object_array.data(), number_of_objects * sizeof(DetectedObject));
    }

    return object_array;
}
*/