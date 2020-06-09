#ifndef WEBDROPDOWN_H
#define WEBDROPDOWN_H

#include <WiFi.h>

const int maxDropDownOptions = 10;

class webDropDown{
  public:
  webDropDown(String Title);
  void showDropDown(WiFiClient &client);
  
  void addOption(String option);
  
  private:
  String titleName;
  
  String options[maxDropDownOptions];
};
#endif
