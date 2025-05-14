#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"
#include "UART.h"
#include "GPIO.h"

// UART5 INIT

void UART_init(){
		SYSCTL_RCGCGPIO_R |= 0x08; // CLOCK --> PORTD
		while((SYSCTL_PRGPIO_R & 1<<3) ==0){};
		GPIO_PORTD_LOCK_R = 0x4C4F434B;
		GPIO_PORTD_CR_R |= 0xC0;
		
    SYSCTL_RCGCUART_R |= 0x04; // CLOCK --> UART2
 	  while((SYSCTL_PRUART_R & 1<<2) == 0){};
    
    
    CLR (UART2_CTL_R ,UART_CTL_UARTEN); // DISABLE UART
	
    UART2_IBRD_R = 104 ; // 104
    UART2_FBRD_R = 11 ; // (0.1667*64)+0.5
	
    SET(UART2_LCRH_R,UART_LCRH_WLEN_8); // WORDLENGTH = 3 (8bits)
    SET(UART2_LCRH_R,UART_LCRH_FEN); // FIFO ENABLE

	
		UART2_CTL_R |= UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE; //RE-ENABLE UART2, RX, TX
	  //SELECT TYPE OF ALTERNATE FUNC
	  GPIO_PORTD_AFSEL_R |= 0xC0;  // Enable alt function on PE4, PE5
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & ~0xFF000000) | (0x11000000); // PD6, PD7 = U2RX, U2TX
    GPIO_PORTD_DEN_R |= 0xC0;    // Digital enable on PD6, PD7
    GPIO_PORTD_AMSEL_R &= ~0xC0; // Disable analog on PD6, PD7
	
		
}
int UART_IsCharAvail()
{
   return ( ( UART2_FR_R & UART_FR_RXFE ) == 0 );
}

	// GET CHAR
char UART_GetChar() {
while( (UART2_FR_R & UART_FR_RXFE) != 0);
return (char) GET_REG(UART2_DR_R); //#0xff
}	
