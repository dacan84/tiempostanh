/*
 * anndatatype.h
 *
 *  Created on: 2/6/2015
 *      Author: Diego
 */

#ifndef ANNDATATYPE_H_
#define ANNDATATYPE_H_

	/* Valores de entrada data class */
	typedef struct {
		float	lux;
		float	temp;
		float 	vref;
	} TrainInputData;

	/* Errores data class */
	typedef struct {
		float error_rel_avg;
		float error_rel_max;
	} ErrorData;



#endif /* ANNDATATYPE_H_ */
