/*
     Example of connection using Static IP
     by Evandro Luis Copercini
     Public domain - 2017
*/

#include <WiFi.h>
#include <Fluotube.h>

const char* ssid     = "your_network_name";
const char* password = "your_network_password";
const char* host     = "example.com";
const char* url      = "/index.html";

IPAddress local_IP(192, 168, 31, 115);
IPAddress gateway(192, 168, 31, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup()
{

  FluoTube.setup();

  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    FluoTube.debugln("STA Failed to configure");
  }

  FluoTube.debug("Connecting to ");
  FluoTube.debugln( String(ssid) );

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    FluoTube.debug(".");
  }

  FluoTube.debugln("");
  FluoTube.debugln("WiFi connected");

  FluoTube.debug("IP address: ");
  FluoTube.debugln( WiFi.localIP().toString() );

  FluoTube.debug("ESP Mac Address: "); 
  FluoTube.debugln( String(WiFi.macAddress()) );

  FluoTube.debug("Subnet Mask: ");
  FluoTube.debugln( String(WiFi.subnetMask()) );

  FluoTube.debug("Gateway IP: ");
  FluoTube.debugln( String(WiFi.gatewayIP()) );

  FluoTube.debug("DNS: ");
  FluoTube.debugln( String(WiFi.dnsIP()) );
}

void loop()
{
  delay(5000);

  FluoTube.debug("connecting to ");
  FluoTube.debugln( String(host) );

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    FluoTube.debugln("connection failed");
    return;
  }

  FluoTube.debug("Requesting URL: ");
  FluoTube.debugln( String(url) );

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      FluoTube.debugln("Client Timeout");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    FluoTube.debug( String(line) );
  }

  FluoTube.debugln("");
  FluoTube.debugln("closing connection");
}

