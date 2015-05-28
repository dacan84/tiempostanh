/*
 * ANN_implementation.c
 *
 *  Created on: 10/3/2015
 *      Author: Diego
 */

#include <stdio.h>
#include <stdint.h>
//#include <math.h>
#include "ANN_implementation.h"
#include "ANN_memory_saving.h"
//#include "../adc/averaged_adc.h"
//#include "../sensores/Light.h"

/* La matriz de entrada esta compuesta por 3 elementos:
 * [el primer elemento corresponde al umbral, Luz, Temperatura]. */
float inputsN[3][1];

/* La matriz de salida constara de uno o 2 elementos. */
//float output[1]; // La dimensión dependera del vector de salida.

static void ClearArrays(void);

void GenerateInArraray(float l, float t) {
	inputsN[0][0] = 1;
	inputsN[1][0] = l;
	inputsN[2][0] = t;
	//inputsN [1][0] = (measLigth()-LIGHT_LOWER_LIMIT)/(LIGHT_UPPER_LIMIT-LIGHT_LOWER_LIMIT);
	//inputsN [2][0] = (AdqTa()-TEMPERATURE_LOWER_LIMIT)/(TEMPERATURE_UPPER_LIMIT-TEMPERATURE_LOWER_LIMIT);
}

static void ClearArrays(void) {
	uint8_t i = 1;

	for (i = 1; i < FILAS_RINTERMEDIO1; ++i) {
		resultadoIntermedio1[i][0] = 0;
		if (i < FILAS_RINTERMEDIO2) {
			resultadoIntermedio2[i][0] = 0;
		}
	}
	tensionReferenciaN[0][0] = 0;
}

float CalTanh(float x) {
	float resul;

	if (x <= -5.3) {
		resul = -1;
	} else if (x >= 5.3) {
		resul = 1;
	} else if ((x > -5.3) && (x < -0.9)) {
		// resul = 0.0127*x*x*x+0.1435*x*x+0.5234*x-0.3840;
		resul = 0.0014 * x * x * x * x * x + 0.0273 * x * x * x * x
				+ 0.2043 * x * x * x + 0.7599 * x * x + 1.4179 * x + 0.0746;
	} else if ((x > 0.9) && (x < 5.3)) {
		//resul =  0.0127*x*x*x-0.1435*x*x+0.5234*x+0.3840;
		resul = 0.0014 * x * x * x * x * x - 0.0273 * x * x * x * x
				+ 0.2043 * x * x * x - 0.7599 * x * x + 1.4179 * x - 0.0746;
	}  else if ((x >= -0.9) && (x <= 0.9)) {
		//resul = x-(1/3)*x*x*x+(2/15)*x*x*x*x*x-17/315*x*x*x*x*x*x*x;
		resul = -0.2358 * x * x * x + 0.9834 * x;
	}

	return resul;
}



/* La operacion tangente hipperbólica requiere variables float con la funcion declarada previamente*/
void Calculo_ANN (void) {
	uint8_t i, j, z;
	//inputsN [0][0] = 1;
	//inputsN [1][0] = (measLigth()-LIGHT_LOWER_LIMIT)/(LIGHT_UPPER_LIMIT-LIGHT_LOWER_LIMIT);
	//inputsN [2][0] = (AdqTa()-TEMPERATURE_LOWER_LIMIT)/(TEMPERATURE_UPPER_LIMIT-TEMPERATURE_LOWER_LIMIT);

	vRefN = 0;

	/*
	 % A con k filas y m columnas, t = size(A)
	 % k = t(1); m = t(2);
	 % B con m filas y n columnas. s = size(B)
	 % m = s(1); n = s(2);
	 % C es la matriz que resulta del producto AB.
	 % C presenta k filas y n columnas.
	 %
	 % C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j]
	 % + ... + A[i][m-1] * B[m-1][j]
	 % */

	i = 0;
	j = 0;
	z = 0;
	// Generamos la matriz C.
	for (i = 0; i < FILAS_B1IW11; ++i) {
		for (j = 0; j < COLUMNAS_INPUTS; ++j) {
			for (z = 0; z < FILAS_INPUTS; ++z) {
				resultadoIntermedio1[i + 1][j] = resultadoIntermedio1[i + 1][j]
						+ b1Iw11[i][z] * inputsN[z][j];
			}
		}
	}

	i = 1;
	for (i = 1; i < FILAS_RINTERMEDIO1; ++i) {
		resultadoIntermedio1[i][0] = (float) CalTanh(
				resultadoIntermedio1[i][0]);
	}

	i = 0;
	j = 0;
	z = 0;
	// Generamos la matriz C.
	for (i = 0; i < FILAS_B2LW12; ++i) {
		for (j = 0; j < COLUMNAS_RINTERMEDIO1; ++j) {
			for (z = 0; z < FILAS_RINTERMEDIO1; ++z) {
				resultadoIntermedio2[i + 1][j] = resultadoIntermedio2[i + 1][j]
						+ b2Lw12[i][z] * resultadoIntermedio1[z][j];
			}
		}
	}

	i = 1;
	for (i = 1; i < FILAS_RINTERMEDIO2; ++i) {
		resultadoIntermedio2[i][0] = (float) CalTanh(
				resultadoIntermedio2[i][0]);
	}

	i = 0;
	j = 0;
	z = 0;
	// Generamos la matriz C.
	for (i = 0; i < FILAS_B3LW13; ++i) {
		for (j = 0; j < COLUMNAS_RINTERMEDIO2; ++j) {
			for (z = 0; z < FILAS_RINTERMEDIO2; ++z) {
				tensionReferenciaN[i][j] = tensionReferenciaN[i][j]
						+ b3Lw13[i][z] * resultadoIntermedio2[z][j];
				vRefN = (float) tensionReferenciaN[i][j];// funcion de salida es lineal con ganancia unidad.
			}
		}
	}
	ClearArrays();
}

float VoltrageReference(float VRefN) {
	//float 		VrefAux = 0;
	float Vref = 0;

	Vref = (VRefN + VOLTAGE_LOWER_LIMIT)
			* (VOLTAGE_UPPER_LIMIT - VOLTAGE_LOWER_LIMIT);

	return Vref;
}

/* La operacion tangente hipperbólica requiere variables de tipo double tanh(x) en la libreria matematica estandar*/
/*
void ANNCalculus(void) {
	uint8_t i, j, z;

	//inputsN [0][0] = 1;
	//inputsN [1][0] = (measLigth()-LIGHT_LOWER_LIMIT)/(LIGHT_UPPER_LIMIT-LIGHT_LOWER_LIMIT);
	//inputsN [2][0] = (AdqTa()-TEMPERATURE_LOWER_LIMIT)/(TEMPERATURE_UPPER_LIMIT-TEMPERATURE_LOWER_LIMIT);
	//GenerateInArraray(0.0,0.0);
	//vRefN = 0;

	 // A con k filas y m columnas, t = size(A)
	 // k = t(1); m = t(2);
	 // B con m filas y n columnas. s = size(B)
	 // m = s(1); n = s(2);
	 // C es la matriz que resulta del producto AB.
	 // C presenta k filas y n columnas.
	 //
	 // C[i][j] = A[i][0] * B[0][j] + A[i][1] * B[1][j] + A[i][2] * B[2][j]
	 // + ... + A[i][m-1] * B[m-1][j]
	 //

	i = 0;
	j = 0;
	z = 0;

	// Generamos la matriz C.
	for (i = 0; i < FILAS_B1IW11; ++i) {
		for (j = 0; j < COLUMNAS_INPUTS; ++j) {
			for (z = 0; z < FILAS_INPUTS; ++z) {
				resultadoIntermedio1[i + 1][j] = resultadoIntermedio1[i + 1][j]
																			 + b1Iw11[i][z] * inputsN[z][j];
			}
		}
	}

	i = 1;
	for (i = 1; i < FILAS_RINTERMEDIO1; ++i) {
		resultadoIntermedio1[i][0] = (float) tanh(resultadoIntermedio1[i][0]);
	}

	i = 0;
	j = 0;
	z = 0;
	// Generamos la matriz C.
	for (i = 0; i < FILAS_B2LW12; ++i) {
		for (j = 0; j < COLUMNAS_RINTERMEDIO1; ++j) {
			for (z = 0; z < FILAS_RINTERMEDIO1; ++z) {
				resultadoIntermedio2[i + 1][j] = resultadoIntermedio2[i + 1][j]
																			 + b2Lw12[i][z] * resultadoIntermedio1[z][j];
			}
		}
	}

	i = 1;
	for (i = 1; i < FILAS_RINTERMEDIO2; ++i) {
		resultadoIntermedio2[i][0] = (float) tanh(resultadoIntermedio2[i][0]);
	}

	i = 0;
	j = 0;
	z = 0;
	// Generamos la matriz C.
	for (i = 0; i < FILAS_B3LW13; ++i) {
		for (j = 0; j < COLUMNAS_RINTERMEDIO2; ++j) {
			for (z = 0; z < FILAS_RINTERMEDIO2; ++z) {
				tensionReferenciaN[i][j] = tensionReferenciaN[i][j]
																 + b3Lw13[i][z] * resultadoIntermedio2[z][j];
				vRefN = (float) tensionReferenciaN[i][j]; //Como es la funcion identidad y como todo se hace en una operación no hay problema.
			}
		}
	}
	ClearArrays();
}*/


