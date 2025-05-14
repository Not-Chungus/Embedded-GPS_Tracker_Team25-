#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"
#include "UART.h"

// UART INIT

void UART_init(){
    SET_BIT(SYSCTL_RCGCUART_R , 0 ); // CLOCK --> UART2
    while(GET_BIT(SYSCTL_PRUART_R,0)==0);
    SET_BIT(SYSCTL_RCGCGPIO_R , 0 ); // CLOCK --> POSTD
    while(GET_BIT(SYSCTL_PRGPIO_R,0)==0);
    
    CLR (UART0_CTL_R ,UART_CTL_UARTEN); // DISABLE UART
    UART0_IBRD_R = 104 ; // 104
    UART0_FBRD_R = 11 ; // (0.1667*64)+0.5
	
    SET(UART0_LCRH_R,UART_LCRH_WLEN_8); // WORDLENGTH = 3
    SET(UART0_LCRH_R,UART_LCRH_FEN); // FIFO ENABLE
	  //SELECT TYPE OF ALTERNATE FUNC
	  CLR(GPIO_PORTA_PCTL_R , 0x000000FF);    // Alter func for PD6 , PD7
	  SET(GPIO_PORTA_PCTL_R , GPIO_PCTL_PA0_U0RX);    // PD6 --> RX
		SET(GPIO_PORTA_PCTL_R , GPIO_PCTL_PA1_U0TX);    // PD7 --> TX
		SET(GPIO_PORTA_DEN_R , 0x3) ;    // PD0 , PD1 --> DIGITAL
}
	int UART_IsCharAvail()
  {
    return ( ( UART0_FR_R & UART_FR_RXFE ) == 0 );
  }

	// GET CHAR
	char UART_GetChar() {
	while( (UART0_FR_R & UART_FR_RXFE) != 0);
	return (char) GET_REG(UART0_DR_R); //#0xff
	}
	
	
	
	