/*
  ESP8266 mDNS-SD responder and query sample

  This is an example of announcing and finding services.
  
  Instructions:
  - Update WiFi SSID and password as necessary.
  - Flash the sketch to two ESP8266 boards
  - The last one powered on should now find the other.
 */

#include <WiFi.h>
#include <ESPmDNS.h>
#include <Fluotube.h>

const char* ssid     = "...";
const char* password = "...";

void setup() {

    FluoTube.setup();

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        FluoTube.debug(".");
    }
    FluoTube.debugln("");
    FluoTube.debug("Connected to ");
    FluoTube.debugln( String(ssid) );
    FluoTube.debug("IP address: ");
    delay(1000);
    FluoTube.debugln( WiFi.localIP().toString() );

    if (!MDNS.begin("ESP32_Browser")) {
        FluoTube.debugln("Error setting up MDNS responder");
        while(1){
            delay(1000);
        }
    }
}

void loop() {
    browseService("http", "tcp");
    delay(1000);
    browseService("arduino", "tcp");
    delay(1000);
    browseService("workstation", "tcp");
    delay(1000);
    browseService("smb", "tcp");
    delay(1000);
    browseService("afpovertcp", "tcp");
    delay(1000);
    browseService("ftp", "tcp");
    delay(1000);
    browseService("ipp", "tcp");
    delay(1000);
    browseService("printer", "tcp");
    delay(10000);
}

void browseService(const char * service, const char * proto){

    FluoTube.debugln("Browsing for service _" + String(service) + "._" + String(proto) + ".local ");

    int n = MDNS.queryService(service, proto);
    if (n == 0) {
        FluoTube.debugln("no services found");
    } else {
        FluoTube.debug(String(n));
        FluoTube.debugln(" service(s) found");
        for (int i = 0; i < n; ++i) {
            // Print details for each service found
            FluoTube.debug("  ");
            FluoTube.debug( String(i + 1) );
            FluoTube.debug(": ");
            FluoTube.debug( String(MDNS.hostname(i)) );
            FluoTube.debug(" (");
            FluoTube.debug( String(MDNS.IP(i)) );
            FluoTube.debug(":");
            FluoTube.debug( String(MDNS.port(i)) );
            FluoTube.debugln(")");
        }
    }
    FluoTube.debugln("");
}
