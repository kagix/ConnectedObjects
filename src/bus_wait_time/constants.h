#ifndef WAITING_TIME_CONSTANTS_H
#define WAITING_TIME_CONSTANTS_H

extern const uint8_t D5;
extern const uint8_t D6;
extern const uint8_t D7;

// The three pins used by the LED matrix
extern uint8_t pinDIN;
extern uint8_t pinCLK;
extern uint8_t pinCS;

extern int shieldCount;  // One matrix so far. In Arduino language, it is called a shield 
extern int shieldID;     // 0-based array. One LED matrix could consume 1000mA, so I cannot imagine 
                      // the current needed for a full size display like those used in a bus.

// This should be set first 
extern const char* ssid;        
extern const char* pass; 


extern const char* host;
extern const int httpsPort; // SSL, that is sure
extern const char* fingerprint;

// I know this is bad practice, but using tabs makes  everything easier to read
extern const char* TAG_RESULT;
extern const char* TAG_ARRIVALS;
extern const char* TAG_WAITING_TIME;
extern const char* TAG_ARRIVED;
extern const int   FIRST_ARRIVAL;


extern String waitTimeURL;

extern const int TEN_SECONDS;
extern const int ONE_SECOND;
extern const int HALF_A_MINUTE;

#endif

