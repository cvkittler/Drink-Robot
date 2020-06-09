#include "webDropDown.h"

webDropDown::webDropDown(String Title){
  titleName = Title;
  for(int i = 0; i < maxDropDownOptions-1; i++){
    options[i] = "";
  }
}

 void webDropDown::showDropDown(WiFiClient &client){
  char chooseMSG[80];
  char optionMSG[80];
  char titleChar[80];
  strcpy(titleChar,titleName.c_str());
  sprintf(chooseMSG, "<div class=\"%s\">" ,titleName);
  client.println(chooseMSG);
  client.println("<button class=\"dropbtn\">Dropdown</button>");
  client.println("<div class=\"dropdown-content\">");
  for(int i = 0; i < maxDropDownOptions-1;i++){
    if(options[i] != ""){
      char optionChar[80];
      strcpy(optionChar,options[i].c_str());
      sprintf(optionMSG,"<a href=\"%s\">%s</a>",optionChar,optionChar);
      client.println(optionMSG);
    }
  }
  client.println("</div>");
  client.println("</div>");
 }

void webDropDown::addOption(String option){
  for(int i = 0; i < maxDropDownOptions-1;i++){
    if(options[i] == ""){
      options[i] = option;
      return;
    }
  }
}
