#include "WString.h"
#include "WifiSetup.h"

class GlobalConfig
{
public:
    static bool wiFiReady;
    static WiFiCredentials *wiFiCredentials;
    static void save();
    static void load();
};