 #ifndef CALCULATIONS_H
 #define CALCULATIONS_H

 #include <math.h>
 #include <stdio.h>

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


 void calc_angle_pan( float opposite, float adjacent) {  
    float angle_rad, angle_deg =0;
    if (opposite > (STAGE_WIDTH/2.0)){
    angle_rad = atan((opposite-STAGE_WIDTH/2)/adjacent);  
    angle_deg = angle_rad / M_PI * 180.0;
    angle_deg +=90;
} else if (opposite <= (STAGE_WIDTH/2.0)){
     angle_rad = atan((STAGE_WIDTH/2-opposite)/adjacent);  
     angle_deg = angle_rad / M_PI *180.0 ;
    angle_deg = 90 - angle_deg;
}
   DMX_pan = (uint8_t) angle_deg/ ANGLE_PAN;
   calc_precision_pan(angle_deg);
    calc_angle_tilt(adjacent, angle_rad);
 }

 void calc_angle_tilt( float adjacent, float angle_rad){
    float hypotenuse = adjacent/ cos(angle_rad); 
    float angle_rad_tilt = atan(hypotenuse/HEIGHT_SPOT);
    float angle_deg_tilt = 90 - ( angle_rad_tilt / M_PI * 180.0 ) + 25; // 25° offset
    DMX_tilt = (uint8_t) angle_deg_tilt/ ANGLE_TILT;
    calc_precision_tilt ( angle_deg_tilt);
 }

 void calc_precision_pan (float angle_deg) {
   float value = fmod(angle_deg,ANGLE_PAN);
   DMX_pan_pr = (uint8_t) value / ANGLE_PAN_PR;
 }

 void calc_precision_tilt (float angle_deg) {
   float value = fmod(angle_deg, ANGLE_TILT);
   DMX_tilt_pr = (uint8_t) value / ANGLE_TILT_PR;
 }

 #endif