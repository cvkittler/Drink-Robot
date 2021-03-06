#include "serverHTML.h"
#include "webButton.h"
#include "serverConfig.h"

#include <WiFi.h>

htmlServer::htmlServer(int port){
  port = port;
  WiFiServer holder(port);
  server = holder;
  for (int i = 0; i < 50; i++){
    buttonPins[i] = -1;
    buttons[i] = NULL;
  }
  for (int i = 0; i < 50; i++){
    text[i] = NULL;
  }
}

void htmlServer::init(){
  //initilize html buttons
  for (int j = 0; j < 50; j++){
    if (buttonPins[j] != -1){
      Serial.println("Made Button");
      buttons[buttonPins[j]] = new webButton(buttonPins[j],buttonNames[j]);
    }
  }
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void htmlServer::run(){
  WiFiClient client = server.available();   // Listen for incoming clients

  
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    
    Serial.println("New Client.");          // print a message out in the serial port
    currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //Check button
            for (int i = 0; i < 50; i++){
              if (buttons[i] != NULL){
                buttons[i]->checkChange(header);
              }
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println("</style></head>");
            

            client.println("<body><h1>" + pageTitle + "</h1>");

            //show text
//            for (int i = 0; i < 50; i++){
//              if (buttons[i] != NULL){
//                text[i]->showText(client);
//                Serial.println("Showing Text");
//              }
//            }
            static webText testText("TEST");
            testText.show(client);
            //show buttons
            for (int i = 0; i < 50; i++){
              if (buttons[i] != NULL){
                buttons[i]->show(client);
                Serial.println("Showing Button");
              }
            }
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
}
}

void htmlServer::addButton(int pin, String Name){
  for (int i = 0; i < 50; i++){
    if (buttonPins[i] == -1){
      buttonPins[i] = pin;
      buttonNames[i] = Name;
      return;
    }
  }
}

void htmlServer::addButton(int pin){
  for (int i = 0; i < 50; i++){
    if (buttonPins[i] == -1){
      buttonPins[i] = pin;
      buttonNames[i] = "";
      return;
    }
  }
}

bool htmlServer::getButtonState(int button){
  if(buttons[button] == NULL)
    return NULL;
  return buttons[button]->pinState;
}

void htmlServer::addText(int tag, String Text){
      text[tag] = new webText(Text);
}
