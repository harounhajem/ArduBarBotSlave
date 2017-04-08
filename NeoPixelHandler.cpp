// 
// 
// 

#include "NeoPixelHandler.h"

NeoPixelHandlerClass NeoPixelHandler;

void NeoPixelHandlerClass::NeoPixelRainBow(uint8_t wait)
{
	if (millis() - timerLed > wait)
	{
		for (i = 0; i < _strip.numPixels(); i++) {
			_strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		_strip.show();
		timerLed = millis();
		j++;
		if (j > 255)
			j = 0;
	}
}

uint32_t NeoPixelHandlerClass::Wheel(byte WheelPos)
{
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	WheelPos -= 170;
	return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}

void NeoPixelHandlerClass::Init(Adafruit_NeoPixel strip)
{
	_strip = strip;
}
