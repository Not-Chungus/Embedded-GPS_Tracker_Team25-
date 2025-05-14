#include "GPIO.h"
#include "tm4c123gh6pm.h"




void delayMs(int n)  // Delay in milliseconds---------------------------------------------
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180; j++) {}  // Calibrated for 16 MHz system clock
}
//----------------------------------------------------------------------------------------


void PORTB_init(void) //initializes portB as digital i/o---------------------------------------
{
	SYSCTL_RCGCGPIO_R |= 1<<1;
	while((SYSCTL_PRGPIO_R & 0x02) == 0); //wait for stable clock init
	
	GPIO_PORTB_LOCK_R = 0x4C4F434B  ; //unlock PORTB
	GPIO_PORTB_CR_R = 0xFF;           //allow changes on all pins
	
	GPIO_PORTB_AMSEL_R = 0x00; //no analog
	GPIO_PORTB_PCTL_R = 0x00000000; //choose GPIO alt fn = 0 on all pins
	GPIO_PORTB_AFSEL_R =0x00;        //disable alt functions
	GPIO_PORTB_DEN_R = 0xFF;         //enable digital all pins
	
	
}
//----------------------------------------------------------------------------------------

void PORTC_init(void)  //initializes PC4 -> PC6 as digital i/o--------------------------------
{
	SYSCTL_RCGCGPIO_R |= 1<<2;
	while((SYSCTL_PRGPIO_R & 0x04) == 0); //wait for stable clock init
	
	GPIO_PORTC_LOCK_R = 0x4C4F434B  ; //unlock PORTC
	GPIO_PORTC_CR_R |= 0x70;           //allow changes PC(4-6)
	
	GPIO_PORTC_AMSEL_R &= ~0x70; //no analog PC4 - PC6
	GPIO_PORTC_PCTL_R &= ~0x0FFF0000; //choose GPIO alt fn = 0 on PC(4-6)
	GPIO_PORTC_AFSEL_R &= ~0x70;        //disable alt functions PC4 - PC6
	GPIO_PORTC_DEN_R |= 0x70;         //enable digital all pins
	
}
//----------------------------------------------------------------------------------------
