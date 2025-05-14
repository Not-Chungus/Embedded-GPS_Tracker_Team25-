#include "gps.h"
#include "LCD.h"
#include "UART.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"


//#define PI 3.14159265358979323846
#define PI 3.1415927f

extern char GPS_logName[];
extern char GPS[100] ;
extern char GPS_formatted[12][30];
extern char *token;

extern float currentLong;
extern float currentLat;
extern const double EARTH_RADIUS; // in meters
//float destLong, destLat;


//****** SERVICES ******//

void GPS_read(){

	char recievedChar,flag ;
	char i = 0 ;
	char fillGPScounter = 0 ;

	do{
			flag = 1 ;
			for( i=0 ; i<7 ;i++) {
			if (UART2_GetChar() != GPS_logName[i]) {
				flag = 0 ; break ;
			}
			}
	}
	while(flag==0);

	// Here I make sure that I recieved the correct log

	strcpy(GPS , ""); //Init GPS Array

	do{   
			recievedChar = UART2_GetChar();
			if (fillGPScounter < sizeof(GPS) - 1) {
							GPS[fillGPScounter++] = recievedChar;
							//U0_print_char_to_PC(GPS[fillGPScounter - 1]);
							//lcd_disp_char(GPS[fillGPScounter - 1]);
					} else {
							break; // Prevent buffer overrun
					}
	}while(recievedChar!='*');

	GPS[fillGPScounter] = '\0';
	U0_print_string_toPC(GPS);

}

/*
void GPS_format(){
    char noOfTokenStrings = 0 ;
    token = strtok(GPS , ",") ;
    do{
    strcpy (GPS_formatted[noOfTokenStrings],token);
    token = strtok(NULL , ",");
    noOfTokenStrings++;
		}while(token!=NULL);


		if(strcmp(GPS_formatted[1],"A")==0){ //Valid

    if(strcmp(GPS_formatted[3],"N")==0)
    currentLat = atof(GPS_formatted[2]);
    else
    currentLat = -atof(GPS_formatted[2]);

    if(strcmp(GPS_formatted[5],"E")==0)
    currentLong = atof(GPS_formatted[4]);
    else
    currentLong = -atof(GPS_formatted[4]);
		}
		
}
*/

void GPS_format() {
	
    int gpsIndex = 0;
    int tokenIndex = 0;
    int charIndex = 0;

    while (GPS[gpsIndex] != '\0' && tokenIndex < 12) {
        if (GPS[gpsIndex] == ',') {
            GPS_formatted[tokenIndex][charIndex] = '\0'; // End current token
            tokenIndex++;
            charIndex = 0;
        } else {
            if (charIndex < 19) { // prevent overflow
                GPS_formatted[tokenIndex][charIndex++] = GPS[gpsIndex];
            }
        }
        gpsIndex++;
    }

    // Handle final token if the string doesn't end with ','

		
    if (myStringCompare(GPS_formatted[1], "A")) {			  
        currentLat = atof(GPS_formatted[2]);
				currentLong = atof(GPS_formatted[4]);
				
        
			if (myStringCompare(GPS_formatted[3], "S"))
						currentLat = -currentLat;
        
        if (myStringCompare(GPS_formatted[5], "W"))
						currentLong = -currentLong;

		}
		
}



float ToDegree(float angle){
    int degree = (int)angle / 100 ;
    float minutes = angle - (float)degree*100;
    return(degree+ (minutes/60));
}

float ToRad(float angle){
    return (float)angle * PI / 180 ;
}

		float GPS_getDistance(float currentLong , float currentLat , float destLong ,float destLat){
    float currentLongRad = ToRad(ToDegree(currentLong));
    float currentLatRad = ToRad(ToDegree(currentLat));
    float destLongRad = ToRad(destLong);
    float destLatRad = ToRad(destLat);

    float longDiff = destLongRad - currentLongRad ;
    float latDiff = destLatRad - currentLatRad ;

    float a = pow(sin(latDiff/2),2)+cos(currentLatRad)*cos(destLatRad)
    *pow(sin(longDiff/2),2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c ;
}
		
char myStringCompare(char *str1, char *str2) {
    char i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return 0; // Strings are different
        }
        i++;
    }
    // If both ended at the same time, strings are equal
    return (str1[i] == str2[i]);
}
