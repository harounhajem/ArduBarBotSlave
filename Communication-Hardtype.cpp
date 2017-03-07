// 
// 
// 

#include "Communication.h"

void CommunicationClass::init()
{


}

void CommunicationClass::SendIngridients(Container containers[6])
{
	unsigned long timeOutTimer = millis();
	for (short i = 0; i < 6; i++)
	{

		//Send index number
		String sendMessage = splitCharIndex;
		sendMessage += String(i);
		sendMessage += splitCharName;
		sendMessage += containers[i].GetName();
		sendMessage += splitCharAmount;
		sendMessage += containers[i].GetAmount();
		sendMessage += endChar;

		int asynAnswer = 0;
		int const ans = 65;
		do
		{
			Serial3.print(sendMessage);
			Serial.println(sendMessage);
			//if ( millis() - timeOutTimer > 6500UL)
			//{
			//	return;
			//}

		} while (!newChecksum(sendMessage));
		delay(100);
	}
	Serial3.flush();
	Serial.flush();
	digitalWrite(2, HIGH);
	delay(5500);
}
bool CommunicationClass::AwaitChecksum(String sentMessage)
{

#define MAX_MILLIS_TO_WAIT 500  //or whatever
	int messageArrayLength = sentMessage.length();
	unsigned long starttime;

	starttime = millis();

	while ((Serial3.available() < messageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
	{
		// hang in this loop until we either get 9 bytes of data or 1 second
		// has gone by
	}
	if (Serial3.available() < messageArrayLength)
	{
		// the data didn't come in - handle that problem here
		Serial.println("ERROR - Didn't get bytes of data!");
		Serial3.flush();
		return false;
	}
	else
	{
		char *RFin_bytes = new char[messageArrayLength];
		for (int n = 0; n < messageArrayLength; n++) {
			RFin_bytes[n] = Serial3.read(); // Then: Get them.
		}

		String messageCheckSum;
		for (size_t i = 0; i < messageArrayLength; i++)
		{
			messageArrayLength += RFin_bytes[i];
			//Serial.print(RFin_bytes[i]);

		}

		/*Serial.print("SentMessage:");
		Serial.println(sentMessage);
		Serial.print("Checksum:");
		Serial.println(messageCheckSum);
		Serial.println("\n");*/


		if (messageCheckSum == sentMessage)
		{
			Serial.println(" IS EQUAL ?");

			Serial.println(messageCheckSum);
			Serial.println(sentMessage);
			delay(2500);
			digitalWrite(2, HIGH);
			int as = 66;
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool CommunicationClass::newChecksum(String sentMessage)
{
	int messageArrayLength = sentMessage.length();
	if (Serial3.available() >= messageArrayLength-1)
	{

		unsigned long starttime;

		char *RFin_bytes = new char[messageArrayLength];
		for (int n = 0; n < messageArrayLength; n++) {
			RFin_bytes[n] = Serial3.read(); // Then: Get them.
		}

		String messageCheckSum;
		for (size_t i = 0; i < messageArrayLength; i++)
		{
			messageArrayLength += RFin_bytes[i];
			//Serial.print(RFin_bytes[i]);

		}
		int t = 45;
		Serial.print("Checksum: ");
		Serial.println(messageCheckSum);
		/*Serial.print("SentMessage:");
		Serial.println(sentMessage);
		Serial.print("Checksum:");
		Serial.println(messageCheckSum);
		Serial.println("\n");*/


		if (messageCheckSum == sentMessage)
		{
			Serial.println(" IS EQUAL ?");

			Serial.println(messageCheckSum);
			Serial.println(sentMessage);
			delay(2500);
			int as = 66;
			return true;
		}
		else
		{
			return false;
		}
	}

}
//bool AwaitChecksum(String sentMessage) {
//
//#define MAX_MILLIS_TO_WAIT 50  //or whatever
//	int messageArrayLength = sizeof(sentMessage);
//	unsigned long starttime;
//
//	starttime = millis();
//
//	while ((Serial3.available() < messageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
//	{
//		// hang in this loop until we either get 9 bytes of data or 1 second
//		// has gone by
//	}
//	if (Serial3.available() < messageArrayLength)
//	{
//		// the data didn't come in - handle that problem here
//		Serial.println("ERROR - Didn't get bytes of data!");
//		Serial3.flush();
//		return false;
//	}
//	else
//	{
//		char *RFin_bytes = new char[messageArrayLength];
//		for (int n = 0; n < messageArrayLength; n++)
//			RFin_bytes[n] = Serial3.read(); // Then: Get them.
//
//
//		String messageCheckSum;
//		for (size_t i = 0; i < sizeof(RFin_bytes); i++)
//		{
//			messageCheckSum += RFin_bytes[i];
//			Serial.print(RFin_bytes[i]);
//			Serial.print(" ");
//		}
//
//		Serial.println();
//		if (messageCheckSum == sentMessage)
//		{
//			return true;
//		}
//	}
//}





CommunicationClass Communication;

