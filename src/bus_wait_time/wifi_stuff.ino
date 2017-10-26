#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "wifi_stuff.h"

int                 status;

void initWiFi(){
  displayWiFi();

  status = WiFi.begin(ssid, pass);
  status = WiFi.waitForConnectResult();
  if (status != WL_CONNECTED) {
 #ifdef ACTIVATE_SERIAL_MONITOR              
      Serial.println("Connection Failed");
 #endif
      while (true) {
#ifdef ACTIVATE_SERIAL_MONITOR          
          Serial.println("Connection failed. Please stop it.");
#endif          
          displayErr();
          delay(TEN_SECONDS);

      }
   }

#ifdef ACTIVATE_SERIAL_MONITOR          
  Serial.println("Connected.");
  Serial.print("MAC Addr: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP Addr:  ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet:   ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway:  ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS Addr: ");
  Serial.println(WiFi.dnsIP());
  Serial.print("Channel:  ");
  Serial.println(WiFi.channel());
  Serial.print("Status: ");
  Serial.println(WiFi.status());
#endif
}




void fetchNextBus() {
  for (int tick2=1; tick2 <=6; tick2++){
       displayProgress(tick2);
       updateDisplay();
       delay(ONE_SECOND);
    }

  WiFiClientSecure client;
  
#ifdef ACTIVATE_SERIAL_MONITOR            
  Serial.print("connecting to ");
  Serial.println(host);
#endif  
  if (!client.connect(host, httpsPort)) {
#ifdef ACTIVATE_SERIAL_MONITOR              
    Serial.println("connection failed");
#endif    
    // After all, it is easier to see the message on the display
    displayErr();
    delay(HALF_A_MINUTE);
    return;
  }

  if (client.verify(fingerprint, host)) {
#ifdef ACTIVATE_SERIAL_MONITOR              
    Serial.println("certificate matches");
#endif
  } else {
#ifdef ACTIVATE_SERIAL_MONITOR              
    Serial.println("certificate doesn't match");
#endif
    displayErr();
    delay(HALF_A_MINUTE);  
  }

#ifdef ACTIVATE_SERIAL_MONITOR              
  Serial.print("requesting URL: ");
  Serial.println(waitTimeURL);
#endif

  client.print(String("GET ") + waitTimeURL + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: Test JSON Decoding\r\n" +
               "Connection: close\r\n\r\n");

#ifdef ACTIVATE_SERIAL_MONITOR              
  Serial.println("request sent");
#endif
  
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
#ifdef ACTIVATE_SERIAL_MONITOR              
      Serial.println("headers received");
#endif
      break;
    }
  }
  String skipLine = client.readStringUntil('\n'); // 1ca - who needs it ?
  String line = client.readString();

#ifdef ACTIVATE_SERIAL_MONITOR                
  Serial.println("reply was:");
  Serial.println("======================================================================");
  Serial.println(line);
  Serial.println("======================================================================");
  Serial.println("closing connection");
#endif
  
  parseJson(line);
  
  for (int tick=1; tick <=6; tick++){
     displayProgress(tick);
     updateDisplay();
     delay(TEN_SECONDS);
  }
}
