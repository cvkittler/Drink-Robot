
#include <Zumo32U4Motors.h>
Zumo32U4Motors motors;

const uint8_t signalPin = 7; //Pin used for the SharpIR
void setup() {
  
  Serial.begin(115200);
  pinMode(signalPin, INPUT);

}

void loop() {
  static int effort = 0;
   int flag = analogRead(signalPin);
   Serial.println(flag);
   if(flag < 500){
    effort = 0;
   }
   else{
    effort = 400;
   }
   motors.setSpeeds(effort, -effort);
}
