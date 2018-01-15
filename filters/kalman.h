/*
 * kalman.h
 *
 * Created: 2017-06-29 10:27:06 PM
 *  Author: Conan
 */ 

#ifndef KALMAN_H_
#define KALMAN_H_

#include <stdint-gcc.h>

// The initial RSSI is some arbitrary RSSI value the node might be away from the broadcast source.
// Initial variance is the variance of our initial RSSI. Variance is squared, so if
// var=900, 900=30^2, so we are 97% confident that we are within 30*3=90 RSSI (three standard deviations).
// This makes a kind of sense, if we set RSSI to be zero, and VAR to be 900.  By the above equalities, this would
// mean that our RSSI is zero, but we have a 97 percent chance to be between 0 - 90.
// Sensor Variance is the inherent measurement variance of the XBEE.  Experimentally found.
// RSSI Variance is the inherent variance of RSSI itself.  Experimentally found.

typedef struct {
	uint32_t RSSI;
	uint32_t VAR;
	uint32_t SENSOR_VAR;
	uint32_t RSSI_VAR;
	}KalmanTuple ;

void kalman_init(KalmanTuple* ktuple, int32_t rssi, int32_t init_var, int32_t sens_var, int32_t proc_var);
void kalman_predict(int32_t u, KalmanTuple* ktuple);
void kalman_update(int32_t new_rssi, KalmanTuple* ktuple);



#endif /* KALMAN_H_ */