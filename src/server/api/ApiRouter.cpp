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
        const size_t bufferSize = JSON_OBJECT_SIZE(2);
        DynamicJsonBuffer jsonBuffer(bufferSize);
        auto data = jsonBuffer.parse(server->arg("plain"));
        String ssid = data["ssid"].as<String>();
        String password = data["password"].as<String>();
        Serial.println();
        auto credentials = new WifiCredentials(ssid, password);
        wifi.setCredentials(credentials);
        auto connectionStatus = wifi.connect();
        if (connectionStatus.connected)
        {
            const size_t responseBufferSize = JSON_OBJECT_SIZE(3);
            DynamicJsonBuffer responseJsonBuffer(responseBufferSize);
            auto json = responseJsonBuffer.createObject();
            json["connected"]=connectionStatus.connected;
            json["ssid"]=connectionStatus.ssid;
            json["ip"]=connectionStatus.ip;
            server->send(200, "application/json", json.)
        };
    });
}