/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <Fluotube.h>

const char* ssid     = "your-ssid";
const char* password = "your-password";

const char* host = "data.sparkfun.com";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup()
{
    FluoTube.setup();

    FluoTube.debug("Connecting to ");
    FluoTube.debugln( String(ssid) );

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        FluoTube.debug(".");
    }

    FluoTube.debugln("");
    FluoTube.debugln("WiFi connected");
    FluoTube.debugln("IP address: ");
    FluoTube.debugln( WiFi.localIP().toString() );
}

int value = 0;

void loop()
{
    delay(5000);
    ++value;

    FluoTube.debug("connecting to ");
    FluoTube.debugln( String(host) );

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        FluoTube.debugln("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = "/input/";
    url += streamId;
    url += "?private_key=";
    url += privateKey;
    url += "&value=";
    url += value;

    FluoTube.debug("Requesting URL: ");
    FluoTube.debugln( String(url) );

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            FluoTube.debugln("Client Timeout ");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        FluoTube.debug( String(line) );
    }

    FluoTube.debugln("");
    FluoTube.debugln("closing connection");
}

