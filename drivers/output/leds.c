/*
 * leds.c
 *
 * Created: 2017-07-16 3:44:20 PM
 *  Author: Conan
 */ 

#include <asf.h>
#include "leds.h"

void led_init(LED_PINS* lpins, ioport_pin_t red, ioport_pin_t green, ioport_pin_t blue){
	
	lpins->RED_LED = red;
	lpins->GREEN_LED = green;
	lpins->BLUE_LED = blue;
	ioport_set_pin_dir(lpins->RED_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(lpins->GREEN_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(lpins->BLUE_LED, IOPORT_DIR_OUTPUT);
	set_led(lpins, BLACK);
}

void set_led(LED_PINS* lpins, LED_COLOUR colour){
	switch (colour){
		case RED:
			set_led_colour(lpins, 1, 0, 0);
			break;
		case BLUE:
			set_led_colour(lpins, 0, 0, 1);
			break;
		case GREEN:
			set_led_colour(lpins, 0, 1, 0);
			break;
		case YELLOW:
			set_led_colour(lpins, 1, 1, 0);
			break;
		case TURQUOISE:
			set_led_colour(lpins, 0, 1, 1);
			break;
		case PURPLE:
			set_led_colour(lpins, 1, 0, 1);
			break;
		case WHITE:
			set_led_colour(lpins, 1, 1, 1);
			break;
		case BLACK:
			set_led_colour(lpins, 0, 0, 0);
			break;
	}
}

void set_led_colour(LED_PINS* lpins, int r, int g, int b){
	if (r==0){
		ioport_set_pin_level(lpins->RED_LED, false);
	}
	else if (r==1){
		ioport_set_pin_level(lpins->RED_LED, true);
	}
	if (g==0){
		ioport_set_pin_level(lpins->GREEN_LED, false);
	}
	else if (g==1){
		ioport_set_pin_level(lpins->GREEN_LED, true);
	}
	if (b==0){
		ioport_set_pin_level(lpins->BLUE_LED, false);
	}
	else if (b==1){
		ioport_set_pin_level(lpins->BLUE_LED, true);
	}
}



		