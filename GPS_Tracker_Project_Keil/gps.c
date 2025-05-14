#include "gps.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"


//#define PI 3.14159265358979323846
#define PI 3.1415927f

char GPS_logName[] = "$GPRMC,";
char GPS[80];
char GPS_formatted[12][20];
char *token;

float currentLong, currentLat, speed;
const double EARTH_RADIUS = 6371000; // in meters
//float destLong, destLat;


//****** SERVICES ******//
void GPS_read(){

char recievedChar,flag ;
char i = 0 ;

do{
    flag = 1 ;
    for( i=0 ; i<7 ;i++) {
    if (UART_GetChar() != GPS_logName[i]) {
    flag = 0 ; break ;
    }
    }
}
while(flag==0);

// Here I make sure that I recieved the correct log

strcpy(GPS , ""); //Init GPS Array

do{
    char fillGPScounter = 0 ;
    recievedChar = UART_GetChar();
    GPS[fillGPScounter++] = recievedChar ;
}while(recievedChar!='*');

}
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
    float destLongRad = ToRad(ToDegree(destLong));
    float destLatRad = ToRad(ToDegree(destLat));

    float longDiff = destLongRad - currentLongRad ;
    float latDiff = destLatRad - currentLatRad ;

    float a = pow(sin(latDiff/2),2)+cos(currentLatRad)*cos(destLatRad)
    *pow(sin(longDiff/2),2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_RADIUS * c ;
}
