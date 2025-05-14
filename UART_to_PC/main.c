#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "GPIO.h"
void Init_PortF(void);
void red_led(char state);
void green_led(char state);
void blue_led(char state);
void UART0_init(void);
void print_char(char c);
char read_char(void);
void print_string(char* string);
void read_string(char* buffer, int max_length);



int main(void){
	
	char message[20];
	UART0_init();
	Init_PortF();
	green_led(1);
	PORTB_init();
	PORTC_init();
	lcd_init();
	
	
	
	
	
	while(1)
	{
		print_string("\nWrite something to the LCD: (max = 16)\n\r");
		read_string(message, 16);
		green_led(0);
		red_led(1);
		lcd_command(0x01); //clears display
		lcd_command(0x80); //cursor at 1st line
		lcd_disp_string(message);
		green_led(1);
		red_led(0);
		print_string("\nWrite something to the LCD: (max = 16)\n\r");
		lcd_command(0xC0); //cursor at 2nd line
		read_string(message, 16);
		green_led(0);
		red_led(1);
		lcd_disp_string(message);
		green_led(1);
		red_led(0);
	}
	
	
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


void print_char(char c)
{
	while((UART0_FR_R & (1<<5)) != 0);
	UART0_DR_R = c;
}


char read_char(void)
{
	char c;
	while((UART0_FR_R & (1<<4)) != 0);
	c =  UART0_DR_R;
	return c;
}

void read_string(char* buffer, int max_length) //max =16 for LCD
{
	char i = 0;
	char c;
	
	while(i < max_length - 1)
	{
		c = read_char();
		if(c == '\r' || c == '\n')
			break;
		buffer[i++] = c;
		print_char(c); //echo it back
	}
	buffer[i] = '\0';
}

void print_string(char* string)
{
	while(*string)
	{
		print_char(*string);
		string++;
	}
}
