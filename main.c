#include <msp430.h> 
#include "GPIO_init.h"
#include "ANN_implementation.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    GPIO_Init();
    P1OUT |=  BIT0;
    P1OUT |=  BIT1;
    while (1){
    	//GenerateInArraray(0.0452,0.3404);
// TODO: Eliminar la declaración doble de vatiables.

    	P1OUT &= ~BIT1;
		#ifdef ANN2LAYER
    		Calculo_ANN_2Layer();
		#endif

		#ifdef ANN3LAYER
    		Calculo_ANN_3Layer();
		#endif
    	P1OUT |=  BIT1;

    }
}
