/*
 * ANN_memory_saving.h
 *
 *  Created on: 25/3/2015
 *      Author: Diego
 */

#ifndef ANN_MEMORY_SAVING_H_
#define ANN_MEMORY_SAVING_H_


#define FILAS_INPUTS		3
#define COLUMNAS_INPUTS		1

/* Se definen los valores de los pesos de las matrices de la ANN.*/
float b1Iw11[4][3] = {
		{-13.0448,  -11.4487,    1.6743},
		{-34.4833,  -41.5950,    6.1036},
		{ 1.1005,   -0.7040,    -1.8756},
		{-13.8932,  -12.9392,    0.80244}
};

#define FILAS_B1IW11		4
#define COLUMNAS_B1IW11		3

float resultadoIntermedio1[5][1] = {
		{1},
		{0},
		{0},
		{0},
		{0}
};

#define FILAS_RINTERMEDIO1		5
#define COLUMNAS_RINTERMEDIO1	1

float b2Lw12[2][5] = {
		{-103.1527, -147.8146,   -0.50767,    1.3867,   46.7842},
		{ 118.2968, -121.7104,  -22.4591,  129.1925,  111.0138}
};

#define FILAS_B2LW12		2
#define COLUMNAS_B2LW12		5

float resultadoIntermedio2[3][1] = {
		{1},
		{0},
		{0}
};

#define FILAS_RINTERMEDIO2			3
#define COLUMNAS_RINTERMEDIO2		1

float b3Lw13[1][3] = {
		{0.10407,   -1.0668,    0.14891}
};

#define FILAS_B3LW13		1
#define COLUMNAS_B3LW13		3

float tensionReferenciaN [1][1] = {
		{0}
};

float vRefN;

#define FILAS_VREFN			1
#define COLUMNAS_VREFN		1

/* Definir límites de normalización. */
/* Límites luz.*/
#define LIGHT_UPPER_LIMIT			5.603328000000000e+04
#define LIGHT_LOWER_LIMIT			0

/* Límites temperatura. */
#define TEMPERATURE_UPPER_LIMIT		60.243443080357140
#define TEMPERATURE_LOWER_LIMIT		11.558314732142856

/* Límites valores de tensión. */
#define VOLTAGE_UPPER_LIMIT			3.659422851562499 // TODO: HAY QUE Poner los valores reales. no se si esta bien
#define VOLTAGE_LOWER_LIMIT			1.802882812500000


#endif /* ANN_MEMORY_SAVING_H_ */
