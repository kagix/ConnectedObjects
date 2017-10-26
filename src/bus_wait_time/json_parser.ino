#include <ArduinoJson.h>
#include "json_parser.h"

// Ugly function that does the parse and displays the waiting time 
void parseJson(String aJson){
  
  DynamicJsonBuffer jsonBuffer(1024);
  JsonObject& theJson = jsonBuffer.parseObject(aJson);

  // In other words, retrieve the waiting time for the first bus.
  const char* resultString = theJson[TAG_RESULT][TAG_ARRIVALS][FIRST_ARRIVAL][TAG_WAITING_TIME];
  
  if (!resultString){
#ifdef ACTIVATE_SERIAL_MONITOR              
    Serial.println("No results");
#endif    
    return;
  }
  
#ifdef ACTIVATE_SERIAL_MONITOR              
  Serial.println("The web server returned some data to be parsed:");
  Serial.println(resultString);
#endif

  String aValue = resultString;
  int minutesToWait=-1;
  int pos = aValue.indexOf(" mn");
  char figureInFirstPlace;  // can be units or tens
  char figureInSecondPlace; // always units

  // We know the text is at least 4 characters long
  if ( aValue.equals(TAG_ARRIVED)){
    minutesToWait = 0;
  }
  else if (pos > 0){
    figureInFirstPlace = resultString[0];
    figureInSecondPlace = resultString[1];

    // The old art of converting a character into a number
    if (pos == 1) {// 1 figure
      minutesToWait=(int)figureInFirstPlace-(int)'0';
    } else if (pos == 2) { // figure
      minutesToWait=((int)figureInFirstPlace-(int)'0')*10+(int)figureInSecondPlace-(int)'0';
    } else {
      // Nothing
    }
  }
  else {
    Serial.println("Valid mins < 0");
  }

#ifdef ACTIVATE_SERIAL_MONITOR              
  char waitingTimeAsText[20];
  sprintf(waitingTimeAsText, "Wait:%d", minutesToWait);
  Serial.println(waitingTimeAsText);
#endif  

  if (minutesToWait >= 0){
    draw_number(minutesToWait);
  } 
  else {
    draw_number(-2); // for the moment shows a blank matrix.
  }
}
