/* 
 Name:      SD_Update.ino
 Created:   12.09.2017 15:07:17
 Author:    Frederik Merz <frederik.merz@novalight.de>
 Purpose:   Update firmware from SD card

 Steps:
   1. Flash this image to the ESP32 an run it
   2. Copy update.bin to a SD-Card, you can basically
      compile this or any other example
      then copy and rename the app binary to the sd card root
   3. Connect SD-Card as shown in SD example, 
      this can also be adapted for SPI
   3. After successfull update and reboot, ESP32 shall start the new app
*/

#include <Update.h>
#include <FS.h>
#include <SD.h>
#include <Fluotube.h>

// perform the actual update from a given stream
void performUpdate(Stream &updateSource, size_t updateSize) {
   if (Update.begin(updateSize)) {      
      size_t written = Update.writeStream(updateSource);
      if (written == updateSize) {
         FluoTube.debugln("Written : " + String(written) + " successfully");
      }
      else {
         FluoTube.debugln("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
      }
      if (Update.end()) {
         FluoTube.debugln("OTA done");
         if (Update.isFinished()) {
            FluoTube.debugln("Update successfully completed. Rebooting.");
         }
         else {
            FluoTube.debugln("Update not finished? Something went wrong");
         }
      }
      else {
         FluoTube.debugln("Error Occurred. Error #: " + String(Update.getError()));
      }

   }
   else
   {
      FluoTube.debugln("Not enough space to begin OTA");
   }
}

// check given FS for valid update.bin and perform update if available
void updateFromFS(fs::FS &fs) {
   File updateBin = fs.open("/update.bin");
   if (updateBin) {
      if(updateBin.isDirectory()){
         FluoTube.debugln("Error, update.bin is not a file");
         updateBin.close();
         return;
      }

      size_t updateSize = updateBin.size();

      if (updateSize > 0) {
         FluoTube.debugln("Try to start update");
         performUpdate(updateBin, updateSize);
      }
      else {
         FluoTube.debugln("Error, file is empty");
      }

      updateBin.close();
    
      // whe finished remove the binary from sd card to indicate end of the process
      fs.remove("/update.bin");      
   }
   else {
      FluoTube.debugln("Could not load update.bin from sd root");
   }
}
SPIClass SPISDc(VSPI);
void setup() {
   uint8_t cardType;

   FluoTube.setup();
   FluoTube.debugln("Welcome to the SD-Update example");

   // You can uncomment this and build again
   // FluoTube.debugln("Update successfull");

   //first init and check SD card
   if ( !SD.begin(SD_CS, SPISDc, 4000000, "/sd") ) {
      rebootEspWithReason("Card Mount Failed");
   }

   cardType = SD.cardType();

   if (cardType == CARD_NONE) {
      rebootEspWithReason("No SD card attached");
   }else{
      updateFromFS(SD);
  }
}

void rebootEspWithReason(String reason){
    FluoTube.debugln( String(reason) );
    delay(1000);
    ESP.restart();
}

//will not be reached
void loop() {
  
}