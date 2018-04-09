#include <WiFi.h>
#include "time.h"
#include <Fluotube.h>

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR_PASS";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    FluoTube.debugln("Failed to obtain time");
    return;
  }
  strftime(buffer,80,"%A, %B %d %Y %H:%M:%S", &timeinfo);
  FluoTube.debugln( buffer );
}

void setup()
{
  FluoTube.setup();
  
  //connect to WiFi
  FluoTube.debugln("Connecting to " + String(ssid) );

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      FluoTube.debug(".");
  }
  FluoTube.debugln(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
