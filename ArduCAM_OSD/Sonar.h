#pragma once

#include <SoftwareSerial.h>
#include <EEPROM.h>
/*
  Simple class for the maxSensors, sonars. 
  Run "loop" as often as possible.
 */
class Sonar
{
  public:
    Sonar(int, int, int, int, int);
    void loop();
    int getDistance() const;
    int getXpos() const;
    int getYpos() const;
  private:
    SoftwareSerial mySerial;
    int xPos, yPos, offset, val;
};
