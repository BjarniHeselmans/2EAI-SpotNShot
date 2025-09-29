#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DmxOutput.hpp"
#include "calculations.hpp"
#include "spi_interface.hpp"

/* UNIVERSE channels*/       
#define MOTOR_SPEED         0                   /* channel 5 : motor speed  0 for max speed, 255 not moving motor */
#define LIGHT_INTENSITY     5               /* channel 6 : color lighting and mode  */
#define GOBO_SELECTION      0                /* channel 7 : GOBO selection*/
#define MASTER_DIMMER       255               /* channel 8 : Master dimmer */
#define STROBE              0                        /* channel 9 : strobe effect */

// DMX - data pins
#define DMX_DATA_PIN PICO_DEFAULT_UART_TX_PIN   // Data-line (DI op RS485) (GPIO0)
#define DMX_ENABLE_PIN 14 // Enable pin (DE en RE samen) (GPIO14)
#define UNIVERSE_LENGTH 504  // depends on the channels enabled in the spot 5ch : 508 9ch: 504 11CH: 502
uint8_t universe[UNIVERSE_LENGTH+1] = {0}; // start code needs to be 0

void shift_array(uint8_t* arr, uint8_t size) {
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

int main() {
    stdio_init_all();
  
    sleep_ms(2000);

    // Put enable pin on so the rs485 is in sending mode 
    gpio_init(DMX_ENABLE_PIN);
    gpio_set_dir(DMX_ENABLE_PIN, GPIO_OUT);
    gpio_put(DMX_ENABLE_PIN, 1); // 1 = Sendmode, 0 = Receivemode
    
    DmxOutput dmx; 
    
    // Start DMX-output with the right GPIO_pin and PIO0 
    
    //  printf("Initialise DMX on  GPIO %d...\n", DMX_DATA_PIN);
    if (dmx.begin(DMX_DATA_PIN, pio0) != DmxOutput::SUCCESS) {
          printf("Error: DMX initialisation failed!\n");
        while (true) {
            sleep_ms(1000);
        }
    }

    init_spi();
    
    while (true) {
        /*std::vector<DetectedObject> detected_objects = receive_spi_data();

        if (!detected_objects.empty()) {
            printf("===== Got objects =====\n");
            for (size_t i = 0; i < detected_objects.size(); i++) {
             /* print for debugging only *//*
                printf("%zu)\t x: %.2f\ty: %.2f\tv: %.f\n", 
                        i, detected_objects[i].x, detected_objects[i].y, detected_objects[i].v); 
            }

            // Process the first detected object
            float x = detected_objects[0].x;
            float y = detected_objects[0].y; */
            uint8_t patternbuf[5] = {0};
            uint8_t byte;
            while (1){
            shift_array(patternbuf,5);
            spi_read_blocking(SPI_PORT,0,&(patternbuf[4]),1);
            //Listen for magic pattern
            // for(int i=0; i<5;i++){
            // printf("patternbuf[%d] : %x ", i, patternbuf[i]);
            // }
            // printf("\n");
            if(patternbuf[0]==4 && patternbuf[1] == 5 && patternbuf[2] == 8 && patternbuf[3] == 1 && patternbuf[4] == 2){
                break;
            }

  
        }

        //Gather packet & fill variables
        uint16_t packet_size;
        uint8_t number_of_objects;

        //if(spi_is_readable(SPI_PORT)){
            spi_read_blocking(SPI_PORT,0,(uint8_t*)(&packet_size),2);

        
       // if(spi_is_readable(SPI_PORT)){
            spi_read_blocking(SPI_PORT,0,&number_of_objects,1);
        
       printf("packet size : %x number objects: %x \n", packet_size,number_of_objects);
         struct DetectedObject* object_array = (struct DetectedObject*)  malloc(number_of_objects*sizeof(struct DetectedObject));

        //if(spi_is_readable(SPI_PORT)){
        //   spi_read_blocking(SPI_PORT,0,(uint8_t*)object_array,(number_of_objects*sizeof(struct DetectedObject)));
        float x,y,v;
        spi_read_blocking(SPI_PORT,0,(uint8_t*)&x,sizeof(float));
        spi_read_blocking(SPI_PORT,0,(uint8_t*)&y,sizeof(float));
        spi_read_blocking(SPI_PORT,0,(uint8_t*)&v,sizeof(float));

        printf("=====Got objects=====\n");
        // for(int i=0;i<number_of_objects;i++){
        //     printf("%d)\t x: %.2f\ty: %.2f\tv: %.f\n",i,object_array[i].x,object_array[i].y,object_array[i].v);
        // }
        printf("x: %.2f   Y: %.2f  V: %.2f\n",x,y,v);
        
     //   float x = object_array[0].x;
     //   float y = object_array[0].y; 
           //Convert x and y to DMX pan/tilt values
            calc_angle_pan(x, y);
 /*
 universe[1] = DMX_pan;                   
 universe[2] = DMX_tilt;  
 universe[3] = 0;                        
 universe[4] = 255;                      
 universe[5] = 100;                      
   */    
    universe[1] = DMX_pan;                  
    universe[2] = DMX_tilt;                 
    universe[3] = DMX_pan_pr;               
    universe[4] = DMX_tilt_pr;              
    universe[5] = MOTOR_SPEED;                       
    universe[6] = LIGHT_INTENSITY;                     
    universe[7] = GOBO_SELECTION;                       
    universe[8] = MASTER_DIMMER;                      
    universe[9] = STROBE;                        
     
            // Check if transmission is done
            if (!dmx.busy()) {
                //  printf("Sending DMX data...\n");
                dmx.write(universe, UNIVERSE_LENGTH+1);
                /* print for debugging only */
                printf("DMX data send: [%d, %d, %d, %d, %d]\n",
                    universe[1], universe[2], universe[3], universe[4], universe[5]); 
                    
             }
        
        // Waite until the next frame is being send (~44ms per frame)
        sleep_ms(2000);
    }
    
    // Should never gets here. 
    dmx.end();
    
    return 0;
}
