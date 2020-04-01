#include "Arduino.h"
#include "Routes.h"
#include "../../lib/aruino-json/ArduinoJson.h"
#include "WifiSetup.h"

WifiSetup wifi;

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
        auto credentials = new WifiCredentials(ssid, password);
        wifi.setCredentials(credentials);
        auto connectionStatus = wifi.connect();

        DynamicJsonDocument responseDocument(1024);
        responseDocument["connected"] = connectionStatus->connected;
        responseDocument["ssid"] = connectionStatus->ssid;
        responseDocument["ip"] = connectionStatus->ip;
        String serializedJson;
        serializeJson(responseDocument, serializedJson);
        if (connectionStatus->connected)
        {
            server->send(200, "application/json", serializedJson);
        }
        else
        {
            server->send(500, "application/json", serializedJson);
        }
    });
}