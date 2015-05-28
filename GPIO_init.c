/*
 * GPIO_init.c
 *
 *  Created on: 25/3/2015
 *      Author: Diego
 */


#include <msp430.h>
#include "GPIO_init.h"

/*
 *  ======== GPIO_Init ========
 *  Initialize MSP430 General Purpose Input Output Ports
 *
 *  The GPIO registers should be set in a specific order:
 *     PxOUT
 *     PxSEL or PxSELx
 *     PxDIR
 *     PxREN
 *     PxIES
 *     PxIFG
 *     PxIE
 *
 *     This will ensure that:
 *         - IFG doesn't get set by manipulating the pin function, edge
 *           select, and pull-up/down resistor functionalities (see
 *           Section 8.2.6 of the MSP430 User's manual)
 *         - Glitch-free setup (configuring the OUT register _before_
 *           setting the pin direction)
 *         - Pull-up/pull-down resistor enable with the correct direction
 *           (.up. vs. .down.)
 */
void GPIO_Init(void)
{

    /* Port 1 Output Register */
    P1OUT = 0;

    /* Port 1 Direction Register */
    P1DIR = BIT0 | BIT1 |  BIT4 | BIT5; // Aqui he añadido el bit 0. // BIT3 | Solo para el el sistema con el modelo.

    /* Port 1 Interrupt Edge Select Register */
    P1IES = 0;

    /* Port 1 Interrupt Flag Register */
    P1IFG = 0;

    /* Port 2 Output Register */
    P2OUT = 0;

    /* Port 2 Direction Register */
    P2DIR = 0;

    /* Port 2 Interrupt Edge Select Register */
    P2IES = 0;

    /* Port 2 Interrupt Flag Register */
    P2IFG = 0;

}
