#include <FluoTube.h>             //include la libreria FluoTube

  void setup(){
      Serial.begin(115200);         //abilita la seriale di debug che potrai utilizzare usando SerialMonitor di ArduinoIDE
      Serial.println("AVR booting ...");

      pinMode(13, OUTPUT);
      FluoTube.Begin();             //inizializza la libreria FluoTube
    
      FluoTube.WiFi.Setting("AndroidFabio", "ciao4321", "fluo"); //imposti credenziali WiFi a cui connettersi (ssid, passkey, hostname)
      FluoTube.WiFi.ServerRest();   //Abilita un server REST sulla porta 8080
  }

  void loop(){
    FluoTube.Run();                 // Manda in esecuzione la libreria
    if(FluoTube.WiFi.Available())  //se soddisfatta la board ha un indirizzo IP valido assegnato (Si può vedere che è connessa dai led)
      Parser(FluoTube.WiFi.RestRead()); //la funzione RestRead() restituisce la stringa che è stata inviata dal client
  }
  void Parser(String data){
    if(data == "/l13on"){
      digitalWrite(13, HIGH); 
    }if(data == "/l13off"){
      digitalWrite(13,LOW);  
    }if(data == "ADRR"){
      Serial.println("Inviare Richieste Rest all'indirizzo: "+FluoTube.WiFi.Info());  
    }
  }