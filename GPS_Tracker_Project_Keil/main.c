//final main program---------------------------------------------------------------------------------------------------------


#include <stdio.h>
#include "gps.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "GPIO.h"



// Global variables
const double EARTH_RADIUS= 6371000; // in meters
char GPS_logName[] = "$GPRMC,";
char GPS[100];
char GPS_formatted[12][20];
char *token;

//extern float destLong, destLat;  //should be 5 objects if u use class
float currentLong, currentLat;
int indexi=0,i;
double min_dist=1000, distancei=0;

typedef struct {
     float latitude;  // Latitude value
     float longitude; // Longitude value
} GpsCoordinate;


#define NUM_POINTS 5
GpsCoordinate gpsPoints[NUM_POINTS] = {
    {30.064284125453856f, 31.280274666862596f},
    {30.063658902119883f, 31.280565036468566f},
    {30.063508782938f, 31.278410970087688f},
    {30.06507928725851f, 31.280180974591516f},
    {30.06431351904756f, 31.277791201596546f} //Concrete Buidling
};


const char *hallNames[] = {
	"Hall A/B",
	"Hall C/D",
	"Credit Halls",
	"library",
	"Concrete Build."
		
};


int main()
{
	//Init_PortF();
	PORTE_init();
  PORTB_init();
	PORTC_init();
	UART2_init();
	lcd_init();
	UART0_init();

// Initializig LCD to Show Course Name and Testing
	GPIO_PORTC_DIR_R |= 1<<7;
  //GPIO_PORTC_DATA_R |= 1<<7;	
	lcd_command(0x80); //cursor at 1st line
	lcd_disp_string("FACULTY OF ENGINEERING");
	lcd_command(0xC0); //cursor at 2nd line
	lcd_disp_string("AIN SHAMS UNIVERSITY");
	delayMs(2000);
	lcd_command(0x01); //clears display

	lcd_command(0x80); //cursor at 1st line
	lcd_disp_string("Welcome!");
	lcd_command(0xC0); //cursor at 2nd line
	lcd_disp_string("CSE 211s");
	delayMs(2000);
	lcd_command(0x01); //clears display
	
	
	
	
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

			min_dist=1000;
			for( i=0 ; i<5 ; i++ ){
				distancei = GPS_getDistance( currentLong, currentLat, gpsPoints[i].longitude , gpsPoints[i].latitude );
						
				if( distancei < min_dist ){
					min_dist = distancei;
					indexi = i;
				}
			}
			
			if(min_dist < 70.00f){
				GPIO_PORTE_DATA_R = 0x04; //red off green on Elbeda E2    eswad E3
				lcd_command(0x80); //cursor at 1st line
				lcd_disp_string("Nearest Landmark");
				lcd_command(0xC0); //cursor at 2nd line
				lcd_disp_string( hallNames[indexi]);
				delayMs(1000);
				lcd_command(0x01); //clears display
			}
			else
				{	
					GPIO_PORTE_DATA_R = 0x08; //red on green off
					lcd_command(0x80); //cursor at 1st line
					lcd_disp_string("No LANDMARK");
					lcd_command(0xC0); //cursor at 2nd line
					lcd_disp_string("In Range");
					delayMs(1000);
					lcd_command(0x01); //clears display
				}
			if(min_dist <18.00f)
				GPIO_PORTC_DATA_R ^= 1<<7;   //buzzer toggling
			else
				GPIO_PORTC_DATA_R &= ~(1<<7); //buzzer off
				
	}
}
