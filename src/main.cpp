#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "WiFiConfig.h"
#include "Routes.h"

#ifndef STASSID
#define STASSID "CasaLB"
#define STAPSK "@1001@1997@"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;


ESP8266WebServer webserver(80);


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Test", "12345678");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    digitalWrite(LED_BUILTIN, 0);
    delay(10);
    Serial.print(".");
    digitalWrite(LED_BUILTIN, 1);
  }
  digitalWrite(LED_BUILTIN, 0);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  addRoutes(&webserver);
  webserver.begin();
  // put your setup code here, to run once:
}

void loop()
{
  webserver.handleClient(); 
}