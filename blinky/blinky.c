/*	Name:		blinky.c																				*/
/*																									*/
/*	Purpose:	Test Program for STM32VLDiscovery - blinks the LEDs on and off at different rates	*/
/*				(Green = 4 x Slower than Blue). Green is turned off if the button is pressed.		*/
/*																									*/
/*	Created:	21st September 2010																	*/
/*																									*/
/*	Author:		Paul Robson (paul@robsons.org.uk)													*/
/*				Simonsson Fun Techonlogies (original work on code for STM32)						*/
/*																									*/
/****************************************************************************************************/

#include "stm32f10x.h"

#define STACK_TOP 0x20002000										/* This can move quite a lot ! */

void nmi_handler(void);												
void hardfault_handler(void);
void delay(void);
int main(void);

/*	Four vectors - the starting stack pointer value, code entry point and NMI and Hard-Fault handlers */

unsigned int * myvectors[4] 
__attribute__ ((section("vectors")))= {
    (unsigned int *)	STACK_TOP,         
    (unsigned int *) 	main,              
    (unsigned int *)	nmi_handler,       
    (unsigned int *)	hardfault_handler  
};


int main(void){	
	int n = 0;
	int button;

	RCC->APB2ENR |= 0x10 | 0x04;									/* Enable the GPIOA (bit 2) and GPIOC (bit 8) */
	GPIOC->CRH = 0x11;												/* Set GPIOC Pin 8 and Pin 9 to outputs */
	GPIOA->CRL = 0x04;												/* Set GPIOA Pin 0 to input floating */

    while(1)
    {
		delay();													/* A short delay */
		button = ((GPIOA->IDR & 0x1) == 0);							/* Read the button - the button pulls down PA0 to logic 0 */
		n++;														/* Count the delays */
		if (n & 1) {												/* Copy bit 0 of counter into GPIOC:Pin 8 */
			GPIOC->BSRR = 1<<8 ; 
		} else { 
			GPIOC->BSRR = 1<<24;	
		}
		if ((n & 4) && button) {									/* Copy bit 4 of counter into GPIOC:Pin 9 if button pressed */
			GPIOC->BSRR = 1<<9 ; 
		} else { 
			GPIOC->BSRR = 1<<33;	
		}
    }
}

void delay(void) 
{
	int i = 100;													/* About 1/4 second delay */
	while (i-- > 0) {
		asm("nop");													/* This stops it optimising code out */
	}
}

void nmi_handler(void)
{
    return ;
}

void hardfault_handler(void)
{
    return ;
}

