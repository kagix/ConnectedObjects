#include "constants.h"


// On ESP8266, matching the pins is a nightmare
const uint8_t D5   = 14;
const uint8_t D6   = 12;
const uint8_t D7   = 13;

// The three pins used by the LED matrix
uint8_t pinDIN=D7;
uint8_t pinCLK=D6;
uint8_t pinCS=D5;

int shieldCount = 1;  // One matrix so far. In Arduino language, it is called a shield 
int shieldID = 0;     // 0-based array. One LED matrix could consume 1000mA, so I cannot imagine 
                      // the current needed for a full size display like those used in a bus.

// This should be set first 
const char *ssid = "the SSID of your WiFi network";        
const char *pass = "the password to your WiFi network"; 

const char* host = "the address of the web server who returns the JSON-encoded waiting time";
const int httpsPort = 443; // SSL, that is sure

const char* fingerprint = "the SHA1 fingerprint from the SSL certificate";                      

// I know this is bad practice, but using tabs makes  everything easier to read
const char* TAG_RESULT       = "result";
const char* TAG_ARRIVALS     = "arrivals";
const char* TAG_WAITING_TIME = "waiting_time";
const char* TAG_ARRIVED      = "arrived";
const int   FIRST_ARRIVAL    = 0;

String waitTimeURL = "/<version>/schedules/<bus|tram|subway|train|ferry|funicular|trolleybus>/<line number>/<stop code|stop name>/<way>";

const int TEN_SECONDS = 10000;
const int ONE_SECOND  = 1000;
const int HALF_A_MINUTE = 30000;

