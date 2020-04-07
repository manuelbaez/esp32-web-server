#include "WString.h"

class WiFiCredentials
{
public:
    String ssid;
    String password;
    WiFiCredentials();
    WiFiCredentials(String _ssid, String _password);
};

class WiFiConnectionStatus
{
public:
    bool connected;
    String ip;
    String ssid;
    WiFiConnectionStatus(bool connected);
    WiFiConnectionStatus(bool connected, String ip, String ssid);
};

class WiFiSetup
{

public:
    WiFiCredentials *networkCredentials;
    static WiFiSetup *wifiClient;
    WiFiSetup();
    void setCredentials(String ssid, String password);
    WiFiConnectionStatus *connect(bool startup=false);
};
