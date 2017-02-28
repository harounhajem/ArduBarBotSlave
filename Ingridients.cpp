// 
// 
// 

#include "Ingridients.h"

Container::Container()
{
	name = "empty";
	amountCl = 0;
}



String Container::GetName()
{
	return name;
}

bool Container::SetName(String newName)
{
	if (sizeof(newName) > 30) {
		Serial.println("Error 9117: name to long, max length is 30 char.");
		return false;
	}
	else
	{
		name = newName;
		return true;
	}

}


bool Container::SetAmount(int newAmount)
{
	amountCl = newAmount;
	return false;
}

int Container::GetAmount()
{
	return amountCl;
}

bool Container::Refill(String newName, int newAmountCl)
{
	if (!SetName(newName)){
		return false;
	}

	SetAmount(newAmountCl);

	return true;
}


Container Ingridients;

