/*  TEST LCD

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

*/

//TEST GPS

#include "gps.h"
#include "UART.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"

extern const double EARTH_RADIUS; // in meters

// Global variables
extern char GPS_logName[];
extern char GPS[80];
extern char GPS_formatted[12][20];
extern char *token;

extern float currentLong, currentLat, speed;
//extern float destLong, destLat;  //should be 5 objects if u use class

int main()
{
	float distance1 = 0;
	UART_init();
	
	while(1)
	{
		GPS_read();    //GPS[] now has "203522,A,5109.029,N,........."
		GPS_format();	 //GPS_formatted[0] = "203522"   //DATE
									 //GPS_formatted[1] = "A"        //Valid
									 //GPS_formatted[2] = "5109.029" //lat
									 //GPS_formatted[1] = "N"        //Valid

									 //and currentLat has the lat from the module and its type is float
									 //and currentLong has the long from the module and its type is float		
		distance1 = GPS_getDistance( currentLong, currentLat, 31.2801565528981 , 30.064103266512063 );
		//                                                     //HallA.long       //HallA.lat
		delayMs(5000);
	}
}







