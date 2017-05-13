#include "SDCardHandler.h"
#include "NeoPixelHandler.h"
#include "DrinkMixer.h"
#include <SD.h>
#include <Adafruit_NeoPixel.h>
#include "DrinkOrder.h"
#include "Communication.h"
#include "Ingridients.h"
#include <SPI.h>
#include "SDCardHandler.h"


	#pragma region PinOut

// Pinout
#define ledNeoPixel 10
#define airPump 8
#define motor 12
#define bottle1 2
#define bottle2 3
#define bottle3 4
#define bottle4 5
#define bottle5 6
#define bottle6 7
#define NUMstrip 16
#define SD_SPI 53
#pragma endregion		

	#pragma region Variables


// Variables
unsigned long timerRecive, timerTimeOut;

#pragma endregion

	#pragma region Class declaration

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMstrip, ledNeoPixel, NEO_GRB + NEO_KHZ800);

// Class declaration
struct SaveContainer {  // Formatting table for saving BarBotContainer
	String Bottle[14];
};

DrinkMixerClass drinkMixer;
NeoPixelHandlerClass neoPixelHandler;
Container barBotContainer[6];			// Barbot alcohol container
CommunicationClass btCommunication;		// Bluetooth communication

SDCardHandlerClass SDHandler;

#pragma endregion

void setup()
{

	pinMode(airPump, OUTPUT);
	pinMode(motor, OUTPUT);
	pinMode(bottle1, OUTPUT);
	pinMode(bottle2, OUTPUT);
	pinMode(bottle3, OUTPUT);
	pinMode(bottle4, OUTPUT);
	pinMode(bottle5, OUTPUT);
	pinMode(bottle6, OUTPUT);
	pinMode(SD_SPI, OUTPUT);

	Serial.begin(115200);
	Serial1.begin(230400);

	// Initiate classes

	SDHandler.BeginSD();
	btCommunication.init();
	drinkMixer.init(airPump, motor, bottle1, bottle2, bottle3, bottle4, bottle5, bottle6);

	//neoPixelHandler.Init(strip);
	//strip.begin();
	//drinkMixer.SetLiquidToStartPos();
	SDHandler.Load(barBotContainer);
	//// Read Saved Data
	Serial.print("\n\Loaded from SD: \n");
	for (size_t i = 0; i < 6; i++)
	{
		Serial.print(barBotContainer[i].GetName());
		Serial.print("  ");
		Serial.println(barBotContainer[i].GetAmount());
	} 
}

void loop()
{
	//neoPixelHandler.NeoPixelRainBow(200);

	/*Serial.println("Got a cocktail command");
	ValidateDrinkOrder();*/

	if (Serial1.available() && (millis() - timerTimeOut > 650UL))
	{
		int msg = Serial1.read();
		Serial.print("\n\nCommand recived: ");
		Serial.println(msg);

		switch (msg)
		{
		case 'e':
			// Send ingridients
			Serial.println("Send ingridients");
			btCommunication.SendIngridients(barBotContainer);
			break;

		case 'd':
			// Update ingridients
			Serial.println("Update ingridients");
			UpdateIngridients();
			break;

		case 'f':
			// Got a Cocktail order
			Serial.println("Got a cocktail command");
			ValidateDrinkOrder();
			break;

		default:
			Serial.print("Unkown command sent: ");
			Serial.println(msg);
			Serial1.flush();
			timerTimeOut = millis();
			break;
		}
	}
}


	#pragma region Produce cocktail order

void ValidateDrinkOrder() {

	// 1. Ta emot ett meddelande
	delay(100);
	String recivedMessage = "none";
	recivedMessage = btCommunication.ReadIncomingMessage();
	Serial.println("Recived orderdrink: " + recivedMessage);

	Communication.init();
	// Trim message

	const char *split = ";";

	String msgTrim = recivedMessage.substring(1, recivedMessage.length() - 1); // Trimma meddelandet

	Serial.println("Message trim: " + msgTrim);

	char input[msgTrim.length()];

	msgTrim.toCharArray(input, msgTrim.length());  // Konvertera meddelandet till en CharArray

	unsigned int countIngridients = 0; // Räkna hur många flaskor som ordern innehåller

	for (size_t i = 0; i < msgTrim.length(); i++)
	{
		if (msgTrim.charAt(i) == ';')
		{
			countIngridients++;
		}
	}


	// Split message

	countIngridients = countIngridients / 2;
	//Serial.print("countIngridients:");
	//Serial.println(countIngridients);

	DrinkOrderClass drinkOrder[countIngridients];

	unsigned short counterToken = 0;

	unsigned short counterIndex = 0;

	char *token = strtok(input, split);

	while (token != NULL)
	{
		//Serial.print("Saved: ");

		if (counterToken % 2 == 0)
		{
			drinkOrder[counterIndex].bottleIndex = String(token).toInt();
			//Serial.print(drinkOrder[counterIndex].bottleIndex);
		}
		else
		{
			drinkOrder[counterIndex].amount = String(token).toInt();
			//Serial.print(drinkOrder[counterIndex].amount);
			counterIndex++;

		}
		//Serial.print("\nToken: ");
		//Serial.println(token);

		token = strtok(NULL, split);
		counterToken++;
	}

	Serial.println("After split:");
	for (size_t i = 0; i < countIngridients; i++)
	{
		Serial.print(" Index :");
		Serial.print(drinkOrder[i].bottleIndex);
		Serial.print("  Amount :");
		Serial.println(drinkOrder[i].amount);
	}


	// 4. Validate that there is enough liquid, 
	//    answer OK if true

	bool canProduce = true;
	for (size_t i = 0; i < countIngridients; i++)
	{
		if ((barBotContainer[drinkOrder[i].bottleIndex].GetAmount() - drinkOrder[i].amount) < 0) {
			Serial.print("\n ORDER\nIndex :");
			Serial.print(drinkOrder[i].bottleIndex);
			Serial.print("  Amount :");
			Serial.print(drinkOrder[i].amount);

			Serial.print(barBotContainer[drinkOrder[i].bottleIndex].GetName() + "  ");
			Serial.println(barBotContainer[drinkOrder[i].bottleIndex].GetAmount());
			Serial.println("FAIL: TO BIG ORDER");
			canProduce = false;
			break;
		}
	}

	if (canProduce)
	{
		Serial1.println("OK");
		Serial.println("OK");
	}
	else
	{
		Serial.println("NOT OK");
		return;
	}

	// 5. Send drink to machine
	ProduceDrinkOrder(drinkOrder, countIngridients);
}

void ProduceDrinkOrder(DrinkOrderClass drinkOrder[], int countIngridients) {

	Serial.println("\n\nProduce:\n");
	for (size_t i = 0; i < countIngridients; i++)
	{
		// Serial print
		Serial.print(" Index :");
		Serial.print(drinkOrder[i].bottleIndex);
		Serial.print("  Amount :");
		Serial.println(drinkOrder[i].amount);

		// 1. Send drinkorder to liquidPump
		drinkMixer.RunDrinkOrder(drinkOrder[i].amount, drinkOrder[i].bottleIndex);

		// 2. Calculate new amount 
		int bottleLiquidAmount = barBotContainer[drinkOrder[i].bottleIndex].GetAmount();
		barBotContainer[drinkOrder[i].bottleIndex].SetAmount(bottleLiquidAmount - drinkOrder[i].amount);
	}

	// 4. Flush center tube
	drinkMixer.CleanCenterTube();

	// 5. Update with the new liquid amount
	SDHandler.Save(barBotContainer);

	// TODO: 6. Send conformation when the drink is ready?
}

#pragma endregion

	#pragma region Update bottles

void UpdateIngridients() {

	Serial.println("Begin updating\nReciving msg.. .");

	// recive ingridient
	timerRecive = millis();
	delay(100);
	String recivedMessage = "none";
	//do
	//{
	//} while ((millis() - timerRecive) > 150);


	// 1. Ta emot nya flaskan
	recivedMessage = Communication.ReadIncomingMessage();
	Serial.print("Recived msg to save: ");
	Serial.println(recivedMessage);

	// 2. Deserialize meddalandet, ta ut Position, Namn, Amount
	const char charBeginDelimiter = Communication.splitCharIndex[0]; // '$'
	const char charNameDelimiter = Communication.splitCharName[0];   // '#'
	const char charAmountDelimiter = Communication.splitCharAmount[0]; // '&'
	const char charEndDelimiter = Communication.splitEnd[0]; // '@'


	int ingridientsPos = recivedMessage.substring(recivedMessage.indexOf(charBeginDelimiter) + 1, recivedMessage.indexOf(charNameDelimiter)).toInt();
	String ingridientsName = recivedMessage.substring(recivedMessage.indexOf(charNameDelimiter) + 1, recivedMessage.indexOf(charAmountDelimiter));
	int ingridientsAmount = recivedMessage.substring(recivedMessage.indexOf(charAmountDelimiter) + 1, recivedMessage.indexOf(charEndDelimiter)).toInt();

	Serial.println("MSG parsed: ");
	Serial.println(ingridientsPos);
	Serial.println(ingridientsName);
	Serial.println(ingridientsAmount);

	
	// 3. Updatera barBotContainer

	barBotContainer[ingridientsPos].SetName(ingridientsName);
	barBotContainer[ingridientsPos].SetAmount(ingridientsAmount);

	// 4. Spara värdet
	SDHandler.Save(barBotContainer);
	Serial.println("Updated / Saved new ingridients");


}

#pragma endregion

	



