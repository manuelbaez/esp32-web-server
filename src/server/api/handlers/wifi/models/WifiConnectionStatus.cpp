#include "WifiSetup.h"

WiFiConnectionStatus::WiFiConnectionStatus(bool _connected){
    connected = _connected;
};

WiFiConnectionStatus::WiFiConnectionStatus(bool _connected, String _ip, String _ssid)
{
    connected = _connected;
    ip = _ip;
    ssid = _ssid;
};