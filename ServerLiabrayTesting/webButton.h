#ifndef WEBBUTTON_H
#define WEBBUTTON_H

#include <WiFi.h>

class webButton{
  private:
    uint8_t pinNumber;
  
  public:
    bool pinState;
    
    webButton(int pin);
    void checkChange(String &header);
    void showButton(WiFiClient &client);
    
};

void buttonStyle(WiFiClient &client);

#endif
