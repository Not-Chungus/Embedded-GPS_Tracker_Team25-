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
	SYSCTL_RCGCGPIO_R |= 0x02;
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
	GPIO_PORTC_CR_R |= 0xF0;           //allow changes PC(4-6)
	
	GPIO_PORTC_AMSEL_R &= ~0xF0; //no analog PC4 - PC6
	GPIO_PORTC_PCTL_R &= ~0xFFFF0000; //choose GPIO alt fn = 0 on PC(4-6)
	GPIO_PORTC_AFSEL_R &= ~0xF0;        //disable alt functions PC4 - PC6
	GPIO_PORTC_DEN_R |= 0xF0;         //enable digital all pins
	
}
//----------------------------------------------------------------------------------------



void Init_PortF(void){
    SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock for Port F
    while((SYSCTL_PRGPIO_R&0x20)==0){}; // Wait for clock to be ready
    
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock Port F
    GPIO_PORTF_CR_R = 0x1F; // Commit changes to Port F 
    
    GPIO_PORTF_AMSEL_R = 0x00; // Disable analog function 
    GPIO_PORTF_PCTL_R = 0x00000000; // Clear PCTL register 
    GPIO_PORTF_AFSEL_R = 0x00; // Disable alternate function 
    
    GPIO_PORTF_DEN_R = 0x1F;  // Enable digital function for PF0-PF4
    GPIO_PORTF_DIR_R = 0x1F; // Set direction for PF0-PF4 as output
}



void red_led(char state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x02; // turn on red LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x02; // turn off red LED
    }
}

void green_led(char state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x08; // turn on green LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x08; // turn off green LED
    }
}

void blue_led(char state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x04; // turn on blue LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x04; // turn off blue LED
    }
}
