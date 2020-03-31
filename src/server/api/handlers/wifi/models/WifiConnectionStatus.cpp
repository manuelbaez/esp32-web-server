#include "WifiSetup.h"

WifiConnectionStatus::WifiConnectionStatus(bool _connected){
    connected = _connected;
};

WifiConnectionStatus::WifiConnectionStatus(bool _connected, String _ip, String _ssid)
{
    connected = _connected;
    ip = _ip;
    ssid = _ssid;
};