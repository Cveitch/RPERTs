/*
 * bearing.c
 *
 * Created: 2017-07-16 9:25:48 PM
 *  Author: Conan
 */ 

#include "conf_board.h"
#include "conf_bno055.h"
#include "bearing.h"

volatile bool sensor_awake = false;

uint8_t prev_state = AWAKE;


void bearing_config(void){
		bno055_i2c_bus_init();
		bno055_gpio_config();
		extint_initialize(&bno055_interrupt_handler); //set interrupt
		sensor_init();
}

void read_bearing(struct bno055_euler_t data){
	bno055_read_euler_hrp(&data);
}

void bno055_interrupt_handler(void){
	uint8_t accel_no_motion_status = 0;
	
	//read no-motion interrupt status
	bno055_get_intr_stat_accel_no_motion(&accel_no_motion_status);
	
	if (accel_no_motion_status) {
		//NO MOTION DETECTED BY THE SENSOR (Sensor CPU has entered sleep mode)
		ioport_set_pin_level(RGB_LED_G,  RGB_LED_G_OFF); //RGB LED Off
		
		//signal main
		sensor_awake = false;
		}else{
		//MOTION DETECTED BY THE SENSOR (Sensor CPU has woke up)
		ioport_set_pin_level(RGB_LED_G,  RGB_LED_G_ON); //RGB LED On
		
		//signal main
		sensor_awake = true;
	}
	
	//reset interrupt register in sensor
	bno055_set_intr_rst(ENABLED);
}


int32_t heading_to_degrees( int32_t h ){
	return h*(360/5759.0); //value between 0 and 360  ... see pg 30 datasheet
}

int32_t roll_to_degrees( int32_t r ){
	return r*(180/2879.0); //value between -90 and 90 degrees
}

int32_t pitch_to_degrees( int32_t p ){
	return p*(360/5759.0); //value between -180 and 180 degree
}

void sensor_init(void){
	bno055_initialize();
	bno055_set_power_mode(POWER_MODE_LOWPOWER);
	bno055_set_intr_rst(ENABLED);
	
	bno055_set_gyro_any_motion_axis_enable(0, ENABLED);
	bno055_set_gyro_any_motion_axis_enable(1, ENABLED);
	bno055_set_gyro_any_motion_axis_enable(2, ENABLED);
	
	bno055_set_intr_gyro_any_motion(ENABLED);
	bno055_set_intr_mask_gyro_any_motion(ENABLED);
	
	bno055_set_accel_any_motion_no_motion_axis_enable(0, ENABLED);
	bno055_set_accel_any_motion_no_motion_axis_enable(1, ENABLED);
	bno055_set_accel_any_motion_no_motion_axis_enable(2, ENABLED);
	
	bno055_set_accel_any_motion_thres(11); //any motion threshold pg. 40 datasheet
	bno055_set_accel_any_motion_durn(90);  // vary this parameter and the above to set waking up sensitivity
	bno055_set_intr_accel_any_motion(ENABLED);
	bno055_set_intr_mask_accel_any_motion(ENABLED);
	
	bno055_set_accel_slow_no_motion_thres(5); //no motion threshold pg. 38 datasheet
	bno055_set_accel_slow_no_motion_durn(1);  // vary this parameter and the above to set sleeping sensitivity
	bno055_set_intr_accel_no_motion(ENABLED);
	bno055_set_intr_mask_accel_no_motion(ENABLED);
	
	//9-DOF (NDOF) FUSION MODE -- meant to find orientation in space (pg. 22 datasheet)
	//See Axis configuration in pg 25
	//See page 18 functional diagram
	bno055_set_operation_mode(OPERATION_MODE_NDOF);
}
