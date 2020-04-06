#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "Routes.h"
#include "WifiSetup.h"

ESP8266WebServer webserver(80);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  addWebAppRoutes(&webserver);
  addApiRoutes(&webserver);
  webserver.begin();
  WifiSetup::loadCredentialsFromEEPROM();
}

void loop()
{
  webserver.handleClient();
}