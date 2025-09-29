#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

void shift_array(uint8_t* arr, uint8_t size){
    for(int i=0;i<size-1;i++){
        arr[i] = arr[i+1];
    }
}

struct DetectedObject {
    float x;
    float y;
    float v;
};

int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    spi_set_slave(SPI_PORT,1);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // THIS LINE IS ABSOLUTELY KEY. Enables multi-byte transfers with one CS assert
    // Page 537 of the RP2040 Datasheet.
    spi_set_format(SPI_PORT, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);

    //Setup vector from sensor to spotlight

    while (true) {
        //Hook into data stream
        uint8_t patternbuf[5] = {0};
        uint8_t byte;
        while (1){
            shift_array(patternbuf,5);
            spi_read_blocking(SPI_PORT,0,&(patternbuf[4]),1);
            //Listen for magic pattern
            if(patternbuf[0]==4 && patternbuf[1] == 5 && patternbuf[2] == 8 && patternbuf[3] == 1 && patternbuf[4] == 2){
                break;
            }
        }


        //Gather packet & fill variables
        uint16_t packet_size;
        uint8_t number_of_objects;

        if(spi_is_readable(SPI_PORT)){
            spi_read_blocking(SPI_PORT,0,(uint8_t*)(&packet_size),2);
        }
        if(spi_is_readable(SPI_PORT)){
            spi_read_blocking(SPI_PORT,0,&number_of_objects,1);
        }
       
        struct DetectedObject* object_array = malloc(number_of_objects*sizeof(struct DetectedObject));

        if(spi_is_readable(SPI_PORT)){
            spi_read_blocking(SPI_PORT,0,(uint8_t*)object_array,(number_of_objects*sizeof(struct DetectedObject)));
        }

        printf("=====Got objects=====\n");
        for(int i=0;i<number_of_objects;i++){
            printf("%d)\t x: %.2f\ty: %.2f\tv: %.f\n",i,object_array[i].x,object_array[i].y,object_array[i].v);
        }



        //Select object

        //Create vector

        //Perform vector math

        //Translate vector to angles

        //Send over DMX
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
