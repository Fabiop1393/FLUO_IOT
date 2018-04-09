/*
   EEPROM Write

   Stores random values into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.
*/

#include "EEPROM.h"
#include <Fluotube.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
#define EEPROM_SIZE 64
void setup()
{

  FluoTube.setup();

  FluoTube.debugln("start... ");

  if (!EEPROM.begin(EEPROM_SIZE))
  {
    FluoTube.debugln("failed to initialise EEPROM"); 
    delay(1000000); //ESP die
  }

  FluoTube.debugln(" bytes read from Flash. Values are: ");

  for (int i = 0; i < EEPROM_SIZE; i++)
  {
    FluoTube.debug( String(byte(EEPROM.read(i))) ); 
    FluoTube.debug(" ");
  }

  FluoTube.debugln("");
  FluoTube.debugln("writing random n in memory");
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
  // int val = analogRead(10) / 4;
  int val = byte(random(10020));
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);

  FluoTube.debug( String(val) ); 
  FluoTube.debug(" ");

  // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 0 when we hit 512.
  // save all changes to the flash.
  addr = addr + 1;
  if (addr == EEPROM_SIZE)
  {
    FluoTube.debugln("");
    addr = 0;
    EEPROM.commit();

    FluoTube.debug( String(EEPROM_SIZE) );
    FluoTube.debugln(" bytes written on Flash. Values are: ");

    for (int i = 0; i < EEPROM_SIZE; i++)
    {
      FluoTube.debug( String(byte(EEPROM.read(i))) ); 
      FluoTube.debug(" ");
    }

    FluoTube.debugln(""); 
    FluoTube.debugln("----------------------------------");
  }

  delay(100);
}
