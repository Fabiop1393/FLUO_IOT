#ifndef	protocol_h
#define	protocol_h

#include <Arduino.h>

String cmdBuild(String cmd, String args);

// Arduino classic WRAP function 

void VirtualdigitalWrite(int pin, int val); //led blink

int VirtualdigitalRead(int pin); //button

int VirtualanalogRead(int pin); //potenziomerto

int VirtualanalogWrite(int pin, int val); // led fade

float VirtualpulseIn_set(int pin, int val, int trials); // no

float VirtualpulseIn(int pin, int val); // no

void VirtualpinMode(int pin, int val); 

//Servo
int VirtualservoRead(int pin);

void VirtualservoWriteMicroseconds(int pin, int uS);

void VirtualservoWrite(int pin, int angle);

void VirtualservoDetach(int pin);

int VirtualservoAttach(int pin, int min=544, int max=2400);

//Serial
void VirtualserialSend(String data); //Serial Debug for ESP

// WIFI and REST

int VirtualUseCase(); // enable MANUAL mode

String VirtualHOSTNAME(); // hostname

String VirtualPASSKEY(); // passkey

String VirtualSSID(); // ssid

String VirtualRESTAPI(); // enable REST API redirect

int VirtualStringSend(String data); // REST string

void VirtualConnection(String);

String VirtualReadAvrMsg(String data); //msg di push da avr

int VirtualMacADDR(String tmp);

#endif
