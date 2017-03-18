#include <flash_efc.h>
#include <efc.h>
#include <DueFlashStorage.h>
#include "Communication.h"
#include "Ingridients.h"
DueFlashStorage EEProm;		// EEProm on Arduino DUE

// Pinout
#define ledLamp 2

// Variables
String readString;

// Class declaration
Container barBotContainer[6];	// Barbot alcohol container
CommunicationClass btCommunication;  // Bluetooth communication

struct SaveContainer {
	String Bottle[12];
};
SaveContainer getSave;
Container openContainer[6];

void setup()
{
	Serial1.begin(230400);
	Serial.begin(115200);
	//SetMockDATA();

#pragma region SetMock


	barBotContainer[0].SetName("Margaritas");
	barBotContainer[1].SetName("Vodka");
	barBotContainer[2].SetName("Tequila");
	barBotContainer[3].SetName("Whiskey");
	barBotContainer[4].SetName("Braunstein Gylden");
	barBotContainer[5].SetName("Ekologiska Osterlensnapsar");

	for (short i = 0; i < 6; i++)
	{
		barBotContainer[i].SetAmount(random(100, 2500));
	}

#pragma endregion


#pragma region Save Mechanism


	// 1. Convert to String
	SaveContainer varSave{
		barBotContainer[0].GetName(),
		String(barBotContainer[0].GetAmount()),
		barBotContainer[1].GetName(),
		String(barBotContainer[1].GetAmount()),
		barBotContainer[2].GetName(),
		String(barBotContainer[2].GetAmount()),
		barBotContainer[3].GetName(),
		String(barBotContainer[3].GetAmount()),
		barBotContainer[4].GetName(),
		String(barBotContainer[4].GetAmount()),
		barBotContainer[5].GetName(),
		String(barBotContainer[5].GetAmount())
	};

	// 2. Save
	byte b2[sizeof(varSave)]; // create byte array to store the struct
	memcpy(b2, &varSave, sizeof(varSave)); // copy the struct to the byte array
	EEProm.write(4, b2, sizeof(varSave)); // write byte array to flash at address 4
#pragma endregion

#pragma region Load Mechanism


										  // 3. Load
	byte* b = EEProm.readAddress(4); // byte array which is read from flash at adress 4
	getSave;
	memcpy(&getSave, b, sizeof(SaveContainer)); // copy byte array to temporary struct




												// 4. Convert saved
	int counter = 0;

	for (size_t i = 0; i < 12; i++)
	{
		if (i % 2 == 0)
		{
			openContainer[counter].SetName(getSave.Bottle[i]);
		}
		else
		{
			long x = getSave.Bottle[i].toInt();
			openContainer[counter].SetAmount(x);
			counter++;
		}
	}
#pragma endregion

}

unsigned long timerRecive;
void loop()
{
	Serial.print("\n\nConverted: \n");
	for (size_t i = 0; i < 6; i++)
	{
		Serial.print(openContainer[i].GetName());
		Serial.print("  ");
		Serial.println(openContainer[i].GetAmount());
		delay(150);
	}

	//if (Serial1.available())
	//{
	//	int msg = Serial1.read();


	//	Serial.print("\n\nCommand recived: ");
	//	Serial.println(msg);


	//	switch (msg)
	//	{
	//	case 'e':
	//		Serial.println("Send ingridients");

	//		// Send ingridients
	//		btCommunication.SendIngridients(barBotContainer);
	//		break;
	//	case 'd':
	//		Serial.println("Update ingridients");

	//		// Update ingridients
	//		timerRecive = millis();

	//		// recive ingridient
	//		delay(100);
	//		do
	//		{
	//		Communication.DeSerializerWithChecksum("a");
	//		} while ((millis() - timerRecive) > 150);

	//		// update ingridient 

	//		break;
	//	case 'f':
	//		// Get Cocktail order
	//		Serial.println("Get cocktail command");
	//		break;
	//	default:
	//		Serial.print("Unkown command sent: ");
	//		Serial.println(msg);
	//		Serial1.read();
	//		break;
	//	}
	//}


}
// SET MOCKDATA
void SetMockDATA() {
	if (!barBotContainer[0].SetName("Margaritas") ||
		!barBotContainer[1].SetName("Vodka") ||
		!barBotContainer[2].SetName("Tequila") ||
		!barBotContainer[3].SetName("Whiskey") ||
		!barBotContainer[4].SetName("Braunstein Gylden") ||
		!barBotContainer[5].SetName("Ekologiska Osterlensnapsar"))
	{
		Serial.print("naming error");
	}

	for (short i = 0; i < 6; i++)
	{
		barBotContainer[i].SetAmount(random(100, 2500));
	}

}

//void StoreData() {
//
//
//#pragma region SetMock
//
//
//	barBotContainer[0].SetName("Margaritas");
//	barBotContainer[1].SetName("Vodka");
//	barBotContainer[2].SetName("Tequila");
//	barBotContainer[3].SetName("Whiskey");
//	barBotContainer[4].SetName("Braunstein Gylden");
//	barBotContainer[5].SetName("Ekologiska Osterlensnapsar");
//
//	for (short i = 0; i < 6; i++)
//	{
//		barBotContainer[i].SetAmount(random(100, 2500));
//	}
//
//#pragma endregion
//
//	for (size_t i = 0; i < 6; i++)
//	{
//		Serial.println(barBotContainer[i].GetName());
//		Serial.println(barBotContainer[i].GetAmount());
//	}
//	// 1. Convert to String
//	SaveContainer varSave{
//		barBotContainer[0].GetName(),
//		String(barBotContainer[0].GetAmount()),
//		barBotContainer[1].GetName(),
//		String(barBotContainer[1].GetAmount()),
//		barBotContainer[2].GetName(),
//		String(barBotContainer[2].GetAmount()),
//		barBotContainer[3].GetName(),
//		String(barBotContainer[3].GetAmount()),
//		barBotContainer[4].GetName(),
//		String(barBotContainer[4].GetAmount()),
//		barBotContainer[5].GetName(),
//		String(barBotContainer[5].GetAmount())
//	};
//
//	// 2. Save
//	byte b2[sizeof(varSave)]; // create byte array to store the struct
//	memcpy(b2, &varSave, sizeof(varSave)); // copy the struct to the byte array
//	EEProm.write(4, b2, sizeof(varSave)); // write byte array to flash at address 4
//}



//void GetStoredData() {
//
//	// 3. Get data
//	byte* b = EEProm.readAddress(4); // byte array which is read from flash at adress 4
//	getSave;
//	memcpy(&getSave, b, sizeof(SaveContainer)); // copy byte array to temporary struct
//
//
//	for (size_t i = 0; i < 12; i++)
//	{
//		Serial.println(getSave.Bottle[i]);
//	}
//
//	// 4. Format saved data
//	int counter = 0;
//
//	for (size_t i = 0; i < 12; i++)
//	{
//		if (i % 2 == 0)
//		{
//			savedData[counter].SetName(getSave.Bottle[i]);
//		}
//		else
//		{
//			int x = getSave.Bottle[i].toInt();
//			savedData[counter].SetAmount(x);
//			counter++;
//		}
//	}
//}



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