//Simple sketch to access the internal hall effect detector on the esp32.
//values can be quite low. 
//Brian Degger / @sctv  
#include <Fluotube.h>

int val = 0;

void setup() {

  FluoTube.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  val = hallRead();
  // print the results to the serial monitor:
  //FluoTube.debug("sensor = ");
  FluoTube.debugln(String(val);//to graph 
}
