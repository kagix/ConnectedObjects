/*
The JSON has the following format
{
  "result": {
    "arrivals": [
      {
        "waiting_time": "30 mn",
        .. other attributes ..
      },
      .. next entry in the array ..
      ]
    },
    .. other data ..
} 
 */

#include "constants.h"
#include "led_matrix.h"
#include "wifi_stuff.h"


// Uncomment next line if you want to monitor the device
// #define ACTIVATE_SERIAL_MONITOR (1)





void setup() {
#ifdef ACTIVATE_SERIAL_MONITOR            
  Serial.begin(9600);
#endif  
  initDisplay();
  initWiFi();


}

// Maybe we should split this function in chunks
void loop() {
  fetchNextBus();
}




