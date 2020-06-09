#ifndef SERVERHTML_H
#define SERVERHTML_H

#include <WiFi.h>

#include "webButton.h"
#include "webText.h"

class htmlServer{
  public:
    htmlServer(int port);
    void init(); //run in setup()
    void run(); //run in loop()

    //must be run before init()
    void addButton(int pin, String Name);
    void addButton(int pin);

    //returns the button state
    bool getButtonState(int button);
    
    //Text
    void addText(int tag, String Text);

    
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
    webButton *buttons[51];
    webText *text[50];
};
     

#endif
