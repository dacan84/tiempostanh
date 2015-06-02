/*
 * ANN_implementation.h
 *
 *  Created on: 10/3/2015
 *      Author: Diego
 */

#ifndef SOLAR_ANN_IMPLEMENTATION_H_
#define SOLAR_ANN_IMPLEMENTATION_H_

#include "anndatatype.h"
#define ANN2LAYERS

//void ANNCalculus (void);
#ifdef ANN3LAYERS
float Calculo_ANN_3Layer (TrainInputData dataN);
#endif

#ifdef ANN2LAYERS
float Calculo_ANN_2Layer (TrainInputData dataN);
#endif
TrainInputData NormalizedInput (TrainInputData input);
float VoltrageReference (float tensionReferenciaN);
void GenerateInArraray (float l, float t);

#endif /* SOLAR_ANN_IMPLEMENTATION_H_ */
