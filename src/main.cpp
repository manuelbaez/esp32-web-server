#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "WiFiConfig.h"
#include "Routes.h"

#ifndef AP_SSID
#define AP_SSID "Switch"
#define AP_PSK "123456789"
#endif

ESP8266WebServer webserver(80);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  // WiFi.mode(WIFI_AP);
  // WiFi.softAP(AP_SSID, AP_PSK);
  // WiFi.begin("CasaLB", "@1001@1997@");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   digitalWrite(LED_BUILTIN, 0);
  //   delay(10);
  //   Serial.print(".");
  //   digitalWrite(LED_BUILTIN, 1);
  // }
  // digitalWrite(LED_BUILTIN, 0);
  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
  addWebAppRoutes(&webserver);
  addApiRoutes(&webserver);
  webserver.begin();
}

void loop()
{
  webserver.handleClient();
}