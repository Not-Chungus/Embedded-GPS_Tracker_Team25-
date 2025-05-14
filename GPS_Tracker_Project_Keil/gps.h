#ifndef hamo
#define hamo

#include "tm4c123gh6pm.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "UART.h"

// Constants
//#define PI 3.14159265358979323846
#define PI 3.1415927f

// Function prototypes
void GPS_read(void);                     // Function to read GPS data
void GPS_format(void);                   // Function to format the GPS data
float ToDegree(float angle);             // Converts angle to degree format
float ToRad(float angle);                // Converts angle to radians
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat); // Calculates distance between two GPS coordinates
char myStringCompare(char *str1, char *str2);

#endif // GPS_H
