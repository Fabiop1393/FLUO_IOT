/*
 *  This sketch shows the WiFi event usage
 *
 */

#include <WiFi.h>
#include <Fluotube.h>

const char* ssid     = "your-ssid";
const char* password = "your-password";


void WiFiEvents(WiFiEvent_t event)
{
    FluoTube.debugln("[WiFi-event] event: " + String(event) );

    switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
        FluoTube.debugln("WiFi connected");
        FluoTube.debugln("IP address: ");
        FluoTube.debugln(  WiFi.localIP().toString() );
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        FluoTube.debugln("WiFi lost connection");
        break;
    }
}

void setup()
{
    FluoTube.setup();

    // delete old config
    WiFi.disconnect(true);

    delay(1000);

    WiFi.onEvent(WiFiEvents);
    WiFi.begin(ssid, password);

    FluoTube.debugln("Wait for WiFi");
}

void loop()  {}

