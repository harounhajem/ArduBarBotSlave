// NeoPixelHandler.h

#ifndef _NEOPIXELHANDLER_h
#define _NEOPIXELHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <Adafruit_NeoPixel.h>
#else
#include "WProgram.h"
#endif

class NeoPixelHandlerClass
{

private:

	unsigned long timerLed = 0;

	uint16_t i, j;

	uint32_t Wheel(byte WheelPos);

public:
	Adafruit_NeoPixel _strip; 

	void NeoPixelRainBow(uint8_t wait);

	void SetColor_DrinkProduce();

	void SetColor_Off();

	NeoPixelHandlerClass(Adafruit_NeoPixel &stripy);
};

extern NeoPixelHandlerClass NeoPixelHandler;

#endif

