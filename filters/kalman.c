/*
 * kalman.c
 *
 * Created: 2017-06-29 10:23:04 am
 *  Author: Conan
 *
 * NOTE: IN ORDER TO USE THE FILTER, YOU MUST INITIALIZE WITH SOME VALUES, THEN CALL THE PREDICT FUNCTION THEN UPDATE FUNCTION:
 * EG, IN MAIN:
 * struct KalmanTuple ktuple;
 * kalman_init(0, 900, 5, 10)
 * uint32_t MEASURED_RSSI = get_rssi() //However this is accomplished
 * kalman_predict(0, ktuple);
 * kalman_update(MEASURED_RSSI, ktuple);
 * 
 */ 
#include "kalman.h"
#include "compiler.h"

void kalman_init(KalmanTuple* ktuple, int32_t rssi, int32_t init_var, int32_t sens_var, int32_t proc_var){
	// Details on values in kalman.h
	ktuple->RSSI = rssi;
	ktuple->VAR = init_var;
	ktuple->SENSOR_VAR = sens_var;
	ktuple->RSSI_VAR = proc_var;
}

void kalman_update(int32_t new_rssi, KalmanTuple* ktuple){

	// Scales the measurement, and the prior measurement by weights, then combines them.
	ktuple->RSSI = ((ktuple->VAR * new_rssi) + (ktuple->RSSI * ktuple->SENSOR_VAR)) / (ktuple->VAR + ktuple->SENSOR_VAR);
	ktuple->VAR = 1.0 / (1.0 / ktuple->VAR + 1.0 / ktuple->SENSOR_VAR);
}

void kalman_predict(int32_t u, KalmanTuple* ktuple){
	
	// u is the expected movement in our measurement.  This is often just 0, since we might not be able to predict.
	ktuple->RSSI += u;
	ktuple->VAR += ktuple->RSSI_VAR;
}


