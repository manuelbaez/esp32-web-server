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
    loadCredentialsFromEeprom();
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
            saveCredentialsToEeprom();
            return connectionStatus;
        }
    }
    WiFi.mode(WIFI_AP);
    return new WifiConnectionStatus(false);
}

struct 
{
    String json;
    String none;    
} eeprom_data;

const int wifiDataAddr = 1;

void WifiSetup::saveCredentialsToEeprom()
{
    EEPROM.begin(1024);
    auto ssid = networkCredentials->ssid;
    auto password = networkCredentials->password;
    DynamicJsonDocument dataJsonDocument(1024);
    // dataJsonDocument["ssid"]= networkCredentials->ssid;
    // serializeJson(dataJsonDocument, eeprom_data.json);
    Serial.println(eeprom_data.json); 
    eeprom_data.json="hola";
    EEPROM.put(wifiDataAddr,eeprom_data);
    EEPROM.commit();
};

void WifiSetup::loadCredentialsFromEeprom()
{
    Serial.println("");
    Serial.println("Loading Credentials");
    EEPROM.begin(1024);
    EEPROM.get(wifiDataAddr, eeprom_data);
    Serial.println("");
    Serial.println(eeprom_data.json);
};