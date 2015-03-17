#include "Sonar.h"

Sonar::Sonar(int TX, int RX, int stall_ADDR, int overspeed_ADDR, int OSD_RSSI_LOW_ADDR, int wait):
    mySerial(TX,RX,true),
    xPos(EEPROM.read(stall_ADDR)),
    yPos(EEPROM.read(overspeed_ADDR)),
    offset(EEPROM.read(OSD_RSSI_LOW_ADDR)),
    maxWait(wait >= 0 ? wait : 2000),
    val(0)
{
    mySerial.begin(9600);
}

void Sonar::loop(unsigned long millis)
{
    //message from the sensor is 5 bytes, so we wait for at least 5 bytes
    if( mySerial.available() >= 5)
    { 
	while(mySerial.available())
	    getData(millis);
    }

    //check if we get a time-out
    if(millis - lastRead > maxWait)
	val = -999+offset; //we display "-999" by adding offset
}

void Sonar::getData(unsigned long millis)
{
    //First byte is 'R', then three ascii-numbers (distance in cm), and a ending 13
    if(mySerial.read() == 'R')
    {
	char tmp[4] = "000";
	tmp[0] = mySerial.read();
	tmp[1] = mySerial.read();
	tmp[2] = mySerial.read();
	if(mySerial.read() == 13)
	{
	    val = atoi(tmp);
	    lastRead = millis;
	}
    }
    
}

int Sonar::getDistance() const
{
    return val-offset;
}

int Sonar::getXpos() const
{
    return xPos;
}

int Sonar::getYpos() const
{
    return yPos;
}
