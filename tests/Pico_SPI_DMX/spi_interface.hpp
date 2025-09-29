#ifndef SPI_INTERFACE_HPP
#define SPI_INTERFACE_HPP

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <vector>

// SPI Defines
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

struct DetectedObject {
    float x;
    float y;
    float v;
};

void init_spi();
std::vector<DetectedObject> receive_spi_data();

#endif // SPI_INTERFACE_HPP
