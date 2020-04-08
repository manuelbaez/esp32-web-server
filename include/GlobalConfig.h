#include "WString.h"
#include "WifiSetup.h"

class GlobalConfig
{
private:
    static WiFiCredentials *wiFiCredentials;

public:
    static bool wiFiReady;
    static void save();
    static void load();
};