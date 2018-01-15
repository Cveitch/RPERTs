/*
 * piezo.h
 *
 * Created: 2017-07-16 6:22:55 PM
 *  Author: Conan
 */ 


#ifndef PIEZO_H_
#define PIEZO_H_

void piezo_init(ioport_pin_t p_buzzer);
void piezo_update(uint32_t duty);
void piezo_start();
void piezo_stop();

#define MAX_PERIOD	150 //1.5ms maximum period
pwm_channel_t piezo_channel;

#endif /* PIEZO_H_ */