#ifndef SERVERHTML_H
#define SERVERHTML_H

#include <WiFi.h>
#include "webButton.h"

class htmlServer{
  public:
    htmlServer(int port);
    void init();
    void addButton(int pin, String Name);
    void addButton(int pin);
    void run();
    
  private:
    String header;
    int port;
    WiFiServer server;
    WiFiClient client;
    unsigned long currentTime;
    unsigned long previousTime;
    String currentLine;
    char c;
    int buttonPins[50];
    String buttonNames[50];
    webButton *buttons[50];
};


#endif
