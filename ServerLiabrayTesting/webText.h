#ifndef WEBTEXT_H
#define WEBTEXT_H

#include <WiFi.h>
#include "webItem.h"

class webText: public webItem{
  public:
  
  webText(String Text);
  void show(WiFiClient &client);
  void setText(String Text);
  
  private:
  
  String curText = "NO TEXT:ERROR";
};

#endif
