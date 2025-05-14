#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"


int main()
{
	lcd_init();
	while(1)
	{	
		lcd_command(0x80); //cursor at 1st line
		lcd_disp_string("CSE 211s:");
		lcd_command(0xC0); //cursor at 2nd line
		lcd_disp_string("Testing Drivers");
		delayMs(3000);
		lcd_command(0x01); //clears display
		delayMs(1000);
	}
}
