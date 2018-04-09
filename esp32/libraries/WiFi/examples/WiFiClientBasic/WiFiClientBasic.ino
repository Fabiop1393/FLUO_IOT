/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <Fluotube.h>

WiFiMulti WiFiMulti;

void setup()
{
    FluoTube.setup();    

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("SSID", "passpasspass");

    FluoTube.debugln();
    FluoTube.debugln();
    FluoTube.debug("Wait for WiFi");

    while(WiFiMulti.run() != WL_CONNECTED) {
        FluoTube.debug(".");
        delay(500);
    }

    FluoTube.debugln("");
    FluoTube.debugln("WiFi connected");
    FluoTube.debugln("IP address: ");
    FluoTube.debugln( WiFi.localIP().toString() );

    delay(500);
}


void loop()
{
    const uint16_t port = 80;
    const char * host = "192.168.1.1"; // ip or dns

    FluoTube.debug("connecting to ");
    FluoTube.debugln( String(host) );

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, port)) {
        FluoTube.debugln("connection failed");
        FluoTube.debugln("wait 5 sec");
        delay(5000);
        return;
    }

    // This will send the request to the server
    client.print("Send this data to server");

    //read back one line from server
    String line = client.readStringUntil('\r');
    client.println(line);

    FluoTube.debugln("closing connection");
    client.stop();

    FluoTube.debugln("wait 5 sec");
    delay(5000);
}

