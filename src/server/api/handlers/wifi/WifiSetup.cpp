#include "WifiSetup.h"
#include <ESP8266WiFi.h>

WifiCredentials::WifiCredentials(String _ssid, String _password)
{
    ssid = _ssid;
    password = _password;
}

void WifiSetup::setCredentials(WifiCredentials* credentials)
{
    networkCredentials = credentials;
}

WifiConnectionStatus WifiSetup::connect()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(networkCredentials->ssid, networkCredentials->password);
    for (uint i = 0; i < 5; i++)
    {
        delay(500);
        digitalWrite(LED_BUILTIN, 0);
        delay(10);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, 1);
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("");
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            auto ip=WiFi.localIP().toString();
            return new WifiConnectionStatus(true,ip,WiFi.SSID());
        }
    }
    return new WifiConnectionStatus(false);
}