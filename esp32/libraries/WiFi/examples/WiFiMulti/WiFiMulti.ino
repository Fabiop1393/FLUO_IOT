/*
 *  This sketch trys to Connect to the best AP based on a given list
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <Fluotube.h>

WiFiMulti wifiMulti;

void setup()
{
    FluoTube.setup();

    wifiMulti.addAP("ssid_from_AP_1", "your_password_for_AP_1");
    wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
    wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

    FluoTube.debugln("Connecting Wifi...");
    if(wifiMulti.run() == WL_CONNECTED) {
        FluoTube.debugln("");
        FluoTube.debugln("WiFi connected");
        FluoTube.debugln("IP address: ");
        FluoTube.debugln( WiFi.localIP().toString() );
    }
}

void loop()
{
    if(wifiMulti.run() != WL_CONNECTED) {
        FluoTube.debugln("WiFi not connected");
        delay(1000);
    }
}