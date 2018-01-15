/*
 * bearing.h
 *
 * Created: 2017-07-16 9:25:58 PM
 *  Author: Conan
 */ 
#include "./ASF/thirdparty/bno055/bno055_port.h"

#ifndef BEARING_H_
#define BEARING_H_

#define SLEEPING 1
#define AWAKE	2

void bearing_config(void);
void bno055_interrupt_handler(void);
void sensor_init(void);
void read_bearing(struct bno055_euler_t data);
int32_t roll_to_degrees( int32_t );
int32_t pitch_to_degrees( int32_t );
int32_t heading_to_degrees( int32_t h );

#endif /* BEARING_H_ */