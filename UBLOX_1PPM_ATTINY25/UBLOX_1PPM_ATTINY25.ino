/* 
 
 U-Blox NEO-M6 GPS Initial config for 1 PPM.
 
 Connects a Attiny25 to a NEO-M6 GPS TX via the
 Send Only Software Serial Library
 
 (D)4 Pin 3 = TX
 
 This example code is in the public domain.
 
 Additional Code by J Coxon http://ukhas.org.uk/guides:falcom_fsa03
 
 Adapted by Rens PA3AXA http://github.com/pa3axa for use with  U-Blox NEO-M6
 and Attiny25 for a 1 PPM puls to sync transmit sequence for PI4 beacon.

 To fit this into an ATtiny25 i used the SendOnlySoftwareSerial.h stripped
 library by http://gammon.com.au/Arduino/SendOnlySoftwareSerial.zip

 */

#include <avr/sleep.h>

#include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial GPS(4); // Attiny pin 3 for TX


void setup()
{
  GPS.begin(9600); 

  /* Wait 10 sec for GPS to wakeup */
  
  delay(10000);

  /* Stop al other messages as we are not reading */

  /* THIS COMMAND SETS TIMEPULSE to 1 PPM */
  
  uint8_t setTp[] = {
    0xB5, 0x62, 0x06, 0x07, 0x14, 0x00, 0x00, 0x87, 0x93, 0x03, 0xA0, 0x86, 0x01,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x98, 0xFB };
  
  
  sendUBX(setTp, sizeof(setTp)/sizeof(uint8_t));
 
}
 
 /* Send a byte array of UBX protocol to the GPS */
 
void sendUBX(uint8_t *MSG, uint8_t len) {
  for(int i=0; i<len; i++) {
    GPS.write(MSG[i]);
  }
  GPS.println();
}


/* When done we goto sleep */

void loop() {

  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_cpu(); 

} /* Main Loop end */   
 
 
