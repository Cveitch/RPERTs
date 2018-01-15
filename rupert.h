/*
 * rupert.h
 *
 * Created: 2017-07-16 10:15:28 PM
 *  Author: Conan
 */ 
#include "./drivers/mobility/motor.h"
#include "wireless/mac/mac.h"
#include "wireless/radio/radio.h"
#include "wireless/message.h"
#include "./filters/kalman.h"

#ifndef RUPERT_H_
#define RUPERT_H_

//  MOTOR PINS
#define A1	IOPORT_CREATE_PIN(PIOB, 0) // ext2 pin 3
#define A2	IOPORT_CREATE_PIN(PIOB, 1) // ext2 pin 4
#define B1	IOPORT_CREATE_PIN(PIOC, 24) // ext2 pin 5
#define B2	IOPORT_CREATE_PIN(PIOC, 25) // ext2 pin 6
#define PWM_A_B	IOPORT_CREATE_PIN(PIOA, 20) // ext2 pin 8, peripheral B, channel 1

// LED PINS
#define LED1_R	IOPORT_CREATE_PIN(PIOC, 27) // ext2 pin10
#define LED1_G	IOPORT_CREATE_PIN(PIOC, 19) // ext2 pin 7
#define LED1_B	IOPORT_CREATE_PIN(PIOC, 26) // ext2 pin 9
#define LED2_R	IOPORT_CREATE_PIN(PIOC, 31) // ext3 pin 10
#define LED2_G	IOPORT_CREATE_PIN(PIOC, 20) // ext3 pin 7
#define LED2_B	IOPORT_CREATE_PIN(PIOA, 0) // ext3 pin 9

// INFRARED PINS - IR_1 is collision, IR_2 is object detector
#define IR_1	IOPORT_CREATE_PIN(PIOC, 30) // ext3 pin 4 ADC channel 14
#define IR_2	IOPORT_CREATE_PIN(PIOC, 29) // ext3 pin 3 ADC channel 13
// FIX THIS, PASS REFERENCE TO CHANNEL RATHER THAN PIN


// PIEZO BUZZER PINS
#define PIEZO_BUZZ IOPORT_CREATE_PIN(PIOC, 22) // ext3 pin 6 Peripheral B, channel 3

// PWM MAXIMUM PERIOD
#define MAX_PERIOD	150 //1.5ms maximum period

// 0xffff is broadcast mode for addressee
// XBEE Pins are UART.
// XBEE Pinout:  TX is EXT2 pin 13
// XBEE Pinout:  RX is EXT2 pin 14
#define ADDRESSEE_NODE		0xffff

void check_bearing();
void random_walk();
void initialize_rupert();
void msg_received(Message *msg);
void ack_received(uint8_t status);
void msg_send(uint32_t addressee, uint32_t data, uint32_t datal);
void test();
void sound_test();
void anchor_behaviour();
void update_kalman(KalmanTuple* kalman, uint32_t u, uint32_t rss);
void rabble_behaviour(KalmanTuple* ktup, uint32_t rss, uint32_t last_rss);

#endif /* RUPERT_H_ */