#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/adc.h"
#include "DmxOutput.hpp"
#include "calculations.hpp"
#include <stdio.h>

/* UNIVERSE channels*/       
#define MOTOR_SPEED 0                   /* channel 5 : motor speed  0 for max speed, 255 not moving motor */
#define LIGHT_INTENSITY 5               /* channel 6 : color lighting and mode  */
#define GOBO_SELECTION 0                /* channel 7 : GOBO selection*/
#define MASTER_DIMMER 255               /* channel 8 : Master dimmer */
#define STROBE 0                        /* channel 9 : strobe effect */



// DMX - data pins
#define DMX_DATA_PIN PICO_DEFAULT_UART_TX_PIN   // Data-line (DI op RS485) (GPIO0)
#define DMX_ENABLE_PIN 14 // Enable pin (DE en RE samen) (GPIO14)
#define UNIVERSE_LENGTH 508  // depends on the channels enabled in the spot 5channel : 508 9ch: 504 11CH: 502
uint8_t universe[UNIVERSE_LENGTH+1] = {0}; // start code needs to be 0


// DMX REACH 
#define DMX_MIN 0
#define DMX_MAX 255

uint8_t DMX_pan;
uint8_t DMX_tilt;
uint8_t DMX_pan_pr;
uint8_t DMX_tilt_pr;

int main() {
    
    stdio_init_all();
    //  printf("DMX Controller Start\n");

    // wait 2s and the start
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
    
    while (true) {
       for(int i = 0; i< STAGE_DEPTH+1; i++ ){
           for(int j=0 ; j<STAGE_WIDTH+1; j++){
    // Make a DMX universe (data pakket) (here in this code i use 5 channel)
    // calc_angle_pan( float opposite, float adjacent)
 calc_angle_pan(i,j);
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

    // Transmission loop
   
        // CVheck if transmission is done
        if (!dmx.busy()) {
            //  printf("Sending DMX data...\n");
            dmx.write(universe, UNIVERSE_LENGTH+1);
              printf("DMX data send: [%d, %d, %d, %d, %d]\n",
                   universe[1], universe[2], universe[3], universe[4], universe[5]); 
                   
        }
        // Waite until the next frame is being send (~44ms per frame)
        sleep_ms(2000);
    }
            }
        } 

    // Should never gets here. 
    dmx.end();
    return 0;
}
