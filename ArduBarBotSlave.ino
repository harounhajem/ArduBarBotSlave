#include "Communication.h"
#include "Ingridients.h"
#include "Communication.h"

#define ledLamp 2
String readString;

Container myContainers[6];
CommunicationClass btCommunication;


void setup()
{
	Serial1.begin(230400);
	Serial.begin(115200);
	pinMode(ledLamp, OUTPUT);
	digitalWrite(ledLamp, LOW);
	SetMockDATA();
}

unsigned long timerRecive;
void loop()
{
	if (Serial1.available())
	{
		int msg = Serial1.read();
		Serial.print("\n\nCommand recived: ");
		Serial.println(msg);
		switch (msg)
		{
		case 'e':
			// Send ingridients
			btCommunication.SendIngridients(myContainers);
			break;
		case 'd':
			// Update ingridients
			timerRecive = millis();
			delay(100);
			do
			{
			Communication.DeSerializerWithChecksum("a");
			} while ((millis() - timerRecive) > 150);

			break;
		case 'f':
			// Get Cocktail order
			Serial.println("Get cocktail command");
			break;
		default:
			Serial.print("Unkown command sent: ");
			Serial.println(msg);
			Serial1.read();
			break;
		}
	}
}
// SET MOCKDATA
void SetMockDATA() {
	if (!myContainers[0].SetName("Margaritas") ||
		!myContainers[1].SetName("Vodka") ||
		!myContainers[2].SetName("Tequila") ||
		!myContainers[3].SetName("Whiskey") ||
		!myContainers[4].SetName("Braunstein Gylden") ||
		!myContainers[5].SetName("Ekologiska Osterlensnapsar"))
	{
		Serial.print("naming error");
	}

	for (short i = 0; i < 6; i++)
	{
		myContainers[i].SetAmount(random(100, 2500));
	}

}


// GET DATA
void ReadBytesOfArray() {

#define MAX_MILLIS_TO_WAIT 1000  //or whatever
#define MessageArrayLength 256
	unsigned long starttime;

	starttime = millis();

	while ((Serial1.available() < MessageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
	{
		// hang in this loop until we either get 9 bytes of data or 1 second
		// has gone by
	}
	if (Serial1.available() < MessageArrayLength)
	{
		// the data didn't come in - handle that problem here
		Serial.println("ERROR - Didn't get 9 bytes of data!");
		Serial1.read();
	}
	else
	{
		char *RFin_bytes = new char[MessageArrayLength];
		for (int n = 0; n < MessageArrayLength; n++)
			RFin_bytes[n] = Serial1.read(); // Then: Get them.

		for (size_t i = 0; i < sizeof(RFin_bytes); i++)
		{
			Serial.print(RFin_bytes[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}
void ReadCommand() {

	while (Serial1.available())
	{
		byte x[1];
		Serial1.readBytes(x, 1);
		Serial.print((char*)x);
	}
	Serial.println();
}


// POST DATA
void SendIngridents() {

	// Send data to cellphone?

	Serial.print(567);











	//myIngridiensts[1].Refill("Vodka", 300);
	//if (Serial.available())
	//{
	//	int asd = (int)Serial.read();
	//	if (asd == 40 )
	//	{
	//		Serial.print(myIngridiensts[1].GetName());
	//	}
	//}



}
void SendMessageOnCommand() {
	while (Serial1.available() > 0)
	{

		int msg = Serial1.read();
		Serial.print(Serial1.read());
		if (msg == 'e')
		{


			SendMessage();

		}
	}
	digitalWrite(ledLamp, LOW);
}

void SendMessage() {

	// Två första tecknen eller första tecknet försvinner

	String myStringMsg = "## Vodka Martini: 10";
	int charCount = 21;
	Serial.println(charCount);

	byte bufferSend[1024];
	digitalWrite(ledLamp, HIGH);

	for (int i = 0; i < charCount; i++) {
		bufferSend[i] = (byte)myStringMsg[i];
		Serial1.write(bufferSend[i]);
		Serial.print((char)bufferSend[i]);
	}
	Serial.println();
	Serial1.flush();
}
void SendNumbers() {
	byte bufferSend[1024];
	for (int i = 0; i < 1024; i++) {
		bufferSend[i] = (byte)i;
		Serial1.print(bufferSend[i]);
		Serial1.print(' ');
		Serial.print((char)bufferSend[i]);
		delay(10);
	}

}