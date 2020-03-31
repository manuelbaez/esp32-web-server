#include "WString.h"

class WifiCredentials
{
public:
    String ssid;
    String password;
    WifiCredentials(String _ssid, String _password);
};

class WifiConnectionStatus
{
public:
    bool connected;
    String ip;
    String ssid;
    WifiConnectionStatus(bool connected);
    WifiConnectionStatus(bool connected, String ip, String ssid);
};

class WifiSetup
{

    WifiCredentials *networkCredentials;

public:
    void setCredentials(WifiCredentials *credentials);
    WifiConnectionStatus connect();

private:
    WifiCredentials loadCredentialsFromEeprom();
};
