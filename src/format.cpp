#include <string>

#include "format.h"

using namespace std;;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    char cstring[40];
    int hours = seconds/3600;
    int remainig = seconds%3600;
    int minutes = remainig/60;
    int s = remainig%60;
    sprintf(cstring,"%.2d:%.2d:%.2d",hours,minutes,s);
    return cstring;
    
}