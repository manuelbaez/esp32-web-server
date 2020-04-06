#include "WifiSetup.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "../../lib/aruino-json/ArduinoJson.h"

#ifndef AP_SSID
#define AP_SSID "SmartSwitch"
#define AP_PSK "123456789"
#endif

WifiSetup ::WifiSetup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PSK);
    loadCredentialsFromEEPROM();
}

void WifiSetup::setCredentials(WifiCredentials *credentials)
{
    networkCredentials = credentials;
}

WifiConnectionStatus *WifiSetup::connect()
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
            auto connectionStatus = new WifiConnectionStatus(true, ip, ssid);
            Serial.println(connectionStatus->ip);
            saveCredentialsToEEPROM();
            return connectionStatus;
        }
    }
    WiFi.mode(WIFI_AP);
    return new WifiConnectionStatus(false);
}

const int wifiDataAddr = 1;

void WifiSetup::saveCredentialsToEEPROM()
{
    EEPROM.begin(1024);
    String ssid = networkCredentials->ssid;
    auto password = networkCredentials->password;
    DynamicJsonDocument dataJsonDocument(1024);
    dataJsonDocument["ssid"] = networkCredentials->ssid;
    dataJsonDocument["password"]= networkCredentials->password;
    char data[256] = {};
    serializeJson(dataJsonDocument, data);
    Serial.println(data);
    EEPROM.put(wifiDataAddr, data);
    EEPROM.commit();
};

void WifiSetup::loadCredentialsFromEEPROM()
{
    Serial.println("");
    Serial.println("Loading Credentials");
    EEPROM.begin(1024);
    char _ssid[256];
    EEPROM.get(wifiDataAddr, _ssid);
    Serial.println("");
    Serial.println(_ssid);
};

static void ClearEEPROM(){
 for (unsigned int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
};