#include <WiFi.h>
#include "pageSwaping.h"
const char* ssid     = "Kittler House";
const char* password = "69kittler";



void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    // We start by connecting to a WiFi network

    Serial.println("TEST");
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //ledcSetup(0,1E5,12);
    //ledcAttachPin(2,0);
    
    server.begin();

}

int value = 0;

void loop(){
  static int state = 0;
  static bool flag = false;
  handleClientResponse(state);
  Serial.print(state);
  Serial.print('\t');
  Serial.print(flag);
  Serial.print('\n');
  
  switch(state){
    case 0:
    //ledcWriteTone(0,0);//no tone
    digitalWrite(2, LOW);
    flag = false;
    break;
    case 1:
    if(!flag){
    digitalWrite(2, HIGH);
    //ledcWriteTone(0,800); //play tone
    flag = true;
    }
    break;
  }
}
