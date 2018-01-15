/*
 * collision.c
 *
 * Created: 2017-07-18 5:19:30 PM
 *  Author: Conan
 */ 

#include <asf.h>
#include "collision.h"

void collision_init(){
	/* Enable ADC clock. */
	pmc_enable_periph_clk(ID_ADC);

	/* Configure ADC. */
	adc_init(ADC, sysclk_get_cpu_hz(), 1000000, ADC_MR_STARTUP_SUT0);
	adc_enable_channel(ADC, ADC_CHANNEL_13);
	adc_enable_channel(ADC, ADC_CHANNEL_14);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
	adc_start(ADC);
}

// This is boolean valued, either an object is in range, or not.
bool check_collision(){
	bool detected;
	uint32_t measured = adc_get_channel_value(ADC, ADC_CHANNEL_14);
	if(measured >= 4095){
		detected = true;
	}
	else{
		detected = false;
	}
	return detected;
}

// This will return a value between 0 and 100.  Lower is further away
int check_object(){
	uint32_t measured = adc_get_channel_value(ADC, ADC_CHANNEL_13);
	uint32_t normalized = (100 - 100*measured/4096);
	return normalized;
}