/*
 * main.c
 *
 * Created: 2017-07-16 3:44:34 PM
 *  Author: Conan
 */ 

#include <asf.h>
#include "rupert.h"
#include "./drivers/output/leds.h"
#include "./drivers/output/piezo.h"
#include "./drivers/mobility/collision.h"
#include "./drivers/mobility/bearing.h"
#include "conf_board.h"
#include "conf_bno055.h"
#include "./ASF/thirdparty/bno055/bno055_port.h"
#include <stdlib.h>


struct bno055_euler_t bearing; // Contains the position vector data
// PINOUT STRUCTS
MOTOR_PINS		mpins_;
MOTOR_PINS*		mpins = &mpins_;
LED_PINS		lpins_1_;
LED_PINS*		lpins_1 = &lpins_1_;
LED_PINS		lpins_2_;
LED_PINS*		lpins_2 = &lpins_2_;
// No filtering yet, just here for completion.
KalmanTuple		ktuple_;
KalmanTuple*	ktuple = &ktuple_;
Message msg;
// rssi default value, in order to be safe.
uint32_t meas_rssi = - 50;
uint32_t last_rss = - 50;

void main(void){
	initialize_rupert();
	delay_ms(50);
	set_led(lpins_1, WHITE);
	set_led(lpins_2, WHITE);
	delay_ms(500);
	bool detected = false;
	uint32_t obj_det = 0;
	motor_speed(10);
	
	kalman_init(ktuple, meas_rssi, 900, 5, 10);
	
	
	while (1){
		delay_ms(1000);
		anchor_behaviour();
		//rabble_behaviour(ktuple, meas_rssi, last_rss);
		
		}
}


void update_kalman(KalmanTuple* ktup, uint32_t u, uint32_t rss){
	uint32_t MEASURED_RSSI = rss;
	kalman_predict(0, ktup);
	kalman_update(MEASURED_RSSI, ktup);
}

void rabble_behaviour(KalmanTuple* ktup, uint32_t rss, uint32_t last_rss){
	update_kalman(ktup, 0, rss);
	set_led(lpins_1, GREEN);
	check_bearing(bearing);
	
	if(!check_collision()){
		set_led(lpins_1, RED);
		drive_motor(mpins, SPIN_RIGHT);
	}
	else if(rss >= 20 && rss <= last_rss){
		drive_motor(mpins, FORWARD);
	}
	else if(rss >= 20 && rss > last_rss){
		drive_motor(mpins, SPIN_RIGHT);
	}
	else if(rss < 20 && rss <= last_rss){
		drive_motor(mpins, SPIN_LEFT);
	}
	else if(rss < 20 && rss > last_rss){
		drive_motor(mpins, FORWARD);
	}
	
	delay_ms(70);
	
}

void initialize_rupert(){
	board_init();
	sysclk_init();
	led_init(lpins_1, LED1_R, LED1_G, LED1_B);
	led_init(lpins_2, LED2_R, LED2_G, LED2_B);
	
	//piezo_init(PIEZO_BUZZ);
	//piezo_start();
	//piezo_update(100);
	
	bearing_config();
	collision_init(IR_1, IR_2);
	motor_init(mpins, A1, A2, B1, B2, PWM_A_B, PWM_CHANNEL_1);
	
	
	//Init MAC
	if( !mac_init( 1, msg_received, ack_received ) ){
		//Error: Xbee's baud rate is different to the one specified in mac_config.h (RADIO SPEED RATE)
		while(1);
	}
	
	
}

void msg_send(uint32_t addressee, uint32_t data, uint32_t datal){
	msg.address = addressee;		//Addressee node
	msg.data[0] = data;					//send anything (random value)
	msg.data_length = datal;				//we're sending one byte
	mac_send(&msg);
	
}





void anchor_behaviour(){
	set_led(lpins_1, RED);
	msg_send(ADDRESSEE_NODE, 7, 1);
	set_led(lpins_2, YELLOW);
	delay_ms(50);
	set_led(lpins_2, BLUE);
}



void random_walk(){
	int r = rand() %6;
	switch(r){
		case 0: case 5:
		drive_motor(mpins, FORWARD);
		break;
		case 1:
		drive_motor(mpins,SPIN_LEFT);
		break;
		case 2:
		drive_motor(mpins,SPIN_RIGHT);
		break;
		case 3:
		drive_motor(mpins,LEFT);
		break;
		case 4:
		drive_motor(mpins,RIGHT);
		break;
	}
}

void sound_test(){
	piezo_start();
	piezo_update(523.25);
	delay_ms(133);
	piezo_update(523.25);
	delay_ms(133);
	piezo_update(523.25);
	delay_ms(133);
	piezo_update(523.25);
	delay_ms(400);
	
	
	piezo_update(415.3);
	delay_ms(400);
	
	piezo_update(466.16);
	delay_ms(400);
	
	piezo_update(523.25);
	delay_ms(133);
	delay_ms(133);
	
	piezo_update(466.16);
	delay_ms(133);
	
	piezo_update(523.25);
	delay_ms(1200);
	
}

void check_bearing(struct bno055_euler_t data){
	bno055_read_euler_hrp(&data);
	if(heading_to_degrees(data.h) < 90 && heading_to_degrees(data.h) > 0){
		set_led(lpins_2, PURPLE);
		//piezo_start();
		//piezo_update(100);
	}
	else if(heading_to_degrees(data.h) > 90 && heading_to_degrees(data.h) < 180){
		set_led(lpins_2, YELLOW);
		//piezo_start();
		//piezo_update(70);
	}
	else if(heading_to_degrees(data.h) > 180 && heading_to_degrees(data.h) < 270){
		set_led(lpins_2, TURQUOISE);
		//piezo_start();
		//piezo_update(80);
	}
	else if(heading_to_degrees(data.h) > 270 && heading_to_degrees(data.h) < 360){
		set_led(lpins_2, BLUE);
		//piezo_start();
		//piezo_update(90);
	}
}

void ack_received(uint8_t status){}
	
void msg_received(Message *msg_in){
	last_rss = meas_rssi;
	meas_rssi = (-1) *  msg_in->rssi;
}