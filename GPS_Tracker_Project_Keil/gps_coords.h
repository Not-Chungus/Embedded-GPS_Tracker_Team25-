#ifndef GPS_COORDS_H 
#define GPS_COORDS_H

#include <stdint.h> 

// Define a structure to hold a single geographic coordinate (latitude and longitude)
typedef struct {
    float latitude;  // Latitude value
    float longitude; // Longitude value
} GpsCoordinate;

// Define the number of points 
#define NUM_POINTS 5


extern GpsCoordinate gpsPoints[NUM_POINTS];

#endif 
