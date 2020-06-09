#include "serverHTML.h"

htmlServer server(80);

void setup() {
  Serial.begin(115200);
  server.addText(0,"HERE");
  server.addButton(2, "Spin");
  server.addButton(3);
  server.init();
}

void loop() {
  server.run();
  
}
