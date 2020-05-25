#include "webButton.h"

webButton::webButton(int pin){
  pinNumber = pin;
  pinState = false;
  pinMode(pin, OUTPUT);
}

void webButton::checkChange(String &header){
  char onMSG[20];
  char offMSG[20];
  sprintf(onMSG, "GET /%d/on", pinNumber);
  sprintf(offMSG, "GET /%d/off", pinNumber);
  if (header.indexOf(onMSG) >= 0) {
              pinState = true;
              digitalWrite(pinNumber, HIGH);
  } else if (header.indexOf(offMSG) >= 0) {
              pinState = false;
              digitalWrite(pinNumber, LOW);
  }
  Serial.print("Pin:");
  Serial.print('\t');
  Serial.print(pinNumber);
  Serial.print('\t');
  Serial.print("State");
  Serial.print('\t');
  Serial.print(pinState);
  Serial.print('\n');
}

void webButton::showButton(WiFiClient &client){
  // Display current state, and ON/OFF buttons for Pin  
  char buttonMSG[50];
  char onHTMl[255]; char offHTMl[255];
  sprintf(buttonMSG, "<p>Pin %d </p>", pinNumber);
  sprintf(onHTMl, "<p><a href=\"/%d/on\"><button class=\"button\">ON</button></a></p>", pinNumber);
  sprintf(offHTMl, "<p><a href=\"/%d/off\"><button class=\"button button2\">OFF</button></a></p>", pinNumber);
  client.println(buttonMSG);
  // If the pinState is off, it displays the ON button       
  if (!pinState) {
    client.println(onHTMl);
  } else {
    client.println(offHTMl);
  } 
}
            
void buttonStyle(WiFiClient &client){
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
}
