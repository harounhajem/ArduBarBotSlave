// 
// 
// 

#include "Communication.h"

void CommunicationClass::init()
{


}

void CommunicationClass::SendIngridients(Container containers[6])
{
	
			for (short i = 0; i < 6; i++)
			{
				String sendMessage = splitChar;
				sendMessage += containers[i].GetName();
				sendMessage += splitChar;
				sendMessage += containers[i].GetAmount();
				sendMessage += endChar;

				Serial3.println(sendMessage);
				//Serial.print(i);
				//Serial.println(" " + sendMessage);
			}
			//Serial.println("\n\n");

			//delay(5000);
		
}


CommunicationClass Communication;

