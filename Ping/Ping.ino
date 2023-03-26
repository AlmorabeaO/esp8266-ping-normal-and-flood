//#include <Pinger.h>
//Pinger pinger;
//#define __ORIGINAL_PINGER__ // this for if the Original pinger header is not define please comment
#include "pinger.h"
#include <ESP8266WiFi.h>
extern "C"
{
  #include <lwip/icmp.h> // needed for icmp packet definitions
}


void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi access point
  bool stationConnected = WiFi.begin(
  "ssid",
  "password");

  // Check if connection errors
  if(!stationConnected)
  {
    Serial.println("Error, unable to connect specified WiFi network.");
  }
  
  // Wait connection completed
  Serial.print("Connecting to AP...");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Ok\n");
}

void loop() {
  PingAttack(IPAddress(192,168,1,118));
}
