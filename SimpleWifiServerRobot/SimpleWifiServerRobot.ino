#include <Zumo32U4Motors.h>
#include <Zumo32U4Encoders.h>
#include "configPID.h"

Zumo32U4Motors motors;
Zumo32U4Encoders encoders;

void CalcPID(); //calculates the pid efford values
void setupPID(); //sets up timer 4 for encoders
const uint8_t signalPin = 7; //Pin connected to pin 2 on the ESP32

void setup() {
  
  Serial.begin(115200);
  
  pinMode(signalPin, INPUT);
}

void loop() {
  CalcPID();
}

void CalcPID(){
  if(readyToPID) //timer flag set
  {
    //clear the timer flag
    readyToPID = 0;

    //for tracking previous counts
    static int16_t prevLeft = 0;
    static int16_t prevRight = 0;

    //error sum
    static int16_t sumLeft = 0;
    static int16_t sumRight = 0;

    //dirivitave 
    static int16_t prevErrorR = 0;
    static int16_t prevErrorL = 0;
    static float errorChangeR = 0;
    static float errorChangeL = 0;
    
    /*
     * Do PID stuffs here. Note that we turn off interupts while we read countsLeft/Right
     * so that it won't get accidentally updated (in the ISR) while we're reading it.
     */
    noInterrupts();
    int16_t speedLeft = countsLeft - prevLeft;
    int16_t speedRight = countsRight - prevRight;

    prevLeft = countsLeft;
    prevRight = countsRight;
    interrupts();

    int16_t errorLeft = targetLeft - speedLeft;
    sumLeft += errorLeft;
    

    int16_t errorRight = targetRight - speedRight;
    sumRight += errorRight;
    
    float effortLeft = Kp * errorLeft + Ki * sumLeft;
    float effortRight = Kp * errorRight + Ki * sumRight;


    prevErrorR = errorRight;
    prevErrorL = errorLeft;
    
    motors.setSpeeds(effortLeft, effortRight);
  }
}

void setupPID(){
  noInterrupts(); //disable interupts while we mess with the Timer4 registers 
  //sets up timer 4
  TCCR4A = 0x00; //disable some functionality -- no need to worry about this
  TCCR4B = 0x0C; //sets the prescaler -- look in the handout for values
  TCCR4C = 0x04; //toggles pin 6 at one-half the timer frequency
  TCCR4D = 0x00; //normal mode
  OCR4C = 132;
  TIMSK4 = 0x04; //enable overflow interrupt
  interrupts(); //re-enable interrupts
}


ISR(TIMER4_OVF_vect){
  //Capture a "snapshot" of the encoder counts for later processing
  countsLeft = encoders.getCountsLeft();
  countsRight = encoders.getCountsRight();
  readyToPID = 1;
}
