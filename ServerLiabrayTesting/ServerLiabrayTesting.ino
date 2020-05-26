#include "serverHTML.h"

htmlServer server(80);

void setup() {
  Serial.begin(115200);
  server.addButton(2,"TEST");
  server.addButton(3);
  server.addButton(4);
  server.addButton(5);
  server.init();
}

void loop() {
  server.run();
}
