
//#include <Pinger.h>
//Pinger pinger;
//#define __ORIGINAL_PINGER__ // this for if the Original pinger header is not define please comment
#include "pinger.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String serverName = "http://192.168.2.116:5000/";
WiFiClient client;
HTTPClient http;


void sendSignal (int num){
  String serverPath = serverName + "?status="+num ;
  http.begin(client, serverPath.c_str());
  if(http.GET() !=200){
    delay(2000);
    sendSignal(num);
  }
 http.end();
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


  //-------------------------------------------------------

  Serial.print("Start Sending the genuine data********");

  for (int i=1; i<=500; i++){
    Serial.print(i);
    Serial.print("\n");
    sendSignal(1);
    delay(3000);
    
    for (int j=1; j<=i;j++){
      PingAttack(IPAddress(192,168,2,116),0xDEAD);
      delay(1000);
      yield();
    }
    sendSignal(2);
    yield();
  }

  
  Serial.print("Finished Sending the genuine data");

}

void loop() {


}
