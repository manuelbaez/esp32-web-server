#include "GlobalConfig.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "../../lib/aruino-json/ArduinoJson.h"

#ifndef AP_SSID
#define AP_SSID "SmartSwitch"
#define AP_PSK "123456789"
#endif

WiFiSetup *WiFiSetup::wifiClient = new WiFiSetup();

WiFiSetup ::WiFiSetup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PSK);
    networkCredentials = new WiFiCredentials();
}

void WiFiSetup::setCredentials(String ssid, String password)
{
    networkCredentials->ssid = ssid;
    networkCredentials->password = password;
}

WiFiConnectionStatus *WiFiSetup::connect(bool startup)
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(networkCredentials->ssid, networkCredentials->password);
    int maxLookoutCycles = (startup) ? INT_MAX : 20;
    for (uint i = 0; i < maxLookoutCycles; i++)
    {
        delay(500);
        digitalWrite(LED_BUILTIN, 0);
        delay(10);
        digitalWrite(LED_BUILTIN, 1);
        if (WiFi.status() == WL_CONNECTED)
        {
            auto ip = WiFi.localIP().toString();
            auto ssid = WiFi.SSID();
            auto connectionStatus = new WiFiConnectionStatus(true, ip, ssid);
            Serial.println(connectionStatus->ip);
            GlobalConfig::wiFiReady = true;
            return connectionStatus;
        }
    }
    WiFi.mode(WIFI_AP);
    return new WiFiConnectionStatus(false);
}
