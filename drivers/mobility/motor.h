/*
 * motor.h
 *
 * Created: 2017-07-16 3:43:42 PM
 *  Author: Conan
 */ 

#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum {
	FORWARD, 
	BACK, 
	RIGHT, 
	LEFT, 
	SPIN_LEFT, 
	SPIN_RIGHT, 
	STOP
} direction;

typedef struct{
	ioport_pin_t AIN1;
	ioport_pin_t AIN2;
	ioport_pin_t PWMA;
	ioport_pin_t BIN1;
	ioport_pin_t BIN2;
	ioport_pin_t PWMB;
	}MOTOR_PINS;

#define MAX_PERIOD	150 //1.5ms maximum period
#define MAX_FREQ	100000
#define MAX_DUTY	7

pwm_channel_t motor_channel_1;
pwm_channel_t motor_channel_2;

//#define periph1 = PIO_TYPE_PIO_PERIPH_B
//#define periph2 = PIO_TYPE_PIO_PERIPH_C

void set_motor(MOTOR_PINS* mpins, bool A1, bool A2, bool B1, bool B2);
void drive_motor(MOTOR_PINS* mpins, direction dir);
void motor_pwm_init(MOTOR_PINS* mpins, pwm_ch_t chan1);
void motor_speed(uint32_t period);
void motor_init(MOTOR_PINS* mpins, ioport_pin_t mot1_pin1, ioport_pin_t mot1_pin2,
ioport_pin_t mot2_pin1, ioport_pin_t mot2_pin2, ioport_pin_t mot1_pwm,
pwm_ch_t chan1);

#endif /* MOTOR_H_ */