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

	Adafruit_NeoPixel _strip = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);

public:

	void NeoPixelRainBow(uint8_t wait);

	uint32_t Wheel(byte WheelPos);

	void Init(Adafruit_NeoPixel strip);
};

extern NeoPixelHandlerClass NeoPixelHandler;

#endif

