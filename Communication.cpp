// 
// 
// 

#include "Communication.h"

void CommunicationClass::init()
{


}

void CommunicationClass::SendIngridients(Container containers[6])
{
	for (size_t i = 0; i < sizeof(containers); i++)
	{
		String sendMessage = startName;
		sendMessage += containers[i].GetName();
		sendMessage += startAmount;
		sendMessage += containers[i].GetAmount();
		sendMessage += stopMessage;

		Serial3.println(sendMessage);
		Serial.println(sendMessage);
	}
	delay(5000);
}


CommunicationClass Communication;

