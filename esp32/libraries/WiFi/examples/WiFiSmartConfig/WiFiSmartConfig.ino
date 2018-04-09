#include "WiFi.h"
#include <Fluotube.h>

void setup() {

  FluoTube.setup();

  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  FluoTube.debugln("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    FluoTube.debug(".");
  }

  FluoTube.debugln("");
  FluoTube.debugln("SmartConfig received.");

  //Wait for WiFi to connect to AP
  FluoTube.debugln("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    FluoTube.debug(".");
  }

  FluoTube.debugln("WiFi Connected.");

  FluoTube.debug("IP Address: ");
  FluoTube.debugln( WiFi.localIP().toString() );
}

void loop() {
  // put your main code here, to run repeatedly:

}
