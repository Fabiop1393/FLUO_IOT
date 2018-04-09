#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <Fluotube.h>

void listDire(fs::FS &fs, const char * dirname, uint8_t levels);
void createDire(fs::FS &fs, const char * path);
void removeDire(fs::FS &fs, const char * path);
void readFil(fs::FS &fs, const char * path);
void writeFil(fs::FS &fs, const char * path, const char * message);
void appendFil(fs::FS &fs, const char * path, const char * message);
void renameFil(fs::FS &fs, const char * path1, const char * path2);
void deleteFil(fs::FS &fs, const char * path);

SPIClass SPISDc(VSPI);

void setup(){
   
    FluoTube.setup();

    if(! SD.begin(SD_CS, SPISDc, 4000000, "/sd") ){
        FluoTube.debugln("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        FluoTube.debugln("No SD card attached");
        return;
    }

    FluoTube.debug("SD Card Type: ");
    if(cardType == CARD_MMC){
        FluoTube.debugln("MMC");
    } else if(cardType == CARD_SD){
        FluoTube.debugln("SDSC");
    } else if(cardType == CARD_SDHC){
        FluoTube.debugln("SDHC");
    } else {
        FluoTube.debugln("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    unsigned long long1 = (unsigned long)((cardSize & 0xffff0000)>>16);
    unsigned long long2 = (unsigned long)((cardSize & 0x0000ffff));
    FluoTube.debugln("SD Card Size: " + String(long1, HEX)+String(long2,HEX) + " MB");

    listDire(SD, "/", 0);
    createDire(SD, "/mydir");
    listDire(SD, "/", 0);
    removeDire(SD, "/mydir");
    listDire(SD, "/", 2);
    writeFil(SD, "/hello.txt", "Hello ");
    appendFil(SD, "/hello.txt", "World!\n");
    readFil(SD, "/hello.txt");
    deleteFil(SD, "/foo.txt");
    renameFil(SD, "/hello.txt", "/foo.txt");
    readFil(SD, "/foo.txt");
    testFilIO(SD, "/test.txt");

    long1 = (unsigned long)((SD.totalBytes()/(1024 * 1024) & 0xffff0000)>>16);
    long2 = (unsigned long)((SD.totalBytes() & 0x0000ffff));
    FluoTube.debugln("Total space: " + String(long1, HEX)+String(long2,HEX) + " MB");
    
    long1 = (unsigned long)((SD.usedBytes()/(1024 * 1024) & 0xffff0000)>>16);
    long2 = (unsigned long)((SD.usedBytes() & 0x0000ffff));
    FluoTube.debugln("Used space: " + String(long1, HEX)+String(long2,HEX) + " MB");
}

void loop(){

}

// Filesystem Function

void listDire(fs::FS &fs, const char * dirname, uint8_t levels){
    FluoTube.debugln("Listing directory: " + String(dirname) );

    File root = fs.open(dirname);
    if(!root){
        FluoTube.debugln("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        FluoTube.debugln("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            FluoTube.debug("  DIR : ");
            FluoTube.debugln( String(file.name()) );
            if(levels){
                listDire(fs, file.name(), levels -1);
            }
        } else {
            FluoTube.debug("  FILE: ");
            FluoTube.debug( String(file.name()) );
            FluoTube.debug("  SIZE: ");
            FluoTube.debugln( String(file.size()) );
        }
        file = root.openNextFile();
    }
}

void createDire(fs::FS &fs, const char * path){
    FluoTube.debugln("Creating Dir: " + String(path) );
    if(fs.mkdir(path)){
        FluoTube.debugln("Dir created");
    } else {
        FluoTube.debugln("mkdir failed");
    }
}

void removeDire(fs::FS &fs, const char * path){
    FluoTube.debugln("Removing Dir: " + String(path));
    if(fs.rmdir(path)){
        FluoTube.debugln("Dir removed");
    } else {
        FluoTube.debugln("rmdir failed");
    }
}

void readFil(fs::FS &fs, const char * path){
    FluoTube.debugln("Reading file: " + String(path) );

    File file = fs.open(path);
    if(!file){
        FluoTube.debugln("Failed to open file for reading");
        return;
    }

    FluoTube.debug("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFil(fs::FS &fs, const char * path, const char * message){
    FluoTube.debugln("Writing file: " + String(path) );

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        FluoTube.debugln("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        FluoTube.debugln("File written");
    } else {
        FluoTube.debugln("Write failed");
    }
    file.close();
}

void appendFil(fs::FS &fs, const char * path, const char * message){
    FluoTube.debugln("Appending to file: " + String(path) );

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        FluoTube.debugln("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        FluoTube.debugln("Message appended");
    } else {
        FluoTube.debugln("Append failed");
    }
    file.close();
}

void renameFil(fs::FS &fs, const char * path1, const char * path2){
    FluoTube.debugln("Renaming file from " + String(path1) + " to " + String(path2));
    if (fs.rename(path1, path2)) {
        FluoTube.debugln("File renamed");
    } else {
        FluoTube.debugln("Rename failed");
    }
}

void deleteFil(fs::FS &fs, const char * path){
    FluoTube.debugln("Deleting file: " + String(path) );
    if(fs.remove(path)){
        FluoTube.debugln("File deleted");
    } else {
        FluoTube.debugln("Delete failed");
    }
}

void testFilIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        FluoTube.debugln( String(flen) + " bytes read for " + String(end) + " ms");
        file.close();
    } else {
        FluoTube.debugln("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        FluoTube.debugln("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    FluoTube.debugln( String(2048 * 512) + " bytes written for " + end + " ms");
    file.close();
}