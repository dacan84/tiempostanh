/*
 * calculo_error.h
 *
 *  Created on: 31/5/2015
 *      Author: Diego
 */

#ifndef CALCULO_ERROR_H_
#define CALCULO_ERROR_H_

#include <stdint.h>
#include "ANN_implementation.h"

#define SIZE 256

/* Errores data class */
typedef struct {
    float error_rel_avg;
    float error_rel_max;
} ErrorData;

ErrorData calculo_errores (uint8_t number_samples, TrainInputData *in_data);

#endif /* CALCULO_ERROR_H_ */
