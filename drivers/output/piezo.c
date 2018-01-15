/*
 * piezo.c
 *
 * Created: 2017-07-16 6:23:11 PM
 *  Author: Conan
 */ 
#include <asf.h>
#include "piezo.h"



void piezo_init(ioport_pin_t p_buzzer)
{
	//PWM Clock options
	pwm_clock_t piezo_clock_opts = {
		.ul_clka = 100000, //100Khz clock frequency = .01 ms steps
		.ul_clkb = 0,
		.ul_mck =  sysclk_get_main_hz() //main clock speed is 240Mhz!, not 120mhz
	};
	
	//PWM options
	piezo_channel.ul_prescaler = PWM_CMR_CPRE_CLKA;
	piezo_channel.ul_period = MAX_PERIOD;
	piezo_channel.ul_duty = 7; //10% duty cycle
	piezo_channel.polarity = PWM_HIGH;
	piezo_channel.channel = PWM_CHANNEL_3;
	
	//configure IO pins
	pio_configure_pin( p_buzzer, PIO_TYPE_PIO_PERIPH_B );
	
	//Enable PWM clock
	pmc_enable_periph_clk(ID_PWM);
	
	//disable temporarily
	pwm_channel_disable(PWM, PWM_CHANNEL_3);
	pwm_init( PWM, &piezo_clock_opts );
	pwm_channel_init( PWM, &piezo_channel );
}

void piezo_start(){
	pwm_channel_enable( PWM, PWM_CHANNEL_3 );
}

void piezo_stop(){
	pwm_channel_disable(PWM, PWM_CHANNEL_3);
}
void piezo_update(uint32_t period){
	pwm_channel_update_period( PWM, &piezo_channel, period );
}