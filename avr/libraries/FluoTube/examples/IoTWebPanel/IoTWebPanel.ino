#include <FluoTube.h>

void setup() {
  FluoTube.Begin();
}

void loop() {
  FluoTube.Run();

  delay(1000);
}
