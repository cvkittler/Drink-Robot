#ifndef __CHECKIR_H
#define __CHECKIR_H

#include "RemoteConstants.h"
#include "RemotDecoder.h"
//function declaration
void processRemoteCommand(uint8_t command);
void processRemoteEvents();

//variables
const uint16_t messageTimeoutMs = 115;
bool messageActive = false;
uint16_t lastMessageTimeMs = 0;
bool pushedButton = false;

 bool checkIR(){
    decoder.service();
    if (decoder.criticalTime()){
    }
    else{
       processRemoteEvents();
    }
   return pushedButton;
  }
  
void processRemoteMessage(const uint8_t * message)
{
  // Print the raw message on the first line of the LCD, in hex.
  // The first two bytes are usually an address, and the third
  // byte is usually a command.  The last byte is supposed to be
  // the bitwise inverse of the third byte, and if that is the
  // case, then we don't print it.
  lcd.clear();
  char buffer[9];
  if (message[2] + message[3] == 0xFF)
  {
    sprintf(buffer, "%02X%02X %02X ",
      message[0], message[1], message[2]);
  }
  else
  {
    sprintf(buffer, "%02X%02X%02X%02X",
      message[0], message[1], message[2], message[3]);
  }
  lcd.print(buffer);

  // Go to the next line of the LCD.
  lcd.gotoXY(0, 1);

  // Make sure the address matches what we expect.
  if (message[0] != remoteAddressByte0 ||
    message[1] != remoteAddressByte1)
  {
    lcd.print(F("bad addr"));
    return;
  }

  // Make sure that the last byte is the logical inverse of the
  // command byte.
  if (message[2] + message[3] != 0xFF)
  {
    lcd.print(F("bad cmd"));
    return;
  }
  processRemoteCommand(message[2]);
}

void processRemoteCommand(uint8_t command)
{
  if(command == remoteUp){
    driveForward();
  }else if(command == remoteDown){
    driveBackward();
  }else if(command == remoteLeft){
    driveTurnLeft();
  }else if(command == remoteRight){
    driveTurnRight();
  }else if(command == remoteOK){
    
  }else{
    driveStop();
  }
}
void processRemoteEvents()
{
  if (decoder.getAndResetMessageFlag())
  {
    // The remote decoder received a new message, so record what
    // time it was received and process it.
    lastMessageTimeMs = millis();
    messageActive = true;
    processRemoteMessage(decoder.getMessage());
  }

  if (decoder.getAndResetRepeatFlag())
  {
    // The remote decoder receiver a "repeat" command, which is
    // sent about every 109 ms while the button is being held
    // down.  It contains no data.  We record what time the
    // repeat command was received so we can know that the
    // current message is still active.
    lastMessageTimeMs = millis();
  }
}

#endif
