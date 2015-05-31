#include "calculo_error.h"
#include "ANN_implementation.h"
#include "ANN_memory_saving.h"

TrainInputData inputs_tran[SIZE];

static TrainInputData NormalizedInput (TrainInputData input);

ErrorData calculo_errores (uint8_t number_samples, TrainInputData *in_data) {
	ErrorData errores;
	TrainInputData in_dataN;
	float error_aux = 0;
	uint8_t i;

	errores.error_rel_max = 0;
	errores.error_rel_avg = 0;

	for (i = 0; i < number_samples; ++i) {
		in_dataN = NormalizedInput(*in_data);
		#ifdef ANN2LAYERS
			error_aux = (in_data -> vref-Calculo_ANN_2Layer(in_dataN))/in_data->vref;
		#endif

		#ifdef ANN3LAYERS
			error_aux = (in_data -> vref-Calculo_ANN_3Layer(in_dataN))/in_data -> vref;
		#endif

//			errores.error_rel_max >= error_aux;
			errores.error_rel_avg += error_aux;
			++in_data;
	}

	errores.error_rel_avg = errores.error_rel_avg/number_samples;

	return errores;
}

static TrainInputData NormalizedInput (TrainInputData input) {
		TrainInputData inputsN;
		inputsN.lux = (input.lux-LIGHT_LOWER_LIMIT)/(LIGHT_UPPER_LIMIT-LIGHT_LOWER_LIMIT);
		inputsN.temp = (input.temp-TEMPERATURE_LOWER_LIMIT)/(TEMPERATURE_UPPER_LIMIT-TEMPERATURE_LOWER_LIMIT);
		inputsN.vref = (input.vref-VMMP_REF_LOWER_LIMIT)/(VMMP_REF_UPPER_LIMIT-VMMP_REF_LOWER_LIMIT);

		return inputsN;
}
