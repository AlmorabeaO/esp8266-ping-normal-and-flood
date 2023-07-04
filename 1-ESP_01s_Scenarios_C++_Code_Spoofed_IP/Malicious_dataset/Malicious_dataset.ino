
//#include <Pinger.h>
//Pinger pinger;
//#define __ORIGINAL_PINGER__ // this for if the Original pinger header is not define please comment

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <cstdlib>
#include "netif/etharp.h"
#include "lwip/netif.h"
#include "pinger.h"


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


}



int timer{0};
void loop() {
    sendSignal(3);
    delay(2000);
    timer = sys_now()+(rand()%500'000+1000);
    while(timer>sys_now()){
    PingAttack(IPAddress(192,168,2,116));
    yield();
    }
    delay(1000);
    sendSignal(4);

}
