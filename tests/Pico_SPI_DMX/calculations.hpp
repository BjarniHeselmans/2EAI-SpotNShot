 #ifndef CALCULATIONS_H
 #define CALCULATIONS_H

 #include <math.h>
 #include <stdio.h>
 #include <stdint.h>

 #define M_PI 3.14159265358979323846  /* pi */
 #define ANGLE_PAN 2.12
 #define ANGLE_TILT 0.9
 #define ANGLE_PAN_PR  0.0083
 #define ANGLE_TILT_PR  0.0035

 #define HEIGHT_SPOT 2.20
 #define STAGE_WIDTH 4
 #define STAGE_DEPTH 4

extern uint8_t DMX_pan;
extern uint8_t DMX_tilt;
extern uint8_t DMX_pan_pr;
extern uint8_t DMX_tilt_pr;


void calc_angle_pan( float opposite, float adjacent) ; 
void calc_angle_tilt( float adjacent, float angle_rad);
void calc_precision_pan (float angle_deg) ;
void calc_precision_tilt (float angle_deg) ;

 #endif //CALCULATIONS_H