/*
Example Code To Get ESP32 To Connect To A Router Using WPS
===========================================================
This example code provides both Push Button method and Pin
based WPS entry to get your ESP connected to your WiFi router.

Hardware Requirements
========================
ESP32 and a Router having atleast one WPS functionality

This code is under Public Domain License.

Author:
Pranav Cherukupalli <cherukupallip@gmail.com>
*/

#include "WiFi.h"
#include "esp_wps.h"
#include <Fluotube.h>

/*
Change the definition of the WPS mode
from WPS_TYPE_PBC to WPS_TYPE_PIN in
the case that you are using pin type
WPS
*/
#define ESP_WPS_MODE WPS_TYPE_PBC

esp_wps_config_t config = WPS_CONFIG_INIT_DEFAULT(ESP_WPS_MODE);

String wpspin2string(uint8_t a[]){
  char wps_pin[9];
  for(int i=0;i<8;i++){
    wps_pin[i] = a[i];
  }
  wps_pin[8] = '\0';
  return (String)wps_pin;
}

void WiFiEvents(WiFiEvent_t event, system_event_info_t info){
  switch(event){
    case SYSTEM_EVENT_STA_START:
    FluoTube.debugln("Station Mode Started");
    break;
    case SYSTEM_EVENT_STA_GOT_IP:
    FluoTube.debugln("Connected to :" + String(WiFi.SSID()));
    FluoTube.debug("Got IP: ");
    FluoTube.debugln( WiFi.localIP().toString() );
    break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
    FluoTube.debugln("Disconnected from station, attempting reconnection");
    WiFi.reconnect();
    break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
    FluoTube.debugln("WPS Successfull, stopping WPS and connecting to: " + String(WiFi.SSID()));
    esp_wifi_wps_disable();
    delay(10);
    WiFi.begin();
    break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
    FluoTube.debugln("WPS Failed, retrying");
    esp_wifi_wps_disable();
    esp_wifi_wps_enable(&config);
    esp_wifi_wps_start(0);
    break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
    FluoTube.debugln("WPS Timedout, retrying");
    esp_wifi_wps_disable();
    esp_wifi_wps_enable(&config);
    esp_wifi_wps_start(0);
    break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
    FluoTube.debugln("WPS_PIN = " + wpspin2string(info.sta_er_pin.pin_code));
    break;
    default:
    break;
  }
}

void setup(){

  FluoTube.setup();

  WiFi.onEvent(WiFiEvents);
  WiFi.mode(WIFI_MODE_STA);

  FluoTube.debugln("Starting WPS");

  esp_wifi_wps_enable(&config);
  esp_wifi_wps_start(0);
}

void loop(){
  //nothing to do here
}
