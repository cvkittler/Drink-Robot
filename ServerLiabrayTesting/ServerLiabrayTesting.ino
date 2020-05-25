#include "serverHTML.h"

htmlServer server(80);

void setup() {
  Serial.begin(115200);
  server.addButton(2);
  server.init();
}

void loop() {
  server.run();
}
