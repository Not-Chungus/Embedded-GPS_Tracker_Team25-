#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"


void lcd_init() 
	{
	LCD_Data_ddr |= 0xFF;   // Set data port as output  (PB0-PB7)
	LCD_Control_ddr |= 0x70; // Set control pins as output(PC4-PC6)
	delayMs(20); // LCD power ON delay
	lcd_command(0x38); // Function set: 8-bit, 2 line, 5x7 dots
	lcd_command(0x0C); // Display ON, Cursor OFF
	lcd_command(0x06); // Entry mode, auto increment with no shift
	lcd_command(0x01); // Clear display
	delayMs(2);
}
	
void lcd_disp_char(u8 data) {  // Display character
	LCD_Control_port &= ~(1 << RW_pin);
	LCD_Control_port |= 1 << RS_pin;
	LCD_Data_port |= data;
	LCD_Control_port |= 1 << E_pin;
	delayMs(1);
	LCD_Control_port &= ~(1 << E_pin);
	delayMs(1);
}

void lcd_command(u8 cmd) {  // Send command
	LCD_Control_port &= ~(1 << RW_pin);
	LCD_Control_port &= ~(1 << RS_pin);
	LCD_Data_port = cmd;
	LCD_Control_port |= 1 << E_pin;
	delayMs(1);
	LCD_Control_port &= ~(1 << E_pin);
	delayMs(1);
}

void lcd_disp_string(const char *str) {  // Display string
	char i = 0;
	for (i = 0; str[i] != '\0'; i++) {
		lcd_disp_char(str[i]);
		delayMs(10); // Reduced delay for faster display
	}
}

//


void Cursor_pos(u8 x_pos , u8 y_pos){
	u8 Adress = 0x80;
	if(x_pos == 0)
	Adress = 0x80;
	else if(x_pos==1)
	Adress = 0xC0;
	if(y_pos<16)
	Adress += y_pos;
	lcd_command(Adress);
}
