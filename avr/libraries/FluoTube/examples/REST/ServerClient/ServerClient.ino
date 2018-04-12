#include<FluoTube.h>             

unsigned long t1;
unsigned long t2;
int i = 0;
int spam = 0;

void setup() {
  Serial.begin(115200);         
  Serial.println("AVR booting ...");

  pinMode(13, OUTPUT);
  FluoTube.Begin();             
  FluoTube.WiFi.Setting("Androidadry", "hellohello", "fluo"); //Set WiFi (ssid, passkey, hostname)
  FluoTube.WiFi.ServerRest();   // enable Rest Server default port 8080

  t1 = millis();
}

void loop() {
 
  FluoTube.Run();                 
  if (FluoTube.WiFi.Available()) { 
    Parser(FluoTube.WiFi.RestRead()); 
    if(spam > 0){
      t2 = millis();
      if( (t2-t1) > 15000){        
        FluoTube.sendMsgToESP("Hi, I'm AVR and I sent  "+ String(spam)+" messages");
        spam++;
        t1 = millis();
      }
    }
    
  }
  
}
void Parser(String data) {            
  if (data == "/l13on") {             
    digitalWrite(13, HIGH);
    FluoTube.sendMsgToESP("Led 13 ON");
    spam = 1;
  } if (data == "/l13off") {
    digitalWrite(13, LOW);
    FluoTube.sendMsgToESP("Led 13 OFF");
    spam = 1;
  } if (data == "ADRR") {
    Serial.println("Inviare Richieste Rest all'indirizzo: ");  
    Serial.println(FluoTube.WiFi.Info());
    spam = 1; 
  }
}
