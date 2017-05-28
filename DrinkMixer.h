// DrinkMixer.h

#ifndef _DRINKMIXER_h
#define _DRINKMIXER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include "Adafruit_NeoPixel.h"
#else
#include "WProgram.h"
#endif

class DrinkMixerClass
{

private:
	int soleniod[8];
	Adafruit_NeoPixel _strip = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
	int _airPump = 0;
	int _motor = 0;
	int _bottle1 = 0;
	int _bottle2 = 0;
	int _bottle3 = 0;
	int _bottle4 = 0;
	int _bottle5 = 0;
	int _bottle6 = 0;

public:
	void SetLiquidToStartPos();

	void TurnOffAllRelays();

	void CleanCenterTube();

	void CleanAllTubes();

	void RunDrinkOrder( int amountCentiliter,  int bottleNr);

	void init(int tmpairPump, int tmpmotor, int tmpbottle1, int tmpbottle2, int tmpbottle3, int tmpbottle4, int tmpbottle5, int tmpbottle6);
};

extern DrinkMixerClass DrinkMixer;

#endif

