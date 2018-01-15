/*
 * leds.h
 *
 * Created: 2017-07-16 3:44:34 PM
 *  Author: Conan
 */ 


#ifndef LEDS_H_
#define LEDS_H_

typedef enum{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	TURQUOISE,
	WHITE,
	BLACK
}LED_COLOUR;

typedef struct{
	ioport_pin_t RED_LED;
	ioport_pin_t GREEN_LED;
	ioport_pin_t BLUE_LED;
}LED_PINS;

void led_init(LED_PINS* lpins, ioport_pin_t red, ioport_pin_t green, ioport_pin_t blue);
void set_led_colour(LED_PINS* lpins, int r, int g, int b);
void set_led(LED_PINS* lpins, LED_COLOUR colour);

#endif /* LEDS_H_ */