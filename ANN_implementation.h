/*
 * ANN_implementation.h
 *
 *  Created on: 10/3/2015
 *      Author: Diego
 */

#ifndef SOLAR_ANN_IMPLEMENTATION_H_
#define SOLAR_ANN_IMPLEMENTATION_H_

/* Valores de entrada data class */
typedef struct {
    float	lux;
    float	temp;
    float 	vref;
} TrainInputData;

//void ANNCalculus (void);
float Calculo_ANN_3Layer (TrainInputData dataN);
float Calculo_ANN_2Layer (TrainInputData dataN);
float VoltrageReference (float tensionReferenciaN);
void GenerateInArraray (float l, float t);

#endif /* SOLAR_ANN_IMPLEMENTATION_H_ */
