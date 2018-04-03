#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESP32AVRISP.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

#include "Fluoweb.h"
#include "Fluohtml.h"
#include "Fluotools.h"
#include "FluoSD.h"
#include "EEPROM.h"
#include "644VirtualCom/protocol.h"

WebServer serverIoT(80);

WebServer serverMANUAL(8080);
WebSocketsServer webSocket(8888);
WiFiServer server(80);
WiFiCallbackClass WiFiCallback;


//CheckMode
enum{
  STA = 1,
  AP,
  APSTA
};
//CheckStatus
enum{
  WAIT,
  CONNECTED,
  CONNECTED_NOWAN,
  SSID_NOVALID,
  PASSKEY_NOVALID,
  FAILURE
};
//struct for args
struct Args
{
    char key;
    char *value;  
};
struct Args WifisaveArg[5];

struct settings_t{
  byte  IoTMode;
  char hostname[31];
  char ssid[31];
  char password[64];
};
struct settings_t settings = {0, "fluo", "ssid", "pass"};

struct socketWeb{ 
  WStype_t typeMess;
  String uri = "";
  int member = -1;  
}webSocketData;

// Function Prototype 
int getRSSIasQuality(int);
void PopulateArgsArrey(char *);
void AP_SettingMode();
void STA_SettingMode();
void MANUAL_SettingMode();
void ActivateManualMode();
void RESThandle();
void WiFiEvent(WiFiEvent_t);
int ComputeBar(int);

void WebSocketSetup();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void WEBSOCKEThandle();

void ReadSetting(struct settings_t *);
void storeStruct(void *, size_t);
void loadStruct(void *, size_t);

// Global Variable
//System
unsigned long prevMillisTaskWiFiCheck;
//Web
int RefreshPageMode = 1; //parte attivo

const char* APssid = "FLUO WI-FI (FirstConfig)"; //default on Start
int CheckStatus; // link to enum
int CheckMode;   // link to enum
int NETnumber; // 

int oneshot; 
int RetryCount;

int MMMode;

void WebSetup(void)
{  
	HardwareInit();

    // WiFi Setting - occhio !!!
    WiFi.setAutoConnect(false);
    WiFi.setAutoReconnect(false);

    Serial.println("ESP32 Application Start");
  
    delay(10);

    WiFi.onEvent(WiFiEvent); // start

    delay(2000);
    //handle Manual mode
    if (VirtualUseCase() == 1)
    {
        ActivateManualMode();
        return;
    }
    // read configuration from EEPROM and save it on RAM -> settings
    loadStruct(&settings, sizeof(settings));
    ReadSetting(&settings); //dbg

    struct settings_t *struct_pointer_tmp = &settings;

    if (struct_pointer_tmp->IoTMode == 1)
      WiFiCallback.STAmode();
    else
      WiFiCallback.APmode();
}

byte ManualMode;

void ActivateManualMode()
{

    //WiFi.mode(WIFI_MODE_STA);
    //Serial.println("[ManualMODE] STA mode and try to connect");

    String hostname = VirtualHOSTNAME(); // hostname
    delay(100);
    String passkey = VirtualPASSKEY(); // passkey
    delay(100);
    String ssid = VirtualSSID(); // ssid
    delay(100);

    Serial.println("[ActivateManualMode] Hostname: "+hostname); 
    Serial.println("[ActivateManualMode] Passkey: "+passkey); 
    Serial.println("[ActivateManualMode] SSID: "+ssid);

    WiFi.mode(WIFI_MODE_STA);
    delay(1000);

    //Try to connect
    WiFi.begin(ssid.c_str(), passkey.c_str());
    ManualMode = 1;

    int i = 0;
    // max 10 tentativi (5 sec)
    while ( (WiFi.status() != WL_CONNECTED) && (i <= 15) ) 
    {
        delay(500);
        //Serial.print(i); DBG
        i++;
    }

    VirtualConnection(WiFi.localIP().toString());

    if (i >= 15) // non provare a configurare MDNS
        return;

    if (!MDNS.begin(hostname.c_str())) 
        Serial.println("[ManualMODE] Error setting up MDNS responder!");

    Serial.println("[ManualMODE] mDNS responder started");

    //Add service to MDNS-WEB
    MDNS.addService("http", "tcp", 80);

    delay(500); 
    //inizializzo il WebSocket
    WebSocketSetup();
}

void WebLoop(void)
{
    webSocket.loop();
    struct settings_t *struct_pointer_tmp = &settings;

    if (MMMode == 2)
    {
        ActivateManualMode();
        Scheduler(); //force
        return;
    }

    if (ManualMode == 1 && MMMode == 1)
    {
        MANUAL_SettingMode();
        Scheduler(); //force
        return;
    }

    // IoT Panel

    if (CheckInterrupt() == 1)
    {
    	WiFiCallback.APmode();

        delay(1000);
        ESP.restart();
    }
          
    if (struct_pointer_tmp->IoTMode == 1)
        STA_SettingMode();
    else
        AP_SettingMode();

    // if only free time ?
    Scheduler();
}

void WebSocketSetup(){
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("[WebSocket] inizializzato e pronto a ricevere");
}



//--------------------------------------------------------
// WiFiCallbackClass
void WiFiCallbackClass::APmode()
{         
   WiFi.disconnect(true); // delete old config
   
   WiFi.mode(WIFI_MODE_AP);
   Serial.println("[AP - WiFiCallback] AP mode");

   delay(100);

   // Start TCP (HTTP) Server WiFi Configurator
   server.begin();
   Serial.println("[AP - WiFiCallback] TCP server started");

   //al reboot la nuova modalita' e' quella AP config
   struct settings_t settings = {0, "fluo", "ssid", "pass"};
   storeStruct(&settings, sizeof(settings));
}

void WiFiCallbackClass::STAmode()
{
   //WiFi.disconnect(true); // delete old config
   struct settings_t *struct_pointer_tmp = &settings;

   WiFi.mode(WIFI_MODE_STA);
   Serial.println("[STA - WiFiCallback] STA mode");

   delay(10);

  //dbg
   Serial.print("[APSTA - WiFiCallback] SSID: ");
   Serial.println(struct_pointer_tmp->ssid);
   Serial.print("[APSTA - WiFiCallback] Passkey: ");
   Serial.println(struct_pointer_tmp->password);

   WiFi.begin(struct_pointer_tmp->ssid, struct_pointer_tmp->password);

   Serial.print("[STA - WiFiCallback] Hostname: ");
   Serial.println(struct_pointer_tmp->hostname);

   if (!MDNS.begin(struct_pointer_tmp->hostname)) 
   {
     Serial.println("[STA - WiFiCallback] Error setting up MDNS responder!");
   }
   Serial.println("[STA - WiFiCallback] mDNS responder started");

   //Add service to MDNS-WEB
   MDNS.addService("http", "tcp", 80);

   delay(100);

   Serial.println("[STA - WiFiCallback] TCP server started");

   //al reboot la nuova modalita' e' quella IoT
   settings.IoTMode = 1;
   storeStruct(&settings, sizeof(settings));
} 

void WiFiCallbackClass::APSTAmode()
{
   WiFi.mode(WIFI_MODE_APSTA);
   
   delay(100);

   struct settings_t *struct_pointer_tmp = &settings;

   //dbg
   Serial.print("[APSTA - WiFiCallback] SSID: ");
   Serial.println(struct_pointer_tmp->ssid);
   Serial.print("[APSTA - WiFiCallback] Passkey: ");
   Serial.println(struct_pointer_tmp->password);

   delay(100);

   WiFi.begin(struct_pointer_tmp->ssid, struct_pointer_tmp->password);


   Serial.println("[AP+STA - WiFiCallback] AP+STA mode");
   
}
void WiFiCallbackClass::SCANmode()
{
    // before scan you must change mode!
    if (WiFi.getMode() != APSTA)
    {
      WiFi.mode(WIFI_MODE_APSTA);
      WiFi.disconnect(); //potrebbe dare problemi
      delay(100);
    }
  
    NETnumber = WiFi.scanNetworks();
    Serial.println("[SCAN mode - WiFiCallback]");
}

//--------------------------------------------------------

// Check Internet connection
void CheckInternet()
{
  WiFiClient clientPing;
  
  // se il ping e' ok return 1
  if( clientPing.connect("www.google.com", 80) == 1 )
  {
    CheckStatus = CONNECTED;
    LinkStatus = LINK_WAN;
  }

  clientPing.stop();
}


//--------------------------------------------------------
// WiFiEvent_t event

void WiFiEvent(WiFiEvent_t event)
{
    switch(event) 
    {
      case SYSTEM_EVENT_AP_START:
      {
        Serial.println("[WiFiEvent] AP_START ");
        WiFi.softAP(APssid);

        LinkStatus = LINK_AP;
        
        break;
      }
      
      case SYSTEM_EVENT_AP_STOP:
      {
        Serial.println("[WiFiEvent] AP_STOP ");
        
        break;
      }

      case SYSTEM_EVENT_STA_START:
      {
        Serial.println("[WiFiEvent] STA_START ");
        CheckStatus = WAIT;
        
        break;
      }

      case SYSTEM_EVENT_STA_STOP:
      {
        Serial.println("[WiFiEvent] STA_STOP ");
        CheckStatus = FAILURE;
        
        break;
      }

      case SYSTEM_EVENT_AP_STADISCONNECTED:
      {
        Serial.println("[WiFiEvent] ESP_SoftAP disconnected ");
        break;
      }
      
      case SYSTEM_EVENT_AP_STACONNECTED:
      {
        Serial.println("[WiFiEvent] ESP_SoftAP connected with a Station ");
        break;
      }
      
      case SYSTEM_EVENT_STA_CONNECTED:
      {
        LinkStatus = LINK_STA;
        Serial.println("[WiFiEvent] ESP_STA connected with a HotSpot ");

        break;
      }

      case SYSTEM_EVENT_STA_GOT_IP:
      {
        Serial.println("[WiFiEvent] ESP_STA connected and GOT IP");
        Serial.print("[WiFiEvent] ESP_STA -> IP address: ");
        Serial.println(WiFi.localIP());

        CheckStatus = CONNECTED_NOWAN;

        CheckInternet();
        
        break;
      }
      
      case SYSTEM_EVENT_STA_DISCONNECTED:
      {
        // potresti aggiungere un retry della connessione wifi se lo perde

        Serial.println("[WiFiEventNew] ESP_STA HotSpot Signal lost ");

        WiFi.begin();
        WiFi.reconnect(); // Try reconnect

        CheckStatus = FAILURE;
        LinkStatus = LINK_NO;
        
        break;
      }


    }
}

//--------------------------------------------------------

void AP_SettingMode()
{
   
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
        return;
    }
    Serial.println("");
    Serial.println("New client");

    // Wait for data from client to become available
    while(client.connected() && !client.available()){
        delay(1);
    }

    // Read the first line of HTTP request
    String req = client.readStringUntil('\r');

    // First line of HTTP request looks like "GET /path HTTP/1.1"
    // Retrieve the "/path" part by finding the spaces
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    
    if (addr_start == -1 || addr_end == -1) {
        Serial.print("Invalid request: ");
        Serial.println(req);
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print("Request: ");
    Serial.println(req);
    client.flush();

    String req_one;
    String req_two;

    for (int i = 0; i < req.length(); i++)  // solo se c'e' il "?"
    {
      if (req.substring(i, i+1) == "?")
      {
        req_one = req.substring(0, i);
        req_two = req.substring(i);
         
        break;
      }
    }

    String page;
    
    if (req == "/")
    {
        page = FPSTR(HTTP_HEAD);
        page.replace("{v}", "Options");
        page.replace("{h}", "");
        page += FPSTR(HTTP_SCRIPT);
        page += FPSTR(HTTP_STYLE);
        page += FPSTR(HTTP_HEAD_END);
        page += F("<h3>FLUO WI-FI Configurator</h3>");
        page += FPSTR(HTTP_PORTAL_OPTIONS);
        page += FPSTR(HTTP_END);

        Serial.println("Sending 200 - End root");
    }
    
    else if(req == "/wifi")
    {   
        page = FPSTR(HTTP_HEAD);
        page.replace("{v}", "Choose WiFi Network");
        page.replace("{h}", "");
        page += FPSTR(HTTP_SCRIPT);
        page += FPSTR(HTTP_STYLE);
        page += FPSTR(HTTP_ENCR);
        page += FPSTR(HTTP_1BAR);
        page += FPSTR(HTTP_2BAR);
        page += FPSTR(HTTP_3BAR);
        page += FPSTR(HTTP_4BAR);
        
        page += FPSTR(HTTP_HEAD_END);

        // chiama la callback per lo scan
        WiFiCallback.SCANmode();

        if (NETnumber == 0) 
        {
          Serial.println("No networks found");
          page += F("No networks found. Refresh to scan again.");
        } 
        else 
        {
          
            //display networks in page
            for (int i = 0; i < NETnumber; ++i) 
            {
                
                String item = FPSTR(HTTP_ITEM);

                  item.replace("{v}", WiFi.SSID(i));
                  
                  if ( ComputeBar(WiFi.RSSI(i)) == 4)
                    item.replace("{b}", "ba"); // ba -> MAX
                  
                  if (ComputeBar(WiFi.RSSI(i)) == 3)
                    item.replace("{b}", "bb");
                  
                  if (ComputeBar(WiFi.RSSI(i)) == 2)
                    item.replace("{b}", "bc");
                  
                  if (ComputeBar(WiFi.RSSI(i)) == 1)
                    item.replace("{b}", "bd");
                  
                  if (WiFi.encryptionType(i) != WIFI_AUTH_OPEN) 
                    item.replace("{i}", "l");
                    
                  else 
                    item.replace("{i}", "");
                  
                Serial.println(item);
                page += item;
                
            }//for
      
            page += "<br/>";
        }

        page += FPSTR(HTTP_FORM_START);
         
        page += FPSTR(HTTP_FORM_END);
        page += FPSTR(HTTP_SCAN_LINK);
      
        page += FPSTR(HTTP_END);

        //At the end
        RefreshPageMode = 1; // questo riattiva la modalita' refresh per /wifisave
        oneshot = 0;
        RetryCount = 0;
        CheckStatus = WAIT;
      
        Serial.println("Sending 200 - End wifi");
    }
    
    else if (req_one == "/wifisave") // uso quella split (query con risposta) 
    {
      Serial.print("Inside - Request: ");
      Serial.println(req_two);

      delay(10);
      
      //Try to connecting ...
      if (oneshot == 0)
      {
        PopulateArgsArrey(string2char(req_two));

        delay(10);

        WiFiCallback.APSTAmode();
        
        oneshot = 1;
      }

      page = FPSTR(HTTP_HEAD);
      
      if (RefreshPageMode == 1) 
        page.replace("{h}", "<meta http-equiv=\"refresh\" content=\"2\">");
      else
        page.replace("{h}", "");


      page.replace("{v}", "WiFi Configuration Saved"); // si usa dopo che hai messo un segnaposto sul codice HTML
      
      page += FPSTR(HTTP_SCRIPT);
      page += FPSTR(HTTP_STYLE);
      page += FPSTR(HTTP_HEAD_END);

      if (RetryCount >= 7)
      {
        Serial.println("Retry Elapsed");
        page += FPSTR(HTTP_SAVED_FAILED);
        page.replace("{x}", "Timeout elapsed"); // gestire i vari casi, please
        RefreshPageMode = 0;
      } 
      
      else if (CheckStatus == FAILURE)
      {
        Serial.println("Failure");
        page += FPSTR(HTTP_SAVED_FAILED);
        page.replace("{x}", "Incorrect network name (SSID) or password"); // gestire i vari casi, please
        RefreshPageMode = 0;
      }   

      else if (CheckStatus == WAIT)
      {
        Serial.println("Wait");
        page += FPSTR(HTTP_SAVED_WAIT);
        page.replace("{bar}", String(RetryCount));
        RefreshPageMode = 1;

        RetryCount++;   
      }

      else if (CheckStatus == CONNECTED)
      {
        struct settings_t *struct_pointer_tmp = &settings;

        Serial.println("Success");  
        page += FPSTR(HTTP_SAVED_SUCCESS);
        page.replace("{a}", struct_pointer_tmp->ssid);

        if (LinkStatus == LINK_WAN)
            page.replace("{b}", "available");
        else
            page.replace("{b}", "<strong>not</strong> available");

        page.replace("{c}", struct_pointer_tmp->hostname);
        page.replace("{d}", WiFi.localIP().toString());
      
        RefreshPageMode = 0;
      }

      page += FPSTR(HTTP_END);

      /* FIX IT
      if (CheckStatus == CONNECTED_NOWAN)
      {
        page.replace("{x}", "Connected but Internet link is down ");
        // cambiare la modalita' - successo passo a only STA
        RefreshPageMode = 0;
      }

      if (CheckStatus == SSID_NOVALID)
      {
        page.replace("{x}", "SSID is not valid, Try to Reconnecting, click here <a href='/wifi'>link</a> to return on previous menu ");
        RefreshPageMode = 0;
      }

      if (CheckStatus == PASSKEY_NOVALID)
      {
        page.replace("{x}", "Passkey is not valid, Try to Reconnecting, click here <a href='/wifi'>link</a> to return on previous menu ");
        RefreshPageMode = 0;
      }
      */

    }

    else if (req == "/i")
    {
      char tmp[8];
      sprintf( tmp, "%04X",(uint16_t)(ESP.getEfuseMac() >> 32) );
      
      page = FPSTR(HTTP_HEAD);
      page.replace("{v}", "Info");
      page.replace("{h}", "");
      page += FPSTR(HTTP_SCRIPT);
      page += FPSTR(HTTP_STYLE);
      page += FPSTR(HTTP_HEAD_END);
      page += F("<dl>");
      page += F("<dt>Chip ID</dt><dd>");
      page += String(tmp);
      page += F("</dd>");
      page += F("<dt>IDE Flash Size</dt><dd>");
      page += ESP.getFlashChipSize();
      page += F(" bytes</dd>");
      page += F("<dt>Soft AP IP</dt><dd>");
      page += WiFi.softAPIP().toString();
      page += F("</dd>");
      page += F("<dt>Soft AP MAC</dt><dd>");
      page += WiFi.softAPmacAddress();
      page += F("</dd>");
      page += F("<dt>Station MAC</dt><dd>");
      page += WiFi.macAddress();
      page += F("</dd>");
      page += F("</dl>");
      page += FPSTR(HTTP_END);
    }
    
    else if (req == "/iot")
    {
        struct settings_t *struct_pointer_tmp = &settings;

        Serial.println("IoT mode enabled"); 

        page = FPSTR(HTTP_HEAD);
        page.replace("{v}", "Info");
        page.replace("{h}", "");
 
        page += FPSTR(HTTP_SAVED_IOT);
        page.replace("{a}", struct_pointer_tmp->ssid);

        if (LinkStatus == LINK_WAN)
            page.replace("{b}", "available");
        else
            page.replace("{b}", "<strong>not</strong> available");

        page.replace("{c}", struct_pointer_tmp->hostname);
        page.replace("{d}", WiFi.localIP().toString());

        page += FPSTR(HTTP_END);

        client.print(page);
        client.stop(); // prevent send page before change mode

        delay(5000);

        WiFiCallback.STAmode(); // only STA mode
        delay(1000);

    }

    else if (req == "/r")
    {
        page = FPSTR(HTTP_HEAD);
        page.replace("{v}", "Reset");
        page.replace("{h}", "");
        page += FPSTR(HTTP_SCRIPT);
        page += FPSTR(HTTP_STYLE);
        page += FPSTR(HTTP_HEAD_END);
        page += F("Module will reset in a few seconds.");
        page += FPSTR(HTTP_END);

        client.print(page); // force send page before restart
        
        delay(3000);
        ESP.restart();
    }
    
    else
    {
        page = FPSTR(HTTP_NOTFOUND);
        Serial.println("Sending 404");
    }

    client.print(page);

    Serial.println("Done with client");

}

// END AP MODE

// ________________________________________________________________________________________________

// START STA MODE

String CheckedOut(char c)
{

if (c == 'O')
    return "active";
else
    return "";
}
String CheckedIn(char c)
{

if (c == 'I')
    return "active";
else
    return "";
}
String CheckedServo(char c)
{

if (c == 'S')
    return "active";
else
    return "";
}
String CheckedPwm(char c)
{

if (c == 'P')
    return "active";
else
    return "";
}
String CheckedOn(String s)
{

if (s == "ON")
    return "active";
else
    return "";
}
String CheckedOff(String s)
{

if (s == "OFF")
    return "active";
else
    return "";
}





void handleNotFound(){

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += serverIoT.uri();
  message += "\nMethod: ";
  message += (serverIoT.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += serverIoT.args();
  message += "\n";
  for (uint8_t i=0; i<serverIoT.args(); i++){
    message += " " + serverIoT.argName(i) + ": " + serverIoT.arg(i) + "\n";
  }
  serverIoT.send(404, "text/plain", message);
}


String getPage()
{

  struct AnalogGpioMap_t *Apointer;
  struct DigitalGpioMap_t *Dpointer; 

  String page = FPSTR(HTTP_IOT_HEADER);

  page += FPSTR(HTTP_IOT_SCRIPT);

  page += FPSTR(HTTP_IOT_STYLE);

  page += FPSTR(HTTP_IOT_TITLE);

  page += FPSTR(HTTP_IOT_ANALOG_ITEM);
  page += FPSTR(HTTP_IOT_ANALOG_TABLE);

  page += FPSTR(HTTP_IOT_ITEM_D0);
  page += FPSTR(HTTP_IOT_ITEM_D1);
  page += FPSTR(HTTP_IOT_ITEM_D2);
  page += FPSTR(HTTP_IOT_ITEM_D3);
  page += FPSTR(HTTP_IOT_ITEM_D4);
  page += FPSTR(HTTP_IOT_ITEM_D5);
  page += FPSTR(HTTP_IOT_ITEM_D6);
  page += FPSTR(HTTP_IOT_ITEM_D7);
  page += FPSTR(HTTP_IOT_ITEM_D8);
  page += FPSTR(HTTP_IOT_ITEM_D9);
  page += FPSTR(HTTP_IOT_ITEM_D10);
  page += FPSTR(HTTP_IOT_ITEM_D11);
  page += FPSTR(HTTP_IOT_ITEM_D12);
  page += FPSTR(HTTP_IOT_ITEM_D13);

  page += FPSTR(HTTP_IOT_CLOSE);

// modified page html

  Apointer = &AnalogGpioMap[0];

  page.replace( "{A0label}",   String(Apointer->label) );
  page.replace( "{A0value}",   String(Apointer->value) );
  page.replace( "{A0voltage}", String(Apointer->voltage) );

  Apointer = &AnalogGpioMap[1];

  page.replace( "{A1label}",   String(Apointer->label) );
  page.replace( "{A1value}",   String(Apointer->value) );
  page.replace( "{A1voltage}", String(Apointer->voltage) );

  Apointer = &AnalogGpioMap[2];

  page.replace( "{A2label}",   String(Apointer->label) );
  page.replace( "{A2value}",   String(Apointer->value) );
  page.replace( "{A2voltage}", String(Apointer->voltage) );

  Apointer = &AnalogGpioMap[3];

  page.replace( "{A3label}",   String(Apointer->label) );
  page.replace( "{A3value}",   String(Apointer->value) );
  page.replace( "{A3voltage}", String(Apointer->voltage) );

  Apointer = &AnalogGpioMap[4];

  page.replace( "{A4label}",   String(Apointer->label) );
  page.replace( "{A4value}",   String(Apointer->value) );
  page.replace( "{A4voltage}", String(Apointer->voltage) );

  Apointer = &AnalogGpioMap[5];

  page.replace( "{A5label}",   String(Apointer->label) );
  page.replace( "{A5value}",   String(Apointer->value) );
  page.replace( "{A5voltage}", String(Apointer->voltage) );

  // Digital
  Dpointer = &DigitalGpioMap[13];
        page.replace( "{D13Input}", String(Dpointer->value) );
        page.replace( "{D13label}", Dpointer->label );
        page.replace( "{D13set}"  , Dpointer->ReadyFunc );

        page.replace( "{D13on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D13off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D13outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D13incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D13servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D13pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[12];
        page.replace( "{D12Input}", String(Dpointer->value) );
        page.replace( "{D12label}", Dpointer->label );
        page.replace( "{D12set}"  , Dpointer->ReadyFunc );

        page.replace( "{D12on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D12off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D12outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D12incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D12servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D12pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[11];
        page.replace( "{D11Input}", String(Dpointer->value) );
        page.replace( "{D11label}", Dpointer->label );
        page.replace( "{D11set}"  , Dpointer->ReadyFunc );

        page.replace( "{D11on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D11off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D11outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D11incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D11servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D11pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[10];
        page.replace( "{D10Input}", String(Dpointer->value) );
        page.replace( "{D10label}", Dpointer->label );
        page.replace( "{D10set}"  , Dpointer->ReadyFunc );

        page.replace( "{D10on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D10off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D10outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D10incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D10servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D10pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[9];
        page.replace( "{D9Input}", String(Dpointer->value) );
        page.replace( "{D9label}", Dpointer->label );
        page.replace( "{D9set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D9on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D9off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D9outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D9incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D9servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D9pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[8];
        page.replace( "{D8Input}", String(Dpointer->value) );
        page.replace( "{D8label}", Dpointer->label );
        page.replace( "{D8set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D8on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D8off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D8outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D8incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D8servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D8pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[7];
        page.replace( "{D7Input}", String(Dpointer->value) );
        page.replace( "{D7label}", Dpointer->label );
        page.replace( "{D7set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D7on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D7off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D7outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D7incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D7servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D7pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[6];
        page.replace( "{D6Input}", String(Dpointer->value) );
        page.replace( "{D6label}", Dpointer->label );
        page.replace( "{D6set}" ,  Dpointer->ReadyFunc ); 

        page.replace( "{D6on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D6off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D6outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D6incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D6servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D6pwmcheck}" ,    CheckedPwm(Dpointer->mode) );       

  Dpointer = &DigitalGpioMap[5];
        page.replace( "{D5Input}", String(Dpointer->value) );
        page.replace( "{D5label}", Dpointer->label );
        page.replace( "{D5set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D5on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D5off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D5outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D5incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D5servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D5pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[4];
        page.replace( "{D4Input}", String(Dpointer->value) );
        page.replace( "{D4label}", Dpointer->label );
        page.replace( "{D4set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D4on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D4off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D4outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D4incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D4servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D4pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[3];
        page.replace( "{D3Input}", String(Dpointer->value) );
        page.replace( "{D3label}", Dpointer->label );
        page.replace( "{D3set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D3on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D3off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D3outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D3incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D3servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D3pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[2];
        page.replace( "{D2Input}", String(Dpointer->value) );
        page.replace( "{D2label}", Dpointer->label );
        page.replace( "{D2set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D2on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D2off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D2outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D2incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D2servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D2pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  Dpointer = &DigitalGpioMap[1];
        page.replace( "{D1Input}", String(Dpointer->value) );
        page.replace( "{D1label}", Dpointer->label );
        page.replace( "{D1set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D1on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D1off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D1outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D1incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D1servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D1pwmcheck}" ,    CheckedPwm(Dpointer->mode) );
    
  Dpointer = &DigitalGpioMap[0];
        page.replace( "{D0Input}", String(Dpointer->value) );
        page.replace( "{D0label}", Dpointer->label );
        page.replace( "{D0set}" ,  Dpointer->ReadyFunc );

        page.replace( "{D0on}" ,          CheckedOn(Dpointer->label) );
        page.replace( "{D0off}" ,         CheckedOff(Dpointer->label) );
        page.replace( "{D0outcheck}" ,    CheckedOut(Dpointer->mode) );
        page.replace( "{D0incheck}" ,     CheckedIn(Dpointer->mode) );
        page.replace( "{D0servocheck}" ,  CheckedServo(Dpointer->mode) );
        page.replace( "{D0pwmcheck}" ,    CheckedPwm(Dpointer->mode) );

  return page;
}



void updateGPIO(int gpio, String DxValue) 
{
    
  //Serial.println(""); DBG
  //Serial.println("Update GPIO "); Serial.print(gpio); Serial.print(" -> "); Serial.println(DxValue);
  
  if ( DxValue == "ON" ) 
  {

    VirtualpinMode(gpio, OUTPUT);
    VirtualdigitalWrite(gpio, HIGH);

    DigitalGpioMap[gpio].value = 1;
    DigitalGpioMap[gpio].mode = 'O';
    DigitalGpioMap[gpio].label = "ON";

    String str= "setMODE(" + String(gpio) + ", 0, 0);" ;
    DigitalGpioMap[gpio].ReadyFunc = str;

    serverIoT.send ( 200, "text/html", getPage() );
  } 
  else if ( DxValue == "OFF" ) 
  {

    VirtualpinMode(gpio, OUTPUT);
    VirtualdigitalWrite(gpio, LOW);

    DigitalGpioMap[gpio].value = 0;
    DigitalGpioMap[gpio].mode = 'O';
    DigitalGpioMap[gpio].label = "OFF";

    String str= "setMODE(" + String(gpio) + ",0,0);" ;
    DigitalGpioMap[gpio].ReadyFunc = str;

    serverIoT.send ( 200, "text/html", getPage() );
  }
  else if ( DxValue == "INPUT" ) 
  {

    VirtualpinMode(gpio, INPUT);

    DigitalGpioMap[gpio].value = VirtualdigitalRead(gpio);
    DigitalGpioMap[gpio].mode = 'I';
    DigitalGpioMap[gpio].label = "INPUT";

    String str= "setMODE(" + String(gpio) + ",1,0);" ;
    DigitalGpioMap[gpio].ReadyFunc = str;

    serverIoT.send ( 200, "text/html", getPage() );
  } 
  else if ( DxValue == "SERVO" ) 
  {
        
    DigitalGpioMap[gpio].value = 0;
    DigitalGpioMap[gpio].mode = 'S';
    DigitalGpioMap[gpio].label = "SERVO";

    String str= "setMODE(" + String(gpio) + ",2,0);" ;
    DigitalGpioMap[gpio].ReadyFunc = str;

    int s = serverIoT.arg("S").toInt();

    if( s > 0 && s < 181) // init
    {
        DigitalGpioMap[gpio].value = s;

        VirtualservoAttach(gpio);
        delay(10);
        VirtualservoWrite(gpio, s);
        delay(10);
        VirtualservoDetach(gpio);
    }
    else
    {
        VirtualservoAttach(gpio);
        delay(10);
        VirtualservoWrite(gpio, 0);
        delay(10);
        VirtualservoDetach(gpio);
    }

    serverIoT.send ( 200, "text/html", getPage() );
  }

  else if ( DxValue == "PWM" ) 
  {

    DigitalGpioMap[gpio].value = 0;
    DigitalGpioMap[gpio].mode = 'P';
    DigitalGpioMap[gpio].label = "PWM";

    String str= "setMODE(" + String(gpio) + ",3,0);" ;
    DigitalGpioMap[gpio].ReadyFunc = str;

    int p = serverIoT.arg("P").toInt();

    if ( p > 0 && p < 256)
    {
        DigitalGpioMap[gpio].value = p;
        VirtualanalogWrite(gpio, p);
    }
    else // init sara' 0
    {
        VirtualanalogWrite(gpio, 0);
    }

    serverIoT.send ( 200, "text/html", getPage() );
  } 

  else 
  {
    Serial.println("Args Error");
  } 

}


void handleRoot(){ 
  if ( serverIoT.hasArg("D0") ) 
      updateGPIO(0, serverIoT.arg("D0"));
  else if ( serverIoT.hasArg("D1") ) 
      updateGPIO(1, serverIoT.arg("D1"));
  else if ( serverIoT.hasArg("D2") ) 
      updateGPIO(2, serverIoT.arg("D2"));
  else if ( serverIoT.hasArg("D3") ) 
      updateGPIO(3, serverIoT.arg("D3"));
  else if ( serverIoT.hasArg("D4") ) 
      updateGPIO(4, serverIoT.arg("D4"));
  else if ( serverIoT.hasArg("D5") ) 
      updateGPIO(5, serverIoT.arg("D5"));
  else if ( serverIoT.hasArg("D6") ) 
      updateGPIO(6, serverIoT.arg("D6"));
  else if ( serverIoT.hasArg("D7") ) 
      updateGPIO(7, serverIoT.arg("D7"));
  else if ( serverIoT.hasArg("D8") ) 
      updateGPIO(8, serverIoT.arg("D8"));
  else if ( serverIoT.hasArg("D9") ) 
      updateGPIO(9, serverIoT.arg("D9"));
  else if ( serverIoT.hasArg("D10") ) 
      updateGPIO(10, serverIoT.arg("D10"));
  else if ( serverIoT.hasArg("D11") ) 
      updateGPIO(11, serverIoT.arg("D11"));
  else if ( serverIoT.hasArg("D12") ) 
      updateGPIO(12, serverIoT.arg("D12"));
  else if ( serverIoT.hasArg("D13") ) 
      updateGPIO(13, serverIoT.arg("D13"));
  else 
      serverIoT.send ( 200, "text/html", getPage() );

}


#if 1 //test per SD CARD
void STA_SettingMode()
{ 

static byte oneshot;

if (!oneshot)
{

    serverIoT.on("/", handleRoot);

    serverIoT.on("/inline", [](){
    serverIoT.send(200, "text/plain", "this works as well");
    });

    serverIoT.onNotFound(handleNotFound);

    serverIoT.begin();

    // Init Label GPIO Map
    for(int i=0; i < 14; i++)
    {
        DigitalGpioMap[i].label = "OFF";
        DigitalGpioMap[i].value = 0;
        DigitalGpioMap[i].mode = 'O';
        
        String str= "setMODE(" + String(i) + ",0,0);" ;
        DigitalGpioMap[i].ReadyFunc = str ;
    }

    oneshot = 1; 
}

//loop
serverIoT.handleClient();

}

#else

bool loadFromSdCard(String path){
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.htm";

  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".htm")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".xml")) dataType = "text/xml";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";

  File dataFile = WrapOpen(SD, path.c_str());
  
  if(dataFile.isDirectory()){
    path += "/index.htm";
    dataType = "text/html";
    dataFile = WrapOpen(SD, path.c_str());
  }

  if (!dataFile)
    return false;

  //if (server.hasArg("download")) dataType = "application/octet-stream";

  if (serverIoT.streamFile(dataFile, dataType) != dataFile.size()) {
    Serial.println("Sent less data than expected!");
  }

  dataFile.close();
  return true;
}

void handleNotFound(){

  if(cardSize && loadFromSdCard(serverIoT.uri())) return;
  String message = "SDCARD Not Detected\n\n";
  message += "URI: ";
  message += serverIoT.uri();
  message += "\nMethod: ";
  message += (serverIoT.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += serverIoT.args();
  message += "\n";
  for (uint8_t i=0; i<serverIoT.args(); i++){
    message += " NAME:"+serverIoT.argName(i) + "\n VALUE:" + serverIoT.arg(i) + "\n";
  }
  serverIoT.send(404, "text/plain", message);
  Serial.print(message);

}


void STA_SettingMode()
{ 

static byte oneshot;

    if (!oneshot)
    {
        //server.close();

        //serverIoT.on("/", handleRootSUKA); //x ora no
        serverIoT.onNotFound(handleNotFoundSUKA);

        serverIoT.begin();

        oneshot = 1; 
    }

//loop
serverIoT.handleClient();

}

#endif


// END STA MODE

// ________________________________________________________________________________________________

// START MANUAL MODE

void MANUAL_SettingMode(){ 

  static byte oneshot;

  if (!oneshot){
      serverMANUAL.onNotFound(RESThandle);
      serverMANUAL.begin();
         
      oneshot = 1; 
  }



  String rd = "";
  rd = VirtualReadAvrMsg("ACK");

  if(rd != "" && webSocketData.typeMess == WStype_CONNECTED){
    String message = "sms: ";
    message += rd;
    webSocket.sendTXT(webSocketData.member, message);
    Serial.println("[MANUAL_setting_mode]Mess da AVR inviato: "+rd+"\n");
  }

  serverMANUAL.handleClient();
  

}


void RESThandle(){
  Serial.println("[RESThandle] URI: "+serverMANUAL.uri());
  if(serverMANUAL.uri() != "/favicon.ico"){
    webSocketData.uri = serverMANUAL.uri();       //GUARDA QUA
    String page = FPSTR(HTTP_WEBSOCKET_HEAD);
    page += FPSTR(HTTP_WEBSOCKET_STYLE);
    page += FPSTR(HTTP_WEBSOCKET_ENDHEAD);
    page += FPSTR(HTTP_WEBSOCKET_BODY);    
    page += FPSTR(HTTP_WEBSOCKET_INITSCRIPT); 
    page += "ws://"+WiFi.localIP().toString()+":8888/"; 
    page += FPSTR(HTTP_WEBSOCKET_SCRIPT);    
    page += FPSTR(HTTP_WEBSOCKET_ENDBODY);

    serverMANUAL.send(200, "text/html", page);
    Serial.println("[RESThandle]Pagina WebSocket inviata\n");
  }
    
}
void WEBSOCKEThandle(){
  
  Serial.println("[WebSocket]invio dati\n");
  // Check if a client has connected
  VirtualStringSend(webSocketData.uri);

  String message = "";
  message += "URI: ";
  message += webSocketData.uri;
  webSocket.sendTXT(webSocketData.member, message);

  message = "Method: ";
  message += (serverMANUAL.method() == HTTP_GET)?"GET":"POST";
  webSocket.sendTXT(webSocketData.member, message);

  message = "Arguments: ";
  message += serverMANUAL.args();
  webSocket.sendTXT(webSocketData.member, message);

  /*
  for (uint8_t i=0; i<serverMANUAL.args(); i++){
      message += "\n " + serverMANUAL.argName(i) + ": " + serverMANUAL.arg(i) + ";";
  }
  webSocket.sendTXT(webSocketData.member, message);*/
  
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            webSocketData.typeMess = WStype_DISCONNECTED;
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
                webSocketData.typeMess = WStype_CONNECTED;
                webSocketData.member = num;
                WEBSOCKEThandle();
            }
            break;
        
    }

}


































int ComputeBar(int value) 
{
  int quality = 0;

  value = abs(value);

  if (value <= 100 && value >= 91) 
    quality = 1;
  else if (value <= 90 && value >= 80) 
    quality = 2;

  else if (value <= 79 && value >= 60) 
    quality = 3;
  else 
    quality = 4;
  
  return quality;
}


void PopulateArgsArrey(char *str)
{
  char * pch;
  int i = 0;
  pch = strtok (str,"=");
  
  while (pch != NULL)
  {
    pch = strtok (NULL, "=");
    Serial.println(pch); 
    if(i == 0)
    {
      WifisaveArg[i].key = 's';
      pch[strlen(pch)-2] = 0;
      WifisaveArg[i].value = pch;
    }     
    if(i == 1)
    {
      WifisaveArg[i].key = 'p';
      pch[strlen(pch)-2] = 0;
      WifisaveArg[i].value = pch;
    }     
    if(i == 2)
    {
      WifisaveArg[i].key = 'g';
      WifisaveArg[i].value = pch;
    }
    i++;
  }

    struct Args *argsOne   = &WifisaveArg[0];
    struct Args *argsTwo   = &WifisaveArg[1];
    struct Args *argsThree = &WifisaveArg[2];

    strncpy(settings.ssid, argsOne->value, strlen(argsOne->value));
    settings.ssid[strlen(argsOne->value)] = '\0';

    strncpy(settings.password, argsTwo->value, strlen(argsTwo->value));
    settings.password[strlen(argsTwo->value)] = '\0';

    strncpy(settings.hostname, argsThree->value, strlen(argsThree->value));
    settings.hostname[strlen(argsThree->value)] = '\0';

}

void ReadSetting( struct settings_t *set ) 
{
    Serial.print("IoT mode : ");
    Serial.println(set->IoTMode);

    Serial.print("SSID : ");
    Serial.println(set->ssid);

    Serial.print("Password : ");
    Serial.println(set->password);

    Serial.print("Hostname : ");
    Serial.println(set->hostname);

    Serial.println("");
}

void storeStruct(void *data_source, size_t size)
{
  EEPROM.begin(size * 2);
  for(size_t i = 0; i < size; i++)
  {
    char data = ((char *)data_source)[i];
    EEPROM.write(i, data);
  }
  EEPROM.commit();
}

void loadStruct(void *data_dest, size_t size)
{
    EEPROM.begin(size * 2);
    for(size_t i = 0; i < size; i++)
    {
        char data = EEPROM.read(i);
        ((char *)data_dest)[i] = data;
    }
}


int AnalogIndex = 24;

void Task644ReadInput()
{
    // legge un ADC ogni secondo in ciclo continuo...

    // Analog
    int j;
    static int shoot; 

    // ManualMode -- se e' 1 0 2 allora ritorna
    MMMode = VirtualUseCase();
    if (MMMode != 0)  
        return;

    if (shoot == 0) // only for test (oneshot)
        shoot = VirtualMacADDR( WiFi.macAddress() );

    // ADC
    j = (AnalogIndex - 24);

    String label;
        label += "A";
        label += String(j);
        
    AnalogGpioMap[j].value = VirtualanalogRead(AnalogIndex);
    AnalogGpioMap[j].label = label; 

    serverIoT.handleClient();   // force Webserver Handle

    AnalogGpioMap[j].voltage = 0; // else condition
        
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    if (AnalogGpioMap[j].value > 0)
        AnalogGpioMap[j].voltage = AnalogGpioMap[j].value * (0.0048875855); //(5.0 / 1023.0)

    AnalogIndex++;

    if (AnalogIndex == 30)
        AnalogIndex = 24; // count restart 

    // Digital
    for(int i = 0; i < 14; i++)
    {
        if (DigitalGpioMap[i].mode == 'I')
        {
            DigitalGpioMap[i].value = VirtualdigitalRead(i);
            serverIoT.handleClient();   // force Webserver Handle
        }
    }

}