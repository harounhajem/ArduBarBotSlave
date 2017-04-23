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
bool CommunicationClass::ReadIncomingMessage_Compare(String compareMsg)
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


	if (compareMsg == tempMessage)
	{
		return true;
	}
	else
	{
		return false;
	}
}


CommunicationClass Communication;

