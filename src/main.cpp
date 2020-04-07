#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "Routes.h"
#include "GlobalConfig.h"

ESP8266WebServer webserver(80);



void setup()
{
  WiFiSetup *wifiClient= WiFiSetup::wifiClient;
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  addWebAppRoutes(&webserver);
  addApiRoutes(&webserver);
  webserver.begin();
  GlobalConfig::load();
  if(GlobalConfig::wiFiReady){
     wifiClient->connect(true);
  }
}

void loop()
{
  webserver.handleClient();
}