/*
 * calculo_error.h
 *
 *  Created on: 31/5/2015
 *      Author: Diego
 */

#ifndef CALCULO_ERROR_H_
#define CALCULO_ERROR_H_

#include <stdint.h>
#include "anndatatype.h"
#define SIZE 256

ErrorData calculo_errores (uint8_t number_samples, TrainInputData *in_data);

#endif /* CALCULO_ERROR_H_ */
