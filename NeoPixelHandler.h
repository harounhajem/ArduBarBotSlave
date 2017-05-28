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
	Adafruit_NeoPixel _strip = Adafruit_NeoPixel(16, 9, NEO_GRB + NEO_KHZ800);

	void NeoPixelRainBow(uint8_t wait);

	void SetColor_DrinkProduce();

	void SetColor_Off();

	void Init(Adafruit_NeoPixel strip);

	NeoPixelHandlerClass(const int numLed, const int ledPin);
};

extern NeoPixelHandlerClass NeoPixelHandler;

#endif

