#include "Sonar.h"

Sonar::Sonar(int TX, int RX, int stall_ADDR, int overspeed_ADDR, int OSD_RSSI_LOW_ADDR):
    mySerial(TX,RX,true),
    xPos(EEPROM.read(stall_ADDR)),
    yPos(EEPROM.read(overspeed_ADDR)),
    offset(EEPROM.read(OSD_RSSI_LOW_ADDR)),
    val(0)
{
    mySerial.begin(9600);
}

void Sonar::loop()
{
    if( mySerial.available() >= 5)
    { 
        char c;
        for(int i = 0; i < 5; i++)
        {
	    c = mySerial.read();
	    if(c == 'R')
	    {
		char tmp[4] = "000";
		tmp[0] = mySerial.read();
		tmp[1] = mySerial.read();
		tmp[2] = mySerial.read();
		c = mySerial.read();
		if(c == 13)
		    val = atoi(tmp);
	    }       
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
