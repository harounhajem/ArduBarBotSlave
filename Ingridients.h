// Ingridients.h

#ifndef _INGRIDIENTS_h
#define _INGRIDIENTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Container
{
private:
	String name;
	int amountCl;


public:
	Container();

	String GetName();
	bool SetName(String newName);

	bool SetAmount(int newAmountCl);
	int GetAmount();

	bool Refill(String newName, int newAmountCl);
	
};

extern Container Containers;

#endif

