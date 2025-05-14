#ifndef LCD
#define LCD

typedef unsigned char u8;

void lcd_init(void);
void lcd_disp_char(u8 data);
void lcd_command(u8 cmd);  // Forward declaration
void lcd_disp_string(const char *str); 
//void lcd_disp_int(unsigned int integer);
void Cursor_pos(u8 x_pos , u8 y_pos); //x_pos: 0~1 , y_pos:0~15




//testing program---------------------------
/*
// Print "Welcome to" on the first line
	lcd_command(0x80); // Move cursor to the beginning of the first line
	lcd_disp_string("Welcome to");
	
	// Print "Embedded Diploma" on the second line
	lcd_command(0xC0); // Move cursor to the beginning of the second line
	lcd_disp_string("Embedded Diploma");
	
	// Delay to keep the message on the screen for a while
	_delay_ms(2000);
	
	// Clear the screen
	lcd_command(0x01); // Clear display
	
	// Print "Bahaa & Ibrahim" on one line
	lcd_command(0x80); // Move cursor to the beginning of the first line
	lcd_disp_string("Bahaa & Ibrahim");
	
	
	// Delay to keep the message on the screen for a while
	_delay_ms(2000);
	lcd_command(0x01); //Clear Display for another "Welcome ....."
*/


#endif

