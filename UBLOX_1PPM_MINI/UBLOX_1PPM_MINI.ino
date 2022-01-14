/*
 * 
 U-Blox NEO-M6 GPS Initial config for 1 PPM.
 
 Connects a Attiny85 GPS RX/TX via the
 Software Serial Library
 
 (D)3 Pin 2 = RX
 (D)4 Pin 3 = TX
 
 This example code is in the public domain.
 
 Additional Code by J Coxon http://ukhas.org.uk/guides:falcom_fsa03
 
 Adapted by Rens PA3AXA http://github.com/pa3axa for use with  U-Blox NEO-M6
 and Attiny85 for a 1 PPM puls to sync transmit sequence for PI4 beacon. 

 */
 
#include <SoftwareSerial.h>

SoftwareSerial GPS(3, 4); // Attiny pin 2 & 3 for RX, TX
 
void setup()
{
  GPS.begin(9600); 

  /* Wait 5 sec for GPS to wakeup */
  
  delay(5000);

  /* Stop al other messages as we are not reading */

  /*
  Serial.print("$PUBX,40,GLL,0,0,0,0*5C\r\n");
  Serial.print("$PUBX,40,ZDA,0,0,0,0*44\r\n");
  Serial.print("$PUBX,40,VTG,0,0,0,0*5E\r\n");
  Serial.print("$PUBX,40,GSV,0,0,0,0*59\r\n");
  Serial.print("$PUBX,40,GSA,0,0,0,0*4E\r\n");
  Serial.print("$PUBX,40,RMC,0,0,0,0*47\r\n");
  */
 
  /* THIS COMMAND SETS TIMEPULSE to 1 PPM */
  
  uint8_t setTp[] = {
    0xB5, 0x62, 0x06, 0x07, 0x14, 0x00, 0x00, 0x87, 0x93, 0x03, 0xA0, 0x86, 0x01,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x98, 0xFB };
  
  
  sendUBX(setTp, sizeof(setTp)/sizeof(uint8_t));
 
}
 
void loop(){
  
  if(GPS.available())
    {
      /* THIS IS THE MAIN LOOP JUST READS IN FROM THE GPS SERIAL AND DUMP DATA
       We are Not using any NMEA data. */
       
      GPS.read(); 
    } 
} /* Main Loop end */   
 
 
 /* Send a byte array of UBX protocol to the GPS */
 
void sendUBX(uint8_t *MSG, uint8_t len) {
  for(int i=0; i<len; i++) {
    GPS.write(MSG[i]);
  }
  GPS.println();
}
