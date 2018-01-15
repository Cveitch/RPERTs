/*
 * motor.c
 *
 * Created: 2017-07-16 3:42:34 PM
 *  Author: Conan
 */ 
#include <asf.h>
#include "motor.h"
void motor_init(MOTOR_PINS * mpins, ioport_pin_t mot1_pin1, ioport_pin_t mot1_pin2, 
				ioport_pin_t mot2_pin1, ioport_pin_t mot2_pin2, ioport_pin_t mot1_pwm, 
				pwm_ch_t chan1){
	mpins->AIN1 = mot1_pin1;
	mpins->AIN2 = mot1_pin2;
	mpins->BIN1 = mot2_pin1;
	mpins->BIN2 = mot2_pin2;
	mpins->PWMA = mot1_pwm;
	delay_ms(50);
	
	ioport_set_pin_dir(mpins->AIN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(mpins->AIN2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(mpins->BIN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(mpins->BIN2, IOPORT_DIR_OUTPUT);
	
	motor_pwm_init(mpins, chan1);
	drive_motor(mpins, STOP);
	
}

void set_motor(MOTOR_PINS* mpins, bool A1, bool A2, bool B1, bool B2){
	ioport_set_pin_level(mpins->AIN1, A1);
	ioport_set_pin_level(mpins->AIN2, A2);
	ioport_set_pin_level(mpins->BIN1, B1);
	ioport_set_pin_level(mpins->BIN2, B2);
}

void drive_motor(MOTOR_PINS* mpins, direction dir){
	delay_ms(20);
	switch(dir){
		case FORWARD:
			set_motor(mpins, true, false, true, false);
			break;
		case BACK:
			set_motor(mpins, false, true, false, true);
			break;
		case RIGHT:
			set_motor(mpins, false, true, true, true);
			break;
		case LEFT:
			set_motor(mpins, true, true, false, true);
			break;
		case SPIN_RIGHT:
			set_motor(mpins, false, true, true, false);
			break;
		case SPIN_LEFT:
			set_motor(mpins,true, false, false, true);
			break;
		case STOP:
		set_motor(mpins, true, true, true, true);
			break;
	}
}

void motor_pwm_init(MOTOR_PINS* mpins, pwm_ch_t chan1){
	
	//PWM Clock options
	pwm_clock_t motor_clock_opts = {
		.ul_clka = MAX_FREQ, //100Khz clock frequency = .01 ms steps
		.ul_clkb = 0,
		.ul_mck =  sysclk_get_main_hz() //main clock speed is 240Mhz!, not 120mhz
	};
	//PWM options
	motor_channel_1.ul_prescaler = PWM_CMR_CPRE_CLKA;
	motor_channel_1.ul_period = MAX_PERIOD;
	motor_channel_1.ul_duty = MAX_DUTY; //10% duty cycle
	motor_channel_1.polarity = PWM_HIGH;
	motor_channel_1.channel = chan1;

	//configure IO pins
	pio_configure_pin( mpins->PWMA, PIO_TYPE_PIO_PERIPH_B );
	
	//Enable PWM clock
	pmc_enable_periph_clk(ID_PWM);
		
	//disable temporarily
	//pwm_channel_disable(PWM, chan1);
	pwm_channel_disable(PWM, chan1);
	pwm_init( PWM, &motor_clock_opts );
	pwm_channel_init( PWM, &motor_channel_1 );
	pwm_channel_enable( PWM, chan1 );
}

void motor_speed(uint32_t period){
	pwm_channel_update_period( PWM, &motor_channel_1, period );
}
