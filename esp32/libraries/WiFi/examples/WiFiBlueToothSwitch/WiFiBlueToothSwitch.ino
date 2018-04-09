// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Sketch shows how to switch between WiFi and BlueTooth or use both
// Button is BUTTON_APRST (AP-RST) on Fluo Board and modes are switched with each press

#include "WiFi.h"
#include <Fluotube.h>

#define STA_SSID "your-ssid"
#define STA_PASS "your-pass"
#define AP_SSID  "esp32"

enum { STEP_BTON, STEP_BTOFF, STEP_STA, STEP_AP, STEP_AP_STA, STEP_OFF, STEP_BT_STA, STEP_END };

void onButton(){
  static uint32_t step = STEP_BTON;
  switch(step){
    case STEP_BTON://BT Only
      FluoTube.debugln("** Starting BT");
      btStart();
    break;
    case STEP_BTOFF://All Off
      FluoTube.debugln("** Stopping BT");
      btStop();
    break;
    case STEP_STA://STA Only
      FluoTube.debugln("** Starting STA");
      WiFi.begin(STA_SSID, STA_PASS);
    break;
    case STEP_AP://AP Only
      FluoTube.debugln("** Stopping STA");
      WiFi.mode(WIFI_AP);
      FluoTube.debugln("** Starting AP");
      WiFi.softAP(AP_SSID);
    break;
    case STEP_AP_STA://AP+STA
      FluoTube.debugln("** Starting STA");
      WiFi.begin(STA_SSID, STA_PASS);
    break;
    case STEP_OFF://All Off
      FluoTube.debugln("** Stopping WiFi");
      WiFi.mode(WIFI_OFF);
    break;
    case STEP_BT_STA://BT+STA
      FluoTube.debugln("** Starting STA+BT");
      WiFi.begin(STA_SSID, STA_PASS);
      btStart();
    break;
    case STEP_END://All Off
      FluoTube.debugln("** Stopping WiFi+BT");
      WiFi.mode(WIFI_OFF);
      btStop();
    break;
    default:
    break;
  }
  if(step == STEP_END){
    step = STEP_BTON;
  } else {
    step++;
  }
  //little debounce
  delay(100);
}

void WiFiEvents(WiFiEvent_t event){
    switch(event) {
        case SYSTEM_EVENT_AP_START:
            FluoTube.debugln("AP Started");
            WiFi.softAPsetHostname(AP_SSID);
            break;
        case SYSTEM_EVENT_AP_STOP:
            FluoTube.debugln("AP Stopped");
            break;
        case SYSTEM_EVENT_STA_START:
            FluoTube.debugln("STA Started");
            WiFi.setHostname(AP_SSID);
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            FluoTube.debugln("STA Connected");
            WiFi.enableIpV6();
            break;
        case SYSTEM_EVENT_AP_STA_GOT_IP6:
            FluoTube.debug("STA IPv6: ");
            FluoTube.debugln( WiFi.localIPv6().toString() );
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            FluoTube.debug("STA IPv4: ");
            FluoTube.debugln( WiFi.localIP().toString() );
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            FluoTube.debugln("STA Disconnected");
            break;
        case SYSTEM_EVENT_STA_STOP:
            FluoTube.debugln("STA Stopped");
            break;
        default:
            break;
    }
}

void setup() {
    FluoTube.setup();

    pinMode(BUTTON_APRST, INPUT_PULLUP);

    WiFi.onEvent(WiFiEvents);
    FluoTube.debug("ESP32 SDK: ");
    FluoTube.debugln( String(ESP.getSdkVersion()) );
    FluoTube.debugln("Press the button to select the next mode");
}

void loop() {
    static uint8_t lastPinState = 1;
    uint8_t pinState = digitalRead(BUTTON_APRST);
    if(!pinState && lastPinState){
        onButton();
    }
    lastPinState = pinState;
}
