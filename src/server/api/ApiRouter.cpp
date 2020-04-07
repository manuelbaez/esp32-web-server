#include "Arduino.h"
#include "Routes.h"
#include "../../lib/aruino-json/ArduinoJson.h"
#include "GlobalConfig.h"

auto wifi =  WiFiSetup::wifiClient;

void addApiRoutes(ESP8266WebServer *server)
{
    server->on("/switch/turnOff", [server]() {
        digitalWrite(LED_BUILTIN, 1);
        server->send(200);
    });

    server->on("/switch/turnOn", [server]() {
        digitalWrite(LED_BUILTIN, 0);
        server->send(200);
    });
    server->on("/wifiSetup", [server]() {
        auto requestJson = server->arg("plain");
        DynamicJsonDocument requestDocument(1024);
        deserializeJson(requestDocument, requestJson);
        String ssid = requestDocument["ssid"];
        String password = requestDocument["password"];
        wifi->setCredentials(ssid, password);
        auto connectionStatus = wifi->connect();

        DynamicJsonDocument responseDocument(1024);
        responseDocument["connected"] = connectionStatus->connected;
        responseDocument["ssid"] = connectionStatus->ssid;
        responseDocument["ip"] = connectionStatus->ip;
        String serializedJson;
        serializeJson(responseDocument, serializedJson);
        if (connectionStatus->connected)
        {
            GlobalConfig::save();
            server->send(200, "application/json", serializedJson);
        }
        else
        {
            server->send(500, "application/json", serializedJson);
        }
    });
}