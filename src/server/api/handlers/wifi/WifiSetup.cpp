#include "WifiSetup.h"
#include <ESP8266WiFi.h>

WifiCredentials::WifiCredentials(String _ssid, String _password)
{
    ssid = _ssid;
    password = _password;
}

void WifiSetup::setCredentials(WifiCredentials *credentials)
{
    networkCredentials = credentials;
}

WifiConnectionStatus* WifiSetup::connect()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(networkCredentials->ssid, networkCredentials->password);
    for (uint i = 0; i < 20; i++)
    {
        delay(500);
        digitalWrite(LED_BUILTIN, 0);
        delay(10);
        digitalWrite(LED_BUILTIN, 1);
        if (WiFi.status() == WL_CONNECTED)
        {
            auto ip = WiFi.localIP().toString();
            auto ssid = WiFi.SSID();
            auto connectionStatus=new WifiConnectionStatus(true, ip, ssid);
            Serial.println(ip);
            Serial.println(connectionStatus->ip);
            return connectionStatus;
        }
    }
    WiFi.mode(WIFI_AP);
    return new WifiConnectionStatus(false);
}