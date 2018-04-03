/*
  FluoTube.cpp - FluoTube library
  Copyright (c) 2017 Adriano Costanzo.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>
#include <EEPROM.h>

#include "FluoTube.h"


//#define DEBUG
#define VERSION "V01"
#define VIRTUALBAUD 57600

//#define DEBUG

void SerialParser();

SoftwareSerial *sserial = NULL;
Servo servos[8];
int servo_pins[] = {0, 0, 0, 0, 0, 0, 0, 0};
boolean connected = false;

SoftwareSerial Virtual(RX_VIRTUALSERIAL, TX_VIRTUALSERIAL); // (RX, TX)
//SoftwareSerial Virtual(2, 4); DBG

enum{
    SSID,
    PASSKEY,
    HOSTNAME,
    IP,
    CONNECTED,
    MAC
};

struct msg{
  String data;
  int semMsg = 1;
}msgAVR;

FluoTubeClass::FluoTubeClass()
{  
    //nothing to do 
}

void FluoTubeClass::Begin()  //check if FluoTube is ready
{
    Serial.begin(115200); //remember right baud use
    pinMode(esp32Interrupt, INPUT);
    pinMode(13, OUTPUT); // already set
  
    Virtual.begin(VIRTUALBAUD);
  
#ifdef DEBUG 
    Serial.println("644p is Alive");
#endif

}


void FluoTubeClass::Run()
{
    while(Virtual.available()) // fix buffer on EEPROM with last cmd
        SerialParser();
}

void FluoTubeClass::sendMsgToESP(String data){
  
  if(msgAVR.semMsg == 1){
    msgAVR.semMsg = 0;
    msgAVR.data = data;
    Serial.println("[Fluotube:sendMsgToESP]Invio mess ad esp:"+data+"\n");
    Virtual.println(msgAVR.data);
  }
}

FluoTubeClass FluoTube;


// Functions

void ContentHandleACK(String data){
  if(msgAVR.semMsg == 0){
      Serial.println(msgAVR.semMsg);
      Serial.println("ContentHandleACK -> "+data);
      msgAVR.semMsg=1;
  }
    
}
int Str2int (String Str_value)
{
  char buffer[10]; //max length is three units
  Str_value.toCharArray(buffer, 10);
  int int_value = atoi(buffer);
  return int_value;
}

void split(String results[], int len, String input, char spChar) {
  String temp = input;
  for (int i=0; i<len; i++) {
    int idx = temp.indexOf(spChar);
    results[i] = temp.substring(0,idx);
    temp = temp.substring(idx+1);
  }
}

void Version(){
  Virtual.println(VERSION);
}

uint8_t readCapacitivePin(String data) {
  int pinToMeasure = Str2int(data);
  // readCapacitivePin
  //  Input: Arduino pin number
  //  Output: A number, from 0 to 17 expressing
  //  how much capacitance is on the pin
  //  When you touch the pin, or whatever you have
  //  attached to it, the number will get higher
  //  http://playground.arduino.cc/Code/CapacitiveSensor
  //
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  //return cycles;
  Virtual.println(cycles);
}

void Tone(String data){
  int idx = data.indexOf('%');
  int len = Str2int(data.substring(0,idx));
  String data2 = data.substring(idx+1);
  int idx2 = data2.indexOf('%');
  int pin = Str2int(data2.substring(0,idx2));
  String data3 = data2.substring(idx2+1);
  String melody[len*2];
  split(melody,len*2,data3,'%');

  for (int thisNote = 0; thisNote < len; thisNote++) {
    int noteDuration = 1000/Str2int(melody[thisNote+len]);
    int note = Str2int(melody[thisNote]);
    tone(pin, note, noteDuration);
    int pause = noteDuration * 1.30;
    delay(pause);
    noTone(pin);
  }
} 

void ToneNo(String data){
  int pin = Str2int(data);
  noTone(pin);
} 

void DigitalHandler(int mode, String data){
      int pin = Str2int(data);
    if(mode<=0){ //read
        Virtual.println(digitalRead(pin));
    }else{
        if(pin <0){
            digitalWrite(-pin,LOW);
        }else{
            digitalWrite(pin,HIGH);
        }
        //Virtual.println('0');
    }
}

void AnalogHandler(int mode, String data)
{
  
     if(mode<=0){ //read
        int pin = Str2int(data);
        Virtual.println(analogRead(pin));
    }else{
        String sdata[2];
        split(sdata,2,data,'%');
        int pin = Str2int(sdata[0]);
        int pv = Str2int(sdata[1]);
        analogWrite(pin,pv);
    }
}

void ConfigurePinHandler(String data){
    int pin = Str2int(data);
    if(pin <=0){
        pinMode(-pin,INPUT);
    }else{
        pinMode(pin,OUTPUT);
    }
}

void shiftOutHandler(String data) {    
    String sdata[4];
    split(sdata, 4, data, '%');
    int dataPin = sdata[0].toInt();
    int clockPin = sdata[1].toInt();
    String bitOrderName = sdata[2];
    byte value = (byte)(sdata[3].toInt());
    if (bitOrderName == "MSBFIRST") {
       shiftOut(dataPin, clockPin, MSBFIRST, value);
    } else {
       shiftOut(dataPin, clockPin, LSBFIRST, value);
    }
}

void shiftInHandler(String data) {
    String sdata[3];
    split(sdata, 3, data, '%');
    int dataPin = sdata[0].toInt();
    int clockPin = sdata[1].toInt();
    String bitOrderName = sdata[2];
    int incoming;
    if (bitOrderName == "MSBFIRST") {
       incoming = (int)shiftIn(dataPin, clockPin, MSBFIRST);
    } else {
       incoming = (int)shiftIn(dataPin, clockPin, LSBFIRST);
    }
    Virtual.println(incoming);
}

void SS_set(String data){
  delete sserial;
  String sdata[3];
  split(sdata,3,data,'%');
  int rx_ = Str2int(sdata[0]);
  int tx_ = Str2int(sdata[1]);
  int baud_ = Str2int(sdata[2]);
  sserial = new SoftwareSerial(rx_, tx_);
  sserial->begin(baud_);
  Virtual.println("ss OK");
}

void SS_write(String data) {
 int len = data.length()+1;
 char buffer[len];
 data.toCharArray(buffer,len);
 Virtual.println("ss OK");
 sserial->write(buffer); 
}
void SS_read(String data) {
 char c = sserial->read(); 
 Virtual.println(c);
}

void pulseInHandler(String data){
    int pin = Str2int(data);
    long duration;
    if(pin <=0){
          pinMode(-pin, INPUT);
          duration = pulseIn(-pin, LOW);      
    }else{
          pinMode(pin, INPUT);
          duration = pulseIn(pin, HIGH);      
    }
    Virtual.println(duration);
}

void pulseInSHandler(String data){
    int pin = Str2int(data);
    long duration;
    if(pin <=0){
          pinMode(-pin, OUTPUT);
          digitalWrite(-pin, HIGH);
          delayMicroseconds(2);
          digitalWrite(-pin, LOW);
          delayMicroseconds(5);
          digitalWrite(-pin, HIGH);
          pinMode(-pin, INPUT);
          duration = pulseIn(-pin, LOW);      
    }else{
          pinMode(pin, OUTPUT);
          digitalWrite(pin, LOW);
          delayMicroseconds(2);
          digitalWrite(pin, HIGH);
          delayMicroseconds(5);
          digitalWrite(pin, LOW);
          pinMode(pin, INPUT);
          duration = pulseIn(pin, HIGH);      
    }
    Virtual.println(duration);
}

void SV_add(String data) {
    String sdata[3];
    split(sdata,3,data,'%');
    int pin = Str2int(sdata[0]);
    int min = Str2int(sdata[1]);
    int max = Str2int(sdata[2]);
    int pos = -1;
    for (int i = 0; i<8;i++) {
        if (servo_pins[i] == pin) { //reset in place
            servos[pos].detach();
            servos[pos].attach(pin, min, max);
            servo_pins[pos] = pin;
            Virtual.println(pos);
            return;
            }
        }
    for (int i = 0; i<8;i++) {
        if (servo_pins[i] == 0) {pos = i;break;} // find spot in servo array
        }
    if (pos == -1) {;} //no array position available!
    else {
        servos[pos].attach(pin, min, max);
        servo_pins[pos] = pin;
        Virtual.println(pos);
        }
}

void SV_remove(String data) {
    int pos = Str2int(data);
    servos[pos].detach();
    servo_pins[pos] = 0;
}

void SV_read(String data) {
    int pos = Str2int(data);
    int angle;
    angle = servos[pos].read();
    Virtual.println(angle);
}

void SV_write(String data) {
    String sdata[2];
    split(sdata,2,data,'%');
    int pos = Str2int(sdata[0]);
    int angle = Str2int(sdata[1]);
    servos[pos].write(angle);
}

void SV_write_ms(String data) {
    String sdata[2];
    split(sdata,2,data,'%');
    int pos = Str2int(sdata[0]);
    int uS = Str2int(sdata[1]);
    servos[pos].writeMicroseconds(uS);
}

void sizeEEPROM() {
    Virtual.println(E2END + 1);
}

void EEPROMHandler(int mode, String data) {
    String sdata[2];
    split(sdata, 2, data, '%');
    if (mode == 0) {  
        EEPROM.write(Str2int(sdata[0]), Str2int(sdata[1]));  
    } else {
        Virtual.println(EEPROM.read(Str2int(sdata[0])));
    }
}


void ManualMode()
{
#ifdef DEBUG
    Serial.println("ask mode, auto or manual");
    Serial.println(WiFi_setting.stored);
#endif

    if (WiFi_setting.stored == 2)
    {
        Virtual.println(WiFi_setting.stored);
        WiFi_setting.stored = 1;
        return;
    }
    // mando una volta 2 cosi che ESP32 sa che e' arrivata un nuovo config
    // ma lo metto a 1 che significa sono in MANUAL MODE
    // se fosse 0 significa non sono piu' in MANUAL MODE

    // send manual configuration
    Virtual.println(WiFi_setting.stored); // 1 -> Manual ON / 2 -> Manual NewConf/AVR rst / 0 -> Manual OFF
}

void ContentHandle(String data)
{
#ifdef DEBUG
    Serial.println(data);
#endif

    Content.data = data;
    Content.ready = 1; 
}

void SerialSend(String data)
{
    String tmp = "ESP: " + data;
    Serial.print(tmp);
}

void WiFi(int args, String data)
{

    if (args == MAC)
    {
        WiFi_setting.mac = data;
        return;
    } 

    if (WiFi_setting.stored == 0)
    {
        Virtual.println("data not ready");
        return;  
    }

// lavoro in ACK
    if (args == SSID)
    {
        Virtual.println(WiFi_setting.ssid);
        #ifdef DEBUG
        Serial.println(WiFi_setting.ssid);
        #endif
    }
        
    if (args == PASSKEY)
    {
        Virtual.println(WiFi_setting.passkey);
        #ifdef DEBUG
        Serial.println(WiFi_setting.passkey);
        #endif
    }

    if (args == HOSTNAME)
    {
        Virtual.println(WiFi_setting.hostname);
        #ifdef DEBUG
        Serial.println(WiFi_setting.hostname);
        #endif
    }

// prendo i valori che ricevo
    if (args == CONNECTED)
    {
        if (data == "0.0.0.0")
        {
            #ifdef DEBUG
            Serial.println("NO IP");
            #endif
            
            WiFi_setting.connected = 0;
            return;
        }

        WiFi_setting.ipv4 = data;
        WiFi_setting.connected = 1;

        #ifdef DEBUG
        Serial.println("NO IP");
        #endif
    }
}




void SerialParser(void) {
  char readChar[64] = "";
  
  Virtual.readBytesUntil(33,readChar,64);
  String read_ = String(readChar);
  
#ifdef DEBUG
  Serial.println(readChar);
#endif
  
  int idx1 = read_.indexOf('%');
  int idx2 = read_.indexOf('$');
  // separate command from associated data
  String cmd = read_.substring(1,idx1);
  String data = read_.substring(idx1+1,idx2);
  
  // determine command sent
  if (cmd == "dw") {
      DigitalHandler(1, data);   
  }
  else if (cmd == "dr") {
      DigitalHandler(0, data);   
  }  
  else if (cmd == "aw") {
      AnalogHandler(1, data);   
  }    
  else if (cmd == "ar") {
      AnalogHandler(0, data);   
  }      
  else if (cmd == "pm") {
      ConfigurePinHandler(data);   
  }    
  else if (cmd == "ps") {
      pulseInSHandler(data);   
  }    
  else if (cmd == "pi") {
      pulseInHandler(data);   
  }        
  else if (cmd == "ss") {
      SS_set(data);   
  }
  else if (cmd == "sw") {
      SS_write(data);   
  }
  else if (cmd == "sr") {
      SS_read(data);   
  }    
  else if (cmd == "sva") {
      SV_add(data);   
  }      
  else if (cmd == "svr") {
      SV_read(data);   
  }   
 else if (cmd == "svw") {
      SV_write(data);   
  }    
 else if (cmd == "svwm") {
      SV_write_ms(data);   
  }      
  else if (cmd == "svd") {
      SV_remove(data);   
  } 
  else if (cmd == "ver") {
      Version();   
  }
  else if (cmd == "mode") {
      ManualMode();   
  }
  else if (cmd == "ssid") {
      WiFi(SSID, data);   
  }
  else if (cmd == "key") {
      WiFi(PASSKEY, data);   
  }
  else if (cmd == "host") {
      WiFi(HOSTNAME, data);   
  }
  else if (cmd == "ip") {
      WiFi(IP, data);   
  }
  else if (cmd == "mac") {
      WiFi(MAC, data);   
  }
  else if (cmd == "conn") {
      WiFi(CONNECTED, data);   
  }
  else if (cmd == "string") {
      ContentHandle(data);   
  }
  else if (cmd == "srs") {
      SerialSend(data);   
  }
  else if (cmd == "to") {
      Tone(data);   
  } 
  else if (cmd == "nto") {
      ToneNo(data);   
  }  
  else if (cmd == "cap") {
      readCapacitivePin(data);   
  }
  else if (cmd == "so") {
      shiftOutHandler(data);
  }
  else if (cmd == "si") {
      shiftInHandler(data);
  }
  else if (cmd == "eewr") {
      EEPROMHandler(0, data);   
  } 
  else if (cmd == "eer") {
      EEPROMHandler(1, data);   
  }  
  else if (cmd == "sz") {  
      sizeEEPROM();
  }
  else if (cmd == "ackToAVR" ) {
      ContentHandleACK(data);
  }
}
