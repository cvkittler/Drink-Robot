#ifndef WEBBUTTON_H
#define WEBBUTTON_H

#include <WiFi.h>

class webButton{
  private:
    uint8_t pinNumber;
    String Name;
  public:
    bool pinState;
    webButton(int pin);
    webButton(int pin, String Name);
    void checkChange(String &header);
    void show(WiFiClient &client);
    
};

void buttonStyle(WiFiClient &client);

#endif
