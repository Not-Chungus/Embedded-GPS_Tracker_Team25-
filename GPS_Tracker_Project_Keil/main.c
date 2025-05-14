/**
//TEST LCD--------------------------------------------------------------------------------------------------------

#include "LCD.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"


int main()
{
	PORTB_init();
	PORTC_init();
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
//-----------------------------------------------------------------------------------------------------------------
*/


/*

//TEST UART-------------------------------------------------------------------------------------------------------
#include "tm4c123gh6pm.h"
#include "UART.h"

int main(void) {
    char c;
    UART_init();  // Initialize UART5

    while (1) {
        if (UART_IsCharAvail()) {  // Check if a char is available
            c = UART_GetChar();    // Read the char
            while (UART2_FR_R & UART_FR_TXFF);  // Wait if TX FIFO is full
            UART2_DR_R = c;        // Echo it back
        }
    }
}
//------------------------------------------------------------------------------------------------------


*/


/*
//TEST GPS---------------------------------------------------------------------------------------------------------

#include "gps.h"
#include "UART.h"
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
		delayMS(5000);
	}
}

//-----------------------------------------------------------------------------------------------------------------*/











//TEST FINAl--------------------------------------------------------------------------------------------


//#include <stdio.h>
#include "gps.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "GPIO.h"
#include "gps_coords.h" 




extern const double EARTH_RADIUS; // in meters

// Global variables
extern char GPS_logName[];
extern char GPS[80];
extern char GPS_formatted[12][20];
extern char *token;

extern float currentLong, currentLat, speed;
//extern float destLong, destLat;  //should be 5 objects if u use class
char indexi=0,i;
float min_dist=1000, distancei=0;


const char *hallNames[] = {
	"Hall A/B",
	"Hall C/D",
	"Credit Halls",
	"Hall 505",
	"Palestine Hall"
		
};


int main()
{
	PORTB_init();
	PORTC_init();
	UART_init();
	lcd_init();

// Initializig LCD to Show Course Name and Testing
	lcd_command(0x80); //cursor at 1st line
	lcd_disp_string("FACULTY OF ENGINEERING");
	lcd_command(0xC0); //cursor at 2nd line
	lcd_disp_string("AIN SHAMS UNIVERSITY");
	delayMs(3000);
	lcd_command(0x01); //clears display
	delayMs(1000);



	lcd_command(0x80); //cursor at 1st line
	lcd_disp_string("Welcome!");
	lcd_command(0xC0); //cursor at 2nd line
	lcd_disp_string("CSE 211s");
	delayMs(3000);
	lcd_command(0x01); //clears display
	delayMs(1000);
	
	
	
	
	while(1)
	{
		
		GPS_read();    //GPS[] now has "203522,A,5109.029,N,........."
		GPS_format();	 //GPS_formatted[0] = "203522"   //DATE
									 //GPS_formatted[1] = "A"        //Valid
									 //GPS_formatted[2] = "5109.029" //lat
									 //GPS_formatted[1] = "N"        //Valid

									 //and currentLat has the lat from the module and its type is float
									 //and currentLong has the long from the module and its type is float		
		//distancei = GPS_getDistance( currentLong, currentLat, gpsPoints[0].longitude , gpsPoints[0].latitude );
		//                                                     //HallA.long              //HallA.lat
			for( i=0 ; i<5 ; i++ ){
				distancei = GPS_getDistance( currentLong, currentLat, gpsPoints[i].longitude , gpsPoints[i].latitude );
					
				if( distancei < min_dist ){
					min_dist = distancei;
					indexi = i;
				}						
			}
			lcd_command(0x80); //cursor at 1st line
			lcd_disp_string("nearest Hall");
			lcd_command(0xC0); //cursor at 2nd line
			lcd_disp_string( hallNames[indexi]);
			delayMs(3000);
			lcd_command(0x01); //clears display
			delayMs(1000);
	}
}

//----------------------------------------------------------------------------------------------------------
