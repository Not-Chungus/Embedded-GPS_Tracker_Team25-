#include "tm4c123gh6pm.h"
#include "Bit_Utilies.h"
#include "UART.h"

// UART INIT

void UART2_init(){
    SYSCTL_RCGCUART_R |= (1 << 2);   // Enable UART2 clock
    SYSCTL_RCGCGPIO_R |= (1 << 3);   // Enable Port D clock
    while ((SYSCTL_PRGPIO_R & (1 << 3)) == 0); // Wait for Port D to be ready

    GPIO_PORTD_AFSEL_R |= (1 << 6) | (1 << 7);      // Enable alt function on PD6, PD7
    GPIO_PORTD_PCTL_R &= ~0xFF000000;               // Clear PCTL for PD6/PD7
    GPIO_PORTD_PCTL_R |=  0x11000000;               // Configure PCTL for UART2
    GPIO_PORTD_DEN_R   |= (1 << 6) | (1 << 7);      // Enable digital I/O on PD6/PD7
    GPIO_PORTD_AMSEL_R &= ~((1 << 6) | (1 << 7));   // Disable analog on PD6/PD7

    UART2_CTL_R &= ~UART_CTL_UARTEN;

    UART2_IBRD_R = 104;       // Integer part
    UART2_FBRD_R = 11;        // Fractional part (0.1667 * 64 + 0.5 ˜ 11)

    UART2_LCRH_R = UART_LCRH_WLEN_8;  // 8 data bits, no parity, 1 stop bit
		UART2_CC_R = 0x00;                //system clk
    UART2_CTL_R |= UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE;
}

	int UART2_IsCharAvail()
  {
    return ( ( UART2_FR_R & UART_FR_RXFE ) == 0 );
  }

	// GET CHAR
	char UART2_GetChar() {
	while( (UART2_FR_R & UART_FR_RXFE) != 0);
	return (char) GET_REG(UART2_DR_R); //#0xff
	}

void UART0_init(void){
	SYSCTL_RCGCUART_R |= (1<<0); // CLOCK --> UART0
	SYSCTL_RCGCGPIO_R |= (1<<0); // CLOCK --> PORTA	
	GPIO_PORTA_AFSEL_R |= 0x03;  //
	GPIO_PORTA_PCTL_R |= (0x00000011); // PA0, PA1   
	GPIO_PORTA_DEN_R |= 0x03;
	
	UART0_CTL_R &= ~(1<<0); //disable UART
	UART0_IBRD_R = 104 ; // 104
  UART0_FBRD_R = 11 ; // (0.1667*64)+0.5
	UART0_LCRH_R = (0x3<<5); //8-bits, no parity, 1 stop
	UART0_CC_R = 0x00;    //system_clk
	UART0_CTL_R |= (1<<0) | (1<<8) | (1<<9); //UARTEN, TxE, RxE
	
}

void U0_print_char_to_PC(char c)
{
	while((UART0_FR_R & (1<<5)) != 0);
	UART0_DR_R = c;
}

char U0_read_char_fromPC(void)
{
	char c;
	while((UART0_FR_R & (1<<4)) != 0);
	c =  UART0_DR_R;
	return c;
}

void U0_print_string_toPC(char* string)
{
	while(*string)
	{
		U0_print_char_to_PC(*string);
		string++;
	}
}
