#include "calculations.hpp"

uint8_t DMX_pan = 0;
uint8_t DMX_tilt = 0;
uint8_t DMX_pan_pr = 0;
uint8_t DMX_tilt_pr = 0;

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
   DMX_pan_pr = value / ANGLE_PAN_PR;   
 }

 void calc_precision_tilt (float angle_deg) {
   float value = fmod(angle_deg, ANGLE_TILT);
   DMX_tilt_pr = value / ANGLE_TILT_PR;   
 }
