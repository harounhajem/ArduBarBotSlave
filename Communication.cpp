// 
// 
// 

#include "Communication.h"

void CommunicationClass::init()
{


}

static boolean recvInProgress = false;
static byte ndx = 0;


char rc;
boolean newData = false;
const byte numChars = 50;
char receivedChars[numChars];
void CommunicationClass::SendIngridients(Container containers[6])
{
	unsigned long timeOutTimer = millis();
	for (short i = 0; i < 6; i++)
	{

		//Send index number
		String sendMessage = splitCharIndex;
		sendMessage += String(i + 1);
		sendMessage += splitCharName;
		sendMessage += containers[i].GetName();
		sendMessage += splitCharAmount;
		sendMessage += containers[i].GetAmount();
		sendMessage += splitEnd;

		short counter = 0;
		do
		{
			if (counter < 2)
			{
				Serial1.print(sendMessage);
				Serial.print("\n\nSent:   ");
				Serial.println(sendMessage);
				counter++;
			}

			if (millis() - timeOutTimer > 5000UL)
			{
				return;
			}

		} while (!ReadIncomingMessage_Compare(sendMessage));

		Serial1.read();
		Serial.read();
	}

	delay(250);
}

String tempString;
String CommunicationClass::ReadIncomingMessage() {

	while (Serial1.available() > 0 && newData == false) {
		rc = Serial1.read();
		Serial.println(rc);
		if (recvInProgress == true) {
			if (rc != splitEnd[0]) {
				receivedChars[ndx] = rc;
				ndx++;
				//if (ndx >= numChars) {   /// Constrainning?
				//	ndx = numChars - 1;
				//}
			}
			else {
				receivedChars[ndx] = rc;
				recvInProgress = false;
				ndx = 0;
				newData = true;
			}
		}
		else if (rc == splitCharIndex[0]) {
			receivedChars[ndx] = rc;
			recvInProgress = true;
			ndx++;
		}
	}


	if (newData == true) {
		newData = false;
		Serial.print("Recived:");
		Serial.println(receivedChars);
		tempString = receivedChars;
		memset(receivedChars, 0, numChars); // Reset array of chars, the message
		return tempString;
	}

	return "empty";

}
String tempMessage;
bool CommunicationClass::ReadIncomingMessage_Compare(String checkSum)
{

	while (Serial1.available() > 0 && newData == false) {
		rc = Serial1.read();

		if (recvInProgress == true) {
			if (rc != splitEnd[0]) {
				receivedChars[ndx] = rc;
				ndx++;
				//if (ndx >= numChars) {   /// Constrainning?
				//	ndx = numChars - 1;
				//}
			}
			else {
				receivedChars[ndx] = rc;
				recvInProgress = false;
				ndx = 0;
				newData = true;
			}
		}
		else if (rc == splitCharIndex[0]) {
			receivedChars[ndx] = rc;
			recvInProgress = true;
			ndx++;
		}
	}


	if (newData == true) {
		newData = false;
		Serial.print("Recived:");
		Serial.println(receivedChars);
		tempMessage = receivedChars;
		memset(receivedChars, 0, numChars); // Reset array of chars, the message
	}


	if (checkSum == tempMessage)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//
//bool CommunicationClass::AwaitChecksum(String sentMessage)
//{
//
//#define MAX_MILLIS_TO_WAIT 500  //or whatever
//	int messageArrayLength = sentMessage.length();
//	unsigned long starttime;
//
//	starttime = millis();
//
//	while ((Serial1.available() > messageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
//	{
//		// hang in this loop until we either get 9 bytes of data or 1 second
//		// has gone by
//	}
//	if (Serial1.available() < messageArrayLength)
//	{
//		// the data didn't come in - handle that problem here
//		Serial.println("ERROR - Didn't get bytes of data!");
//		Serial1.flush();
//		return false;
//	}
//	else
//	{
//		char *RFin_bytes = new char[messageArrayLength];
//		for (int n = 0; n < messageArrayLength; n++) {
//			RFin_bytes[n] = Serial1.read(); // Then: Get them.
//		}
//
//		String messageCheckSum;
//		for (size_t i = 0; i < messageArrayLength; i++)
//		{
//			messageArrayLength += RFin_bytes[i];
//			//Serial.print(RFin_bytes[i]);
//
//		}
//
//		/*Serial.print("SentMessage:");
//		Serial.println(sentMessage);
//		Serial.print("Checksum:");
//		Serial.println(messageCheckSum);
//		Serial.println("\n");*/
//
//
//		if (messageCheckSum == sentMessage)
//		{
//			Serial.println(" IS EQUAL ?");
//
//			Serial.println(messageCheckSum);
//			Serial.println(sentMessage);
//			delay(2500);
//			digitalWrite(2, HIGH);
//			int as = 66;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//}
//bool CommunicationClass::newChecksum(String sentMessage)
//{
//	int messageArrayLength = sentMessage.length();
//	if (Serial1.available() >= messageArrayLength - 1)
//	{
//
//		unsigned long starttime;
//
//		char *RFin_bytes = new char[messageArrayLength];
//		for (int n = 0; n < messageArrayLength; n++) {
//			RFin_bytes[n] = Serial1.read(); // Then: Get them.
//		}
//
//		String messageCheckSum;
//		for (size_t i = 0; i < messageArrayLength; i++)
//		{
//			messageArrayLength += RFin_bytes[i];
//			//Serial.print(RFin_bytes[i]);
//
//		}
//		int t = 45;
//		Serial.print("Checksum: ");
//		Serial.println(messageCheckSum);
//		/*Serial.print("SentMessage:");
//		Serial.println(sentMessage);
//		Serial.print("Checksum:");
//		Serial.println(messageCheckSum);
//		Serial.println("\n");*/
//
//
//		if (messageCheckSum == sentMessage)
//		{
//			Serial.println(" IS EQUAL ?");
//
//			Serial.println(messageCheckSum);
//			Serial.println(sentMessage);
//			delay(2500);
//			int as = 66;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//}
//bool AwaitChecksum(String sentMessage) {
//
//#define MAX_MILLIS_TO_WAIT 50  //or whatever
//	int messageArrayLength = sizeof(sentMessage);
//	unsigned long starttime;
//
//	starttime = millis();
//
//	while ((Serial1.available() < messageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
//	{
//		// hang in this loop until we either get 9 bytes of data or 1 second
//		// has gone by
//	}
//	if (Serial1.available() < messageArrayLength)
//	{
//		// the data didn't come in - handle that problem here
//		Serial.println("ERROR - Didn't get bytes of data!");
//		Serial1.flush();
//		return false;
//	}
//	else
//	{
//		char *RFin_bytes = new char[messageArrayLength];
//		for (int n = 0; n < messageArrayLength; n++)
//			RFin_bytes[n] = Serial1.read(); // Then: Get them.
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

