// DrinkOrder.h

#ifndef _DRINKORDER_h
#define _DRINKORDER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DrinkOrderClass
{
 protected:


 public:
	unsigned int bottleIndex;
	unsigned int amount;
};

extern DrinkOrderClass DrinkOrder;

#endif

