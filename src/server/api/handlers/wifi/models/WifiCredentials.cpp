#include "WifiSetup.h"

WiFiCredentials::WiFiCredentials(){};

WiFiCredentials::WiFiCredentials(String _ssid, String _password)
{
    ssid = _ssid;
    password = _password;
}
