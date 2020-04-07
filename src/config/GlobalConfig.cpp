#include "GlobalConfig.h"
#include <EEPROM.h>
#include "../../lib/aruino-json/ArduinoJson.h"

auto _wifi = WiFiSetup::wifiClient;

const int dataAddr = 1;

// static void ClearEEPROM(){
//  for (unsigned int i = 0; i < EEPROM.length(); i++)
//     {
//         EEPROM.write(i, 0);
//     }
// };
WiFiCredentials *GlobalConfig::wiFiCredentials = _wifi->networkCredentials;
bool GlobalConfig::wiFiReady = false;

void GlobalConfig::save()
{
    EEPROM.begin(1024);
    auto ssid = _wifi->networkCredentials->ssid;
    auto password = _wifi->networkCredentials->password;
    DynamicJsonDocument dataJsonDocument(1024);
    dataJsonDocument["ssid"] = _wifi->networkCredentials->ssid;
    dataJsonDocument["password"] = _wifi->networkCredentials->password;
    dataJsonDocument["wiFiReady"] = GlobalConfig::wiFiReady;
    char data[512] = {};
    serializeJson(dataJsonDocument, data);
    EEPROM.put(dataAddr, data);
    EEPROM.commit();
};

void GlobalConfig::load()
{
    EEPROM.begin(1024);
    char data[512];
    EEPROM.get(dataAddr, data);
    Serial.println("");
    Serial.println(data);
    DynamicJsonDocument dataJsonDocument(1024);
    deserializeJson(dataJsonDocument, data);
    _wifi->setCredentials(dataJsonDocument["ssid"], dataJsonDocument["password"]);
    GlobalConfig::wiFiReady = dataJsonDocument["wiFiReady"];
};