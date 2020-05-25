#include <SPI.h>
#include <Ethernet.h>

#define MAX 2 //2 is the number of outputs
const int pin[MAX] = {5, 6}; //these are the pins that control the dual channel relay
boolean pin_status[MAX] = {0, 0}; //this is a control array
char *title[MAX] = {"Lamp", "Lights"}; //these are my web page things
EthernetServer server(80);

void setup() {
  byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
  byte ip[] = { 192, 168, 0, 55 };  //change it base on your DHCP from step 2
  byte gateway[] = { 192, 168, 0, 1 }; //change it to your DHCP from step 2
  byte subnet[] = { 255, 255, 255, 0 };

  Serial.begin(9600);
  for (int i = 0; i < MAX; i++) { //index!!!
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i], HIGH);
  }
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop() {
  String readString = "";
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n') {
          Serial.print("\n");
 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();

          for (int i = 0; i < MAX; i++) { //index!!!
            if (readString.indexOf("?" + String(i) + "_turn_on") > 0) { //Turn on pin n
              digitalWrite(pin[i], LOW);
              Serial.println("Pin " + String(i) + " has been turned on");
              pin_status[i] = true;
            } else if (readString.indexOf("?" + String(i) + "_turn_off") > 0) { //Turn off pin n
              digitalWrite(pin[i], HIGH);
              Serial.println("Pin " + String(i) + " has been turned off");
              pin_status[i] = false;
            }
          }

          //client.println("<meta http-equiv='cache-control' content='no-cache' />");
          client.println("<meta name='viewport' content='width=720, initial-scale=1' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://genos.eco.br/wp-content/marco/autohome_v6.css' />");
          client.println("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>");
          client.println("<script type='text/javascript' src='http://genos.eco.br/wp-content/marco/autohome_v6.js'></script>");

          client.println("<div class='div'></div>");

          for (int i = 0; i < MAX; i++) { //index!!!
            client.println("<div class='div'>");
              client.print("<div class='text'>"); client.print(title[i]); client.println("</div>");
              client.print("<label class='switch' onClick='Relay("); client.print(i); client.println(")'>");
                client.print("<input id='checkbox_"); client.print(i); client.println("' type='checkbox'>");
                client.println("<div class='slider round'></div>");
              client.println("</label>");
            client.println("</div>");
          }

          for (int i = 0; i < MAX; i++) { //index!!!
            client.print("<div id='status_");
            client.print(i);
            client.print("'>");
            client.print(pin_status[i]);
            client.println("</div>");
          }
          
          delay(1);
          client.print("<script>onload(");
          client.print(MAX);
          client.println(")</script>");
          client.stop();

          /*Serial.println(readString);
          for (int i = 0; i < MAX; i++) { //index!!!
            Serial.println(pin_status[i]);
          }
          Serial.println("");*/

          readString = "";
        }
      }
    }
  }
}
