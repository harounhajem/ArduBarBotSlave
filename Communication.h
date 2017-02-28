// Communication.h

#ifndef _COMMUNICATION_h
#define _COMMUNICATION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "Ingridients.h"
#else
#include "WProgram.h"
#endif

class CommunicationClass
{
protected:

public:
	void init();
	void SendIngridients(Container containers[6]);

private:
	String 
		splitChar = "#",
		endChar = "@";

};

extern CommunicationClass Communication;

#endif

