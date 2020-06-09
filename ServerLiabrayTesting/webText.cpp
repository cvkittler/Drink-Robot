#include "webText.h"

  webText::webText(String Text){
    curText = Text;
  }

  void webText::show(WiFiClient &client){
    client.println("<p>" + curText + "</p>");
  }
  
  void webText::setText(String Text){
    curText = Text;
  }
