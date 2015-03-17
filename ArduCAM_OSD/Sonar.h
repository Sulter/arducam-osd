#pragma once

#include <SoftwareSerial.h>
#include <EEPROM.h>
/*
  Simple class for the maxSonar(r), sonar-sensor. 
 */
class Sonar
{
public:
    /*
      TX - doesn't really matter, but I'm not sure if this pin can be used(!?)
      RX - where the sonar will be connected (arduino port)
      stall_ADDR - eeprom address of x pos
      overspeed_ADDR - eeprom address of y pos
      OSD_RSSI_LOW_ADDR - eeprom address of offset
      maxWait - how long we wait before assuming sonar is dead(msec)
    */
    Sonar(int, int, int, int, int, int wait= 2000);
    
    /*
      run as often as possible, should get miliseconds since the start as parameter (arduino - millis()).
    */
    void loop(unsigned long);

    //returns distance (or -999 if connection lost)
    int getDistance() const;
    int getXpos() const;
    int getYpos() const;
    
private:
    SoftwareSerial mySerial;
    void getData(unsigned long);
    int xPos, yPos, offset, val;
    int maxWait;
    unsigned long lastRead;
};
